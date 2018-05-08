#ifndef ALGODAT_GRAPH_H
#define ALGODAT_GRAPH_H

#include <utility>
#include <vector>
#include <set>
#include <list>
#include <type_traits>
#include <ostream>
#include <iterator>
#include <memory>

#include "GraphIterator.h"

template <typename _NodeDescriptor>
struct Graph_edge_descriptor {
    using self = Graph_edge_descriptor<_NodeDescriptor>;
    using node_descriptor = _NodeDescriptor;
    using descriptor = std::pair<node_descriptor, node_descriptor>;

    inline Graph_edge_descriptor(node_descriptor from, node_descriptor to)
        : _mytuple(std::pair<node_descriptor, node_descriptor>(from, to))
    { };

    Graph_edge_descriptor(const self& rhs) = default;
    Graph_edge_descriptor(self&& rhs) = default;

    node_descriptor source() const { return _mytuple.first; }
    node_descriptor target() const { return _mytuple.second; }

    descriptor _mytuple;
};

template <typename _EdgeProperty, typename _NodeDescriptor>
struct Graph_edge_descriptor_with_property : public Graph_edge_descriptor<_NodeDescriptor>{
    using self = Graph_edge_descriptor_with_property<_EdgeProperty, _NodeDescriptor>;
    using node_descriptor = _NodeDescriptor;
    using property = _EdgeProperty;
    using base = Graph_edge_descriptor<node_descriptor>;

    Graph_edge_descriptor_with_property(node_descriptor from, node_descriptor to, property* p)
            : base(from, to), _property(p)
    { }

    Graph_edge_descriptor_with_property(const self& rhs)
            : base(rhs), _property(std::move(rhs._property))
    {}

    self& operator=(const self& rhs) {
        _property = std::move(const_cast<self&>(rhs)._property);
        return *this;
    }

    self& operator=(self&& rhs) {
        _property = std::move(rhs._property);
        return *this;
    }

    _EdgeProperty* _property;
};

template <typename Char, typename Traits, typename D, typename N>
std::basic_ostream<Char, Traits>&
operator<<(std::basic_ostream<Char, Traits>& os,
const Graph_edge_descriptor_with_property<D, N>& e) {
    return os << "(" << e.source() << ", " << e.target() << ")";
}

template<typename _Property, typename _NodeDescriptor>
struct stored_edge_impl {
    using self = stored_edge_impl<_Property, _NodeDescriptor>;
    using node_descriptor = _NodeDescriptor;
    using Property = _Property;
    stored_edge_impl() { }
    stored_edge_impl(const node_descriptor to, const Property& p)
            : _to(to), _property(new Property(p))
    { }

    stored_edge_impl(const self& rhs)
            :_to(rhs._to), _property(std::move(
                    const_cast<self&>(rhs)._property))
    { }

    stored_edge_impl(stored_edge_impl&& rhs)
            : _to(rhs._to), _property(std::move(rhs._property))
    { }

    node_descriptor target() const { return _to; }
    inline Property& property() const { return *_property; }

    node_descriptor _to;
    std::unique_ptr<Property> _property;
};

struct no_property {

};

template <typename Iterator>
Iterator prior(Iterator it) {
    return --it;
}

template <typename Container, typename T>
typename Container::iterator push_dispatch(Container& c, T v) {
    c.push_back(v);
    return prior(c.end());
}

template <typename _NodeProperty, typename _EdgeProperty>
class Graph_base {
public:
    struct Graph_node_base;
    using self = Graph_base<_NodeProperty, _EdgeProperty>;
    using node_property = _NodeProperty;
    using edge_property = _EdgeProperty;

    using node_descriptor = unsigned int;
    using edge_descriptor = Graph_edge_descriptor_with_property<edge_property, node_descriptor>;

    using stored_node = Graph_node_base;
    using stored_edge = stored_edge_impl<edge_property, node_descriptor>;

    using node_list = std::vector<stored_node>;
    using edge_list = std::list<stored_edge>;
    using outgoing_edge_list = std::vector<edge_list>;

    using edges_size_t = unsigned int;
    using vertices_size_t = unsigned int;
    using degree_size_t = unsigned int;

    using OutEdgeIter = typename edge_list::iterator;
    using OutEdgeIterTraits = std::iterator_traits<OutEdgeIter>;
    using OutEdgeIterDiff = typename OutEdgeIterTraits::difference_type;
    using out_edge_iterator = out_edge_iter<OutEdgeIter, node_descriptor, edge_descriptor, OutEdgeIterDiff>;

    using node_iterator = Integer_iterator<node_descriptor>;
    using edge_iterator = Graph_edge_iterator<
            node_iterator,
            out_edge_iterator,
            self>;

    /**
     * Konstruktoren, Zuweisung
     */
     Graph_base() = default;
     template <typename EdgeIterator>
     Graph_base(EdgeIterator first, EdgeIterator last,
                vertices_size_t size) {
         while (first != last) {
             add_edge((*first).first, (*first).second);
             ++first;
         }
     }
     Graph_base(const Graph_base&) = default;
     Graph_base& operator=(const Graph_base&) = default;
     Graph_base(Graph_base&&) noexcept = default;
     Graph_base& operator=(Graph_base&&) noexcept = default;

    /**
     * Methoden
     */
    node_descriptor add_node() {
        m_nodes.resize(m_nodes.size() + 1);
        return m_nodes.size() - 1;
    }

     node_descriptor add_node(const node_property& p)
    {
        m_nodes.push_back(stored_node(p));
        return m_nodes.size() - 1;
    }

    void remove_node(node_descriptor v) {
        m_nodes.erase(m_nodes.begin() + v);
        node_descriptor V = num_nodes();

        if (v != V) {
            for (node_descriptor i = 0; i < V; ++i)
                reindex_edge_list(out_edge_list(v), v);
        }
    }

    edge_descriptor add_edge(node_descriptor v, node_descriptor u) {
        typename self::edge_property p{};
        return add_edge(v, u, p);
    }

    edge_descriptor add_edge(node_descriptor v, node_descriptor u, _EdgeProperty e) {
        node_descriptor x = std::max(v, u);
        if (m_nodes.size() <= x) {
            m_nodes.resize(x + 1);
        }

        auto it = push_dispatch(out_edge_list(v), stored_edge(u, e));

        return edge_descriptor(v, u, (*it)._property.get());
    }

    template <typename... TArgs>
    edge_descriptor add_edge(node_descriptor v, node_descriptor u, TArgs&&... args) {
        return add_edge(v, u, _EdgeProperty(std::forward<TArgs>(args)...));
    }

    void remove_edge(edge_descriptor e) {
        out_edge_list(e.source()).erase(e.target());
    }

    template <typename Predicate>
    void remove_out_edge_if(node_descriptor u, Predicate pred) {

    }

    template <typename Predicate>
    void remove_edge_if(node_descriptor u, node_descriptor v, Predicate pred) {


    }

    inline degree_size_t out_degree(node_descriptor u) const {
        return out_edge_list(u).size();
    }

    struct Graph_node_base {
        using descriptor = unsigned int;

        Graph_node_base() { }
        explicit Graph_node_base(const node_property & p) : m_property(p) { }

        edge_list m_out_edges;
        node_property m_property;
    };

    std::pair<node_iterator, node_iterator> nodes() {
        return std::make_pair(vertex_set().begin(), vertex_set().end());
    };

    Integer_range<node_descriptor> vertex_set() const {
        return Integer_range<node_descriptor>(0, m_nodes.size());
    }

    /**
     * Returns begin and end iterator of out-edges.
     * @param u
     * @return
     */
    std::pair<out_edge_iterator, out_edge_iterator>
    out_edges(node_descriptor u) {
        auto begin = out_edge_iterator(out_edge_list(u).begin(), u);
        auto end = out_edge_iterator(out_edge_list(u).end(), u);
        return std::make_pair(begin, end);
    };

    /**
     * @return begin and end iterator of edges.
     */
    std::pair<edge_iterator, edge_iterator> edges() {
        auto begin = edge_iterator(vertex_set().begin(),
                                   vertex_set().begin(),
                                   vertex_set().end(),
                                   *this);
        auto end = edge_iterator(vertex_set().begin(),
                                 vertex_set().end(),
                                 vertex_set().end(),
                                 *this);
        return std::make_pair(begin, end);
    }

    inline edge_list& out_edge_list(node_descriptor v) {
        return m_nodes[v].m_out_edges;
    }

    /**
     * @return the list of outgoing edges of a node.
     */
    inline const edge_list& out_edge_list(node_descriptor v) const {
        return m_nodes[v].m_out_edges;
    }

    /**
     * @return number of edges in Graph
     */
    edges_size_t num_edges() {
        edges_size_t number_edges = 0;
        node_iterator i, iend;
        for (std::tie(i, iend) = nodes(); i != iend; ++i)
            number_edges += out_degree(*i);

        return number_edges;
    }

    /**
     * @return number of nodes in Graph
     */
    vertices_size_t num_nodes() const {
        return m_nodes.size();
    }

    /**
     * @return property associated with node
     */
    node_property get(node_descriptor u) const {
        return m_nodes[u].m_property;
    }

    edge_property get(edge_descriptor u) const {
        edge_list el = out_edge_list(u.source());
        typename edge_list::iterator i = el.begin();


    }

    /**
     * Associate a property with a node.
     * @param u
     * @param p
     */
    void put(node_descriptor u, node_property p) {
        m_nodes[u].m_property = p;
    }

    /**
     * Associate a property with an edge.
     * @param e
     * @param p
     */
    void put(edge_descriptor e, edge_property p) {

    }

private:
    void reindex_edge_list(edge_list& el, node_descriptor u) {
        typename edge_list::iterator ei = el.begin(), e_end = el.end();

        for (; ei != e_end; ++ei) {
            if ((*ei)._to > u) {
                --(*ei)._to;
            }
        }
    }

private:
    node_list m_nodes;
};

template <typename _TCost>
using Weighted_graph = Graph_base<no_property, _TCost>;

#endif //ALGODAT_GRAPH_H