#include <Graph.h>
#include <BreadthFirstSearch.h>
#include <Dijkstra.h>
#include <iostream>
#include "GraphAlgorithmTest.h"

const char *names = "sytxz";

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

TEST_F(GraphAlgorithmTest, DijkstraSearch) {
    using graph_t = Graph_base<uint32_t, int>;
    enum { s, y, t, x, z, N};

    graph_t g(true);
    
    g.add_edge(s, y, 5);
    g.add_edge(s, t, 10);
    g.add_edge(y, t, 3);
    g.add_edge(y, z, 2);
    g.add_edge(z, x, 6);
    g.add_edge(x, z, 4);
    g.add_edge(t, x, 1);
    g.add_edge(z, s, 7);
    g.add_edge(y, x, 9);
    g.add_edge(t, y, 2);
    
    Dijkstra<graph_t, int> dijk(g, s, x);
    std::list<graph_t::node_descriptor> path = dijk.getPathToTarget();
    
    for (auto i = path.begin(); i != path.end(); ++i) {
        std::cout << names[*i] << std::endl;
    }
}