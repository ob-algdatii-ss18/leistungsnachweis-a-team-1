#include <Graph.h>
#include <BreadthFirstSearch.h>
#include <iostream>
#include "GraphAlgorithmTest.h"

const char *names = "rstuvwxy";

template <typename Graph>
struct MyBFSVisitor {
    using Node = typename Graph::node_descriptor;
    using Edge = typename Graph::edge_descriptor;

    void initialize_node(Node u, Graph& g) {
        std::cout << u << " initialized with white color." << std::endl;
        g.put(u, 0);
    }

    void discover_node(Node u, Graph&) {
        std::cout << names[u] << " discovered" << std::endl;
    }

    void tree_edge(Edge e, Graph& g) {
        int distance = g.get(e.source());
        g.put(e.target(), distance + 1);
    }
};

TEST_F(GraphAlgorithmTest, BreadthFirstSearch) {
    using graph_t = Graph_base<uint32_t, no_property>;
    enum { r, s, t, u, v, w, x, y, N};

    using E = std::pair<int, int>;
    E edge_array[] = { E(r, s),
                       E(r, v),
                       E(s, w),
                       E(w, t),
                       E(w, x),
                       E(x, t),
                       E(t, u),
                       E(x, y),
                       E(u, y),
                       E(x, u) };

    const int n_edges = sizeof(edge_array) / sizeof(E);
    graph_t g(edge_array, edge_array + n_edges, N, true);

    breadth_first_search(g, s, MyBFSVisitor<graph_t>());

    auto ni = g.nodes();

    for (auto i = ni.first; i != ni.second; ++i) {
        std::cout << names[*i] << g.get(*i) << std::endl;
    }
}