#ifndef ALOGDAT_LABYRINTH_BREADTHFIRSTSEARCH_H
#define ALOGDAT_LABYRINTH_BREADTHFIRSTSEARCH_H

#include "Color.h"

#include <deque>

template <typename Graph, typename BFSVisitor>
void breadth_first_search(Graph& g, typename Graph::node_descriptor start_node, BFSVisitor vis) {
    using Node = typename Graph::node_descriptor;
    using Iter = typename Graph::out_edge_iterator;
    using ColorValue = color_type;
    typename Graph::node_iterator ni, ni_end;
    std::vector<color_type> colors(g.num_nodes());
    std::deque<Node> queue;
    Iter ei, ei_end;

    // Init all nodes with white color
    for (std::tie(ni, ni_end) = g.nodes(); ni != ni_end; ++ni) {
        colors[*ni] = Color::white();
        vis.initialize_node(*ni, g);
    }

    colors[start_node] = Color::gray();
    vis.discover_node(start_node, g);
    queue.push_back(start_node);

    while (!queue.empty()) {
        Node u = queue.front();
        queue.pop_front();
        std::tie(ei, ei_end) = g.out_edges(u);

        for (; ei != ei_end; ++ei)
        {
            Node v = (*ei).target();
            ColorValue color = colors[v];

            if (color == Color::white()) {
                vis.tree_edge(*ei, g);
                colors[v] = Color::gray();
                vis.discover_node(v, g);
                queue.push_back(v);
            }
        }

        colors[u] = Color::black();
    }
}

#endif //ALOGDAT_LABYRINTH_BREADTHFIRSTSEARCH_H
