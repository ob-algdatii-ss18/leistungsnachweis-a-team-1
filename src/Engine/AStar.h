#ifndef ALOGDAT_LABYRINTH_ASTAR_H
#define ALOGDAT_LABYRINTH_ASTAR_H

template <typename TGraph, typename TCost, typename heuristic>
class AStar_Search {
    using Node = typename TGraph::node_descriptor;
    using Edge = typename TGraph::edge_descriptor;

private:
    TGraph& m_graph;

    std::vector<const Edge*> m_shortestPathTree;
    std::vector<TCost> m_fcosts;
    std::vector<TCost> m_gcosts;

    std::vector<const Edge*> m_frontier;

    Node m_source;
    Node m_target;

    void search();

public:
    AStar_Search(TGraph& graph, const Node source, const Node target)
            : m_graph(graph), m_shortestPathTree(m_graph.num_nodes()),
              m_fcosts(graph.num_nodes(), 0.0f), m_gcosts(graph.num_nodes(), 0.0f),
              m_frontier(graph.num_nodes()),
              m_source(source), m_target(target)
    {
        search();
    }

    std::vector<const Edge*> getSPT() const { return m_shortestPathTree; }

    float getCostToTarget() const { return m_gcosts[m_target];}

    std::list<Node> getPathToTarget() const {
        std::list<Node> path;

        if (m_target < 0) return path;

        Node n = m_target;

        path.push_front(n);

        while ((n!= m_source) && (m_shortestPathTree[n] != nullptr))
        {
            n = m_shortestPathTree[n]->source();
            path.push_front(n);
        }

        return path;
    }
};

template <typename TGraph, typename TCost, typename heuristic>
void AStar_Search<TGraph, TCost, heuristic>::search() {
    PriorityQueue<float> q(m_fcosts, m_graph.num_nodes());

    q.insert(m_source);

    while (!q.empty())
    {
        Node closestNode = q.pop();

        m_shortestPathTree[closestNode] = m_frontier[closestNode];

        if (closestNode == m_target) return;


        typename TGraph::out_edge_iterator ei, ei_end;
        std::tie(ei, ei_end) = m_graph.out_edges(closestNode);
        for (auto i = ei; i != ei_end; ++i) {
            // berechne den heuristischen Wert von akutellen Knoten zum Zielknoten.
            double hcost = heuristic::get(m_graph, m_target, (*i).target());

            // berechne die echten Kosten vom source zu diesem Knoten.
            double gcost = m_gcosts[closestNode] + m_graph.get(*i);

            // füge neu entdeckte Kanten hinzu.
            if (m_frontier[(*i).target()] == nullptr)
            {
                m_fcosts[(*i).target()] = gcost + hcost;
                m_gcosts[(*i).target()] = gcost;

                q.insert((*i).target());
                m_frontier[(*i).target()] = new Edge(*i);
            }
                // relaxieren Kanten.
            else if ((gcost < m_gcosts[(*i).target()]) &&
                     (m_shortestPathTree[(*i).target()] == nullptr)) {
                m_fcosts[(*i).target()] = gcost + hcost;
                m_gcosts[(*i).target()] = gcost;

                // sortiere queue neu, wenn sich die Kosten ändern.
                q.change_priority((*i).target());
                m_frontier[(*i).target()] = new Edge(*i);
            }
        }
    }
}

#endif //ALOGDAT_LABYRINTH_ASTAR_H
