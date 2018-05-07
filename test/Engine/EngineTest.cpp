#include <Graph.h>
#include <Timer.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "EngineTest.h"

TEST_F(EngineTest, TimerStart) {
    stopwatch watch;
    watch.start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    watch.stop();
    EXPECT_DOUBLE_EQ(std::round(watch.elapsedTime<double, centi>()/100.0), 3);
}

TEST_F(EngineTest, AddNode) {
    Weighted_graph<double> graph;
    Weighted_graph<double>::node_descriptor v = graph.add_node();
    Weighted_graph<double>::node_descriptor u = graph.add_node();
    ASSERT_THAT(u, 1);
    ASSERT_THAT(v, 0);
}

TEST_F(EngineTest, AddEdge) {
    Graph_base<double, double> g;
    g.add_node(10.0);
    Weighted_graph<double> graph;

    Weighted_graph<double>::node_descriptor v = graph.add_node();
    Weighted_graph<double>::node_descriptor u = graph.add_node();

    Weighted_graph<double>::edge_descriptor e1 = graph.add_edge(v, u, 10.0);
    std::cout << e1.source() << ", " << e1.target() << std::endl;
    ASSERT_THAT(e1, std::make_pair(v, u));
}

TEST_F(EngineTest, RemoveNodes) {
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

    ASSERT_THAT(e1, std::make_pair(v, u));
}

TEST_F(EngineTest, RemoveEdge) {

}

TEST_F(EngineTest, OutputNodes) {

}

TEST_F(EngineTest, OutputEdges) {
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

    auto ei = graph.nodes();

    std::copy(ei.first, ei.second, std::ostream_iterator<Weighted_graph<double>::node_descriptor >{
            std::cout, "\n"}
            );
}

TEST_F(EngineTest, IntegerRangeTest) {
    auto it = Integer_range<int>(0, 11);

    for (auto i : it) {
        std::cout << i << std::endl;
    }
}

TEST_F(EngineTest, GetNodeProperty) {
    using MyGraph_t = Graph_base<double, double>;
    MyGraph_t g;

    g.add_node(10);
    g.add_node(12);
    g.add_node(30);
    g.add_node(40);
    g.add_node(50);

    g.add_edge(0, 1, 20);
    g.add_edge(0, 2, 30);

    g.remove_node(3);

    auto ni = g.nodes();

    /*std::copy(ni.first, ni.second, std::ostream_iterator<MyGraph_t::node_descriptor>{
        std::cout, "\n"
    });*/

    auto it = ni.first;

    for (; it != ni.second; ++it) {
        std::cout << g.get(*it) << std::endl;
    }

}