#ifndef ALGODAT_GRAPH_H
#define ALGODAT_GRAPH_H

#include <utility>
#include <vector>
#include <set>

class Graph {
public:
    using node_descriptor = int;
    using edge_descriptor = std::pair<int, int>;

    /**
     * Konstruktoren, Zuweisung
     */


    /**
     * Methoden
     */

private:
    std::vector<node_descriptor> m_nodes;
    std::vector<std::set<edge_descriptor>> m_edges;
};


#endif //ALGODAT_GRAPH_H
