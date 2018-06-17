#ifndef ALOGDAT_LABYRINTH_ASTAR_H
#define ALOGDAT_LABYRINTH_ASTAR_H

template <typename TGraph, typename heuristic>
class AStar_Search {
private:
    const TGraph& m_graph;

    std::vector<double> m_gcosts;
    std::vector<double> m_fcosts;


    int m_source;
    int m_target;

    void search();

public:
    //AStar_Search(TGraph& graph, int source, int target) : m_graph(graph), m_shortestPathTree()
};

#endif //ALOGDAT_LABYRINTH_ASTAR_H
