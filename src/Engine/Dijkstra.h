#ifndef ALOGDAT_LABYRINTH_DIJKSTRA_H
#define ALOGDAT_LABYRINTH_DIJKSTRA_H

#include <LowPriorityQueue.h>

template <typename TGraph, typename TCost>
void relax_edge(typename TGraph::edge_descriptor edge, std::vector<TCost>& cost) {
    TCost newCost = cost[edge.source()] + *edge._property;
    if (cost[edge.target()] > newCost)
        cost[edge.target()] = newCost;
}

template <typename TGraph, typename TCost = double>
struct Dijkstra {
    using Edge = typename TGraph::edge_descriptor;
    using Node = typename TGraph::node_descriptor;
    using cost_t = TCost;

    Dijkstra(TGraph& graph, const Node source, const Node target)
            : m_graph(graph), m_costToThisNode(graph.num_nodes()),
              m_shortestPathTree(graph.num_nodes()),
              m_frontier(graph.num_nodes()),
              m_source(source),
              m_target(target) {
        search();
    }

    ~Dijkstra() {
        typename std::vector<const Edge*>::iterator it = m_frontier.begin();
        for (; it != m_frontier.end(); ++it)
            if (*it != nullptr)
                delete *it;
    }

    std::list<Node> getPathToTarget() const {
        return std::list<Node>();
    }
    cost_t getCostToTarget() const { return m_costToThisNode[m_target]; }
    cost_t getCostToNode(Node n) const { return m_costToThisNode[n]; }

private:
    TGraph& m_graph;
    std::vector<TCost> m_costToThisNode;
    std::vector<const Edge*> m_shortestPathTree;
    std::vector<const Edge*> m_frontier;
    Node m_source;
    Node m_target;


private:
    void search();
};


template<typename TGraph, typename TCost>
void Dijkstra<TGraph, TCost>::search() {
    PriorityQueue<TCost> pq(m_costToThisNode, m_graph.num_nodes());

    pq.insert(m_source);

    while (!pq.empty()) {
        Node nextClosestNode = pq.pop();

        if (nextClosestNode == m_target) return;

        typename TGraph::out_edge_iterator ei, ei_end;
        std::tie(ei, ei_end) = m_graph.out_edges(nextClosestNode);
        for (auto i = ei; i != ei_end; ++i) {
            TCost newCost = m_costToThisNode[nextClosestNode] + m_graph.get(*i);
            if (m_frontier[(*i).target()] == nullptr)
            {
                m_costToThisNode[(*i).target()] = newCost;
                pq.insert((*i).target());
                m_frontier[(*i).target()] = new Edge(*i);
            }
            else
                relax_edge<TGraph>(*i, m_costToThisNode);
        }
    }
}

#endif //ALOGDAT_LABYRINTH_DIJKSTRA_H
