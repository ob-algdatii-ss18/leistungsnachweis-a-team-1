#ifndef ALOGDAT_LABYRINTH_GRAPHWIDGET_H
#define ALOGDAT_LABYRINTH_GRAPHWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <Graph.h>
#include "MathUtils.h"

enum class algorithm_type {
    non,
    search_astar,
    search_bfs,
    search_dijkstra
};

enum class field_type {
    planar,
    water,
    hill,
    wall
};

class GraphWidget : public QWidget {
    Q_OBJECT
public:
    using Graph_t = Graph<Vector2f, float>;
    using Node = Graph_t::node_descriptor;
    GraphWidget();

    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

    void showGraph(bool visible);
    bool isGraphVisible() const { return m_showGraph; }

    bool pointToNode(const QPoint& p, Node& nodeIndex);

    void setCurTerrain(field_type type) {
        m_curTerrain = type;
    }

    void setTargetField() { }
    void setSourceField() { }

    Graph_t::node_size_t numNodes() {
        return m_graph.num_nodes();
    }

    Graph_t::edges_size_t numEdges() {
        return m_graph.num_edges();
    }

    signals:
    void changedGraph(Graph_t& graph);

private:
    void emitChangedGraph();

private:
    Graph_t m_graph;
    bool m_showGraph;
    float m_cellWidth, m_cellHeight;
    algorithm_type m_currAlgorithm;
    Graph_t::NodeMap<field_type> m_terrain;
    field_type m_curTerrain;
    int m_numCellsX, m_numCellsY;
};


#endif //ALOGDAT_LABYRINTH_GRAPHWIDGET_H
