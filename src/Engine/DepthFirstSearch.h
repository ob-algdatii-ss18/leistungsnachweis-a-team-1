#ifndef ALOGDAT_LABYRINTH_DEPTHFIRSTSEARCH_H
#define ALOGDAT_LABYRINTH_DEPTHFIRSTSEARCH_H

template <typename TGraph>
class Graph_depth_first_search {
private:
    enum {visited, unvisited, no_parent_assigned};

private:
    using graph_type = TGraph;
    using node_descriptor = typename TGraph::node_descriptor;
    const graph_type & m_graph;

    /**
     * contains the indexes of all the nodes that are visited as the search
     * progresses.
     */
    std::vector<node_descriptor> m_visited;

    /**
     * this holds the route taken to the target.
     */
    std::vector<node_descriptor> m_route;

    // the source and target node indices
    node_descriptor m_source, m_target;

    // true if path to the target has been found.
    bool m_found;

public:
    Graph_depth_first_search(const graph_type& graph,
                                node_descriptor source, node_descriptor target) : m_graph(graph), m_source(source), m_target(target), m_found(false), m_visited(m_graph.num_nodes(), unvisited),
                                                                                  m_route(m_graph.num_nodes(), no, no_parent_assigned)
    {
        m_found = find();
    }

    bool search() {

    }

    std::list<node_descriptor> path_to_target() const;
};

#endif //ALOGDAT_LABYRINTH_DEPTHFIRSTSEARCH_H
