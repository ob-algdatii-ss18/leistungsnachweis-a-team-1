#include "GraphTest.h"

#include <Graph.h>

TEST_F(GraphTest, IntegerRangeTest) {
    auto it = Integer_range<int>(0, 100);

    for (auto i : it) {
        std::cout << i << std::endl;
    }
}

TEST_F(GraphTest, AddNode) {
    Weighted_graph<double> graph;
    Weighted_graph<double>::node_descriptor v = graph.add_node();
    Weighted_graph<double>::node_descriptor u = graph.add_node();
    unsigned int i1 = 0;
    unsigned int i2 = 1;
    ASSERT_EQ(std::make_pair(v, u), std::make_pair(i1, i2));
}

TEST_F(GraphTest, AddEdge) {
    Graph_base<double, double> g;
    g.add_node(10.0);
    Weighted_graph<double> graph;

    Weighted_graph<double>::node_descriptor v = graph.add_node();
    Weighted_graph<double>::node_descriptor u = graph.add_node();

    Weighted_graph<double>::edge_descriptor e1 = graph.add_edge(v, u, 10.0);

    unsigned int i1 = 0;
    unsigned int i2 = 1;
    ASSERT_EQ(std::make_pair(e1.source(), e1.target()), std::make_pair(i1, i2));
}

TEST_F(GraphTest, RemoveNodes) {
    Weighted_graph<double> graph;

    Weighted_graph<double>::node_descriptor v = graph.add_node();
    Weighted_graph<double>::node_descriptor u = graph.add_node();
    Weighted_graph<double>::node_descriptor u1 = graph.add_node();
    Weighted_graph<double>::node_descriptor u2 = graph.add_node();
    Weighted_graph<double>::node_descriptor u3 = graph.add_node();

    Weighted_graph<double>::edge_descriptor e1 = graph.add_edge(v, u, 10.0);
    graph.add_edge(u, v, 14.0);
    graph.add_edge(u1, u2, 10.0);

    graph.remove_node(v);
}

TEST_F(GraphTest, RemoveEdge) {
    using Graph_t = Graph_base<double, double>;
    Graph_t graph;

    Graph_t::node_descriptor v = graph.add_node(10);
    Graph_t::node_descriptor u = graph.add_node(20);
    Graph_t::node_descriptor u1 = graph.add_node(12);

    Graph_t::edge_descriptor e1 = graph.add_edge(v, u, 10.0);
    graph.add_edge(u, v, 14.0);

    graph.remove_edge()

    auto ni = graph.nodes();

    auto i = ni.first;

    for(;i != ni.second; ++i) {
        std::cout << graph.get(*i) << std::endl;
    }

    ASSERT_THAT(graph.num_nodes(), 3);
}

TEST_F(GraphTest, OutputNodes) {
    Weighted_graph<double> graph;

    Weighted_graph<double>::node_descriptor v = graph.add_node();
    Weighted_graph<double>::node_descriptor u = graph.add_node();
    Weighted_graph<double>::node_descriptor u1 = graph.add_node();
    Weighted_graph<double>::node_descriptor u2 = graph.add_node();
    Weighted_graph<double>::node_descriptor u3 = graph.add_node();
    graph.add_node();

    Weighted_graph<double>::edge_descriptor e1 = graph.add_edge(v, u, 10.0);
    graph.add_edge(u, v, 14.0);
    graph.add_edge(u1, u2, 10.0);

    auto ni = graph.nodes();

    std::copy(ni.first, ni.second, std::ostream_iterator<Weighted_graph<double>::node_descriptor>{
            std::cout, "\n"}
    );

    ASSERT_THAT(graph.num_nodes(), 6);
}

TEST_F(GraphTest, OutputEdges) {
    Weighted_graph<double> graph;

    Weighted_graph<double>::node_descriptor v = graph.add_node();
    Weighted_graph<double>::node_descriptor u = graph.add_node();
    Weighted_graph<double>::node_descriptor u1 = graph.add_node();
    Weighted_graph<double>::node_descriptor u2 = graph.add_node();
    Weighted_graph<double>::node_descriptor u3 = graph.add_node();
    graph.add_node();

    Weighted_graph<double>::edge_descriptor e1 = graph.add_edge(v, u, 10.0);
    graph.add_edge(u, v, 14.0);
    graph.add_edge(u1, u2, 10.0);

    auto ei = graph.edges();

    std::copy(ei.first, ei.second, std::ostream_iterator<Weighted_graph<double>::edge_descriptor>{
            std::cout, "\n"}
    );

    ASSERT_THAT(graph.num_edges(), 3);
}

TEST_F(GraphTest, GetNodeProperty) {
    using Graph_t = Graph_base<double, double>;
    Graph_t graph;

    Graph_t::node_descriptor v = graph.add_node(10);
    Graph_t::node_descriptor u = graph.add_node(20);
    Graph_t::node_descriptor u1 = graph.add_node(12);

    Graph_t::edge_descriptor e1 = graph.add_edge(v, u, 10.0);
    graph.add_edge(u, v, 14.0);

    auto ni = graph.nodes();

    auto i = ni.first;

    for(;i != ni.second; ++i) {
        std::cout << graph.get(*i) << std::endl;
    }

    ASSERT_THAT(graph.num_nodes(), 3);
}

TEST_F(GraphTest, GetEdgeProperty) {

}
