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

        it = m_shortestPathTree.begin();

        for (; it != m_shortestPathTree.end(); ++it) {
            if (*it != nullptr)
                delete *it;
        }
    }

    std::vector<const Edge*> getSPT() const {
        return m_shortestPathTree;
    }

    std::list<Node> getPathToTarget() const {
        std::list<Node> path;

        if (m_target < 0) return path;

        Node nd = m_target;

        path.push_front(nd);

        while ((nd != m_source) && (m_shortestPathTree[nd] != nullptr))
        {
            nd = m_shortestPathTree[nd]->source();
            path.push_front(nd);
        }

        return path;
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
    PriorityQueue<TCost> q(m_costToThisNode, m_graph.num_nodes());

    q.insert(m_source);
    int t = 0;

    while (!q.empty()) {
        Node nextClosestNode = q.pop();

        m_shortestPathTree[nextClosestNode] = m_frontier[nextClosestNode];

        if (nextClosestNode == m_target) return;

        typename TGraph::out_edge_iterator ei, ei_end;
        std::tie(ei, ei_end) = m_graph.out_edges(nextClosestNode);
        for (auto i = ei; i != ei_end; ++i) {
            /*
             * die Gesamtkosten zu diesem Knoten sind die Kosten des aktuellen Knotens
             * plus den Kosten der Kante welche sie verbindet.
             */
            TCost newCost = m_costToThisNode[nextClosestNode] + m_graph.get(*i);
            t = newCost*2;
            t++;
            q.change_priority((*i).target());
            // füge neu entdeckte Kanten hinzu.
            /*if (m_frontier[(*i).target()] == nullptr)
            {
                m_costToThisNode[(*i).target()] = newCost;
                q.insert((*i).target());
                m_frontier[(*i).target()] = new Edge(*i);
            }
            // relaxieren Kanten.
            else if ((newCost < m_costToThisNode[(*i).target()]) &&
                    (m_shortestPathTree[(*i).target()] == nullptr)) {
                m_costToThisNode[(*i).target()] = newCost;

                // sortiere queue neu, wenn sich die Kosten ändern.
                q.change_priority((*i).target());
                m_frontier[(*i).target()] = new Edge(*i);
            }*/
        }
    }
}

#endif //ALOGDAT_LABYRINTH_DIJKSTRA_H
