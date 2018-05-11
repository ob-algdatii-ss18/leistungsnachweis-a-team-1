#ifndef ALOGDAT_LABYRINTH_GRAPHITERATOR_H
#define ALOGDAT_LABYRINTH_GRAPHITERATOR_H

#include "IntegerIterator.h"

template <typename Iterator>
struct iterator_value
{
    using type = typename std::iterator_traits<Iterator>::value_type ;
};

template <typename Iterator>
struct iterator_reference
{
    using type = typename std::iterator_traits<Iterator>::reference ;
};

template <typename Iterator>
struct iterator_pointer
{
    using type = typename std::iterator_traits<Iterator>::pointer ;
};

/**
 * The iterator iterates through every outgoing edge from one node in a graph.
 * @tparam BaseIter - The type of the iterator containing the edges.
 * @tparam NodeDescriptor
 * @tparam EdgeDescriptor
 * @tparam Difference - The type to calculate the difference between two iterators
 */
template <typename BaseIter, typename NodeDescriptor, typename EdgeDescriptor, typename  Difference>
struct out_edge_iter {
    using self = out_edge_iter<BaseIter, NodeDescriptor, EdgeDescriptor, Difference>;
    using value_type = EdgeDescriptor;
    using reference = typename iterator_reference<BaseIter>::type;
    using pointer = typename iterator_pointer<BaseIter>::type;
    using difference_type = Difference;

    using iterator_category = typename BaseIter::iterator_category;

    inline out_edge_iter() { }

    inline out_edge_iter(const BaseIter& i, const NodeDescriptor& src)
            : m_iterator(i), m_src(src)
    { }

    inline out_edge_iter(const self& rhs) = default;
    self& operator=(const self& rhs) = default;

    inline EdgeDescriptor dereference() const {
        return EdgeDescriptor(m_src, (*m_iterator).target(),
        &(*m_iterator).property());
    }

    inline EdgeDescriptor operator*() const {
        return dereference();
    }

    void operator++() {
        ++m_iterator;
    }

    inline bool operator==(const self& rhs) const {
        return m_iterator == rhs.m_iterator;
    }

    inline bool operator!=(const self& rhs) const {
        return m_iterator != rhs.m_iterator;
    }

    BaseIter m_iterator;
    NodeDescriptor m_src;
};

/**
 * This iterator iterates through every edge from every node in a graph.
 * @tparam VertexIterator
 * @tparam OutEdgeIterator
 * @tparam Graph
 */
template<typename VertexIterator, typename OutEdgeIterator, typename Graph>
class Graph_edge_iterator {
    using self = Graph_edge_iterator<VertexIterator, OutEdgeIterator, Graph>;
public:
    using value_type = typename OutEdgeIterator::value_type;
    using reference = typename OutEdgeIterator::reference;
    using pointer = typename OutEdgeIterator::pointer;
    using difference_type = typename OutEdgeIterator::difference_type;
    using iterator_category = std::forward_iterator_tag;

    Graph_edge_iterator() { }

    Graph_edge_iterator(const self&) = default;

    template <typename G>
    inline Graph_edge_iterator(VertexIterator begin, VertexIterator curr, VertexIterator end, G& g)
            : m_begin(begin), m_curr(curr), m_end(end), m_g(&g)
    {
        /* Go to the first node with more than zero edges */
        if (m_curr != m_end) {
            while (m_curr != m_end && m_g->out_degree(*m_curr) == 0)
                ++m_curr;
            if (m_curr != m_end)
                m_edges = m_g->out_edges(*m_curr);
        }
    }

    inline self& operator++() {
        ++m_edges.first;
        if (m_edges.first == m_edges.second) {
            ++m_curr;
            while (m_curr != m_end && m_g->out_degree(*m_curr) == 0) {
                ++m_curr;
            }
            if (m_curr != m_end)
                m_edges = m_g->out_edges(*m_curr);
        }

        return *this;
    }

    inline self& operator++(int) {
        self tmp = *this;
        ++(*this);
        return tmp;
    }

    inline value_type operator*() const {
        return *m_edges.first;
    }

    inline bool operator== (const self& x) const {
        return m_curr == x.m_curr && (m_curr == m_end || m_edges.first == x.m_edges.first);
    }

    inline bool operator!= (const self& x) const {
        return !(*this==x);
    }

protected:
    VertexIterator m_begin;
    VertexIterator m_curr;
    VertexIterator m_end;

    std::pair<OutEdgeIterator, OutEdgeIterator> m_edges;

    Graph *m_g;
};

#endif