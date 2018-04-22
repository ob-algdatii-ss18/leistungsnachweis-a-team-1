#ifndef ALGODAT_GRAPH_H
#define ALGODAT_GRAPH_H

#include <utility>
#include <vector>
#include <set>
#include <list>

template <typename _Node>
struct Graph_edge_base {
    inline Graph_edge_base() = default;
    inline Graph_edge_base(_Node from, _Node to)
        : _from (from), _to(to) { }

    _Node _from, _to;
};

template <typename _TCost>
class Graph_weighted_edge : public Graph_edge_base<int> {
public:
    Graph_weighted_edge(int from, int to, _TCost cost)
            : Graph_edge_base(from, to), _cost(cost) { }

private:
    _TCost _cost;
};

template <typename _Node, typename _Edge>
class Graph_base {
public:
    using node_descriptor = _Node;
    using edge_descriptor = _Edge;
    using node_list = std::vector<node_descriptor>;
    using edge_list = std::list<edge_descriptor>;
    using out_edge_list = std::vector<edge_list>;


    /**
     * Konstruktoren, Zuweisung
     */
     Graph_base() = default;
     Graph_base(const Graph_base&) = default;
     Graph_base& operator=(const Graph_base&) = default;
     Graph_base(Graph_base&&) noexcept = default;
     Graph_base& operator=(Graph_base&&) noexcept = default;

    /**
     * Methoden
     */
     node_descriptor add_node(node_descriptor node)
    {
        return 0;
    }

private:
    std::pair<node_list, out_edge_list> _mytuple;
};


#endif //ALGODAT_GRAPH_H
