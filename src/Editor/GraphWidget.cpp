#include <QtGui/QPainter>
#include <QLayout>
#include "GraphWidget.h"
#include <QDebug>
#include <Timer.h>
#include <Dijkstra.h>
#include "GraphUtils.h"
#include "config.h"
#include "BreadthFirstSearch.h"

template <typename Graph>
struct MyBFSVisitor {
    using Node = typename Graph::node_descriptor;
    using Edge = typename Graph::edge_descriptor;

    std::list<Node>& m_path;
    std::list<Edge> m_spanningTree;
    std::vector<Node> m_route;
    Node m_target;
    bool m_found;

    explicit MyBFSVisitor(Graph &g, Node target, std::list<Node>& path) : m_path(path), m_route(g.num_nodes()), m_target(target), m_found(false) { }

    void initialize_node(Node u, Graph& g) {
        qDebug() << u << " initialized with white color.";
    }

    void discover_node(Node u, Graph&) {
        qDebug() << u << " discovered";
        if (u == m_target);
    }

    void tree_edge(Edge e, Graph& g) {
        if (e.target() == m_target && !m_found) {
            m_found = true;
            return;
        }
        m_route.push_back(e.source());
        qDebug()  << e.source() << e.target();
        m_path.push_back(e.target());
        m_spanningTree.push_back(e);
    }
};

GraphWidget::GraphWidget(int xNum, int yNum) : m_showGraph(false), m_cellWidth(0), m_cellHeight(0),
                                               m_currAlgorithm(algorithm_type::none),
                                               m_curTerrain(field_type::planar),
                                               m_sourceField(0), m_targetField(0) {
    QSize size = this->size();
    setFixedSize(size.width(), size.height());
    createGraph(xNum, yNum);
}

void GraphWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    auto nodeiter = m_graph.nodes();

    QColor fieldBackground;
    QPen pen(QColor(0, 0, 0), 3);
    painter.setPen(pen);

    for (auto ni = nodeiter.first; ni != nodeiter.second; ++ni) {
        int left = static_cast<int>(m_graph.get(*ni).x - m_cellWidth / 2.0f);
        int top = static_cast<int>(m_graph.get(*ni).y - m_cellHeight / 2.0f);
        int right = static_cast<int>(m_graph.get(*ni).x + m_cellWidth / 2.0f);
        int bottom = static_cast<int>(m_graph.get(*ni).y + m_cellHeight / 2.0f);


        switch (m_terrain[*ni]) {
            case field_type::wall:
                fieldBackground = QColor(110, 110, 110);
                break;
            case field_type::hill:
                fieldBackground = QColor(76, 48, 7);
                break;
            case field_type::planar:
                fieldBackground = QColor(53, 57, 60);
                break;
            case field_type::water:
                fieldBackground = QColor(31, 96, 157);
                break;
            default: break;
        }

        if (*ni == m_sourceField)
            fieldBackground = QColor(0, 100, 0);
        if (*ni == m_targetField)
            fieldBackground = QColor(100, 0, 0);
        QBrush brush(fieldBackground);

        painter.fillRect(left, top, right - left, bottom - top, brush);
        painter.drawRect(left, top, right - left, bottom - top);
    }

    if (m_showGraph)
        GraphGridHelper::Draw(painter, m_graph);

    // Draw path to target field.
    if (!m_path.empty()) {
        painter.setPen(QPen(QColor(0, 255, 0), 3));
        auto it = m_path.begin();
        auto next = it; ++next;

        for (; next != m_path.end(); ++it, ++next) {
            Vector2f vec1 = m_graph.get(*it);
            Vector2f vec2 = m_graph.get(*next);
            painter.drawLine(vec1.x, vec1.y, vec2.x, vec2.y);
        }

    }
}

void GraphWidget::showGraph(bool visible) {
    m_showGraph = visible;
    repaint();
}

void GraphWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);

    Node node = 0;
    pointToNode(event->pos(), node);
    if (event->button() == Qt::LeftButton) {
        if ((m_curTerrain == field_type::target) || (m_curTerrain == field_type::source)) {
            switch (m_curTerrain) {
                case field_type::source:
                    m_sourceField = node; break;
                case field_type::target:
                    m_targetField = node; break;
                default:
                    break;
            }
        }
        else {
            updateGraphFromTerrain(node, m_curTerrain);
            emitChangedGraph();
        }
        updateAlgorithm();
        qDebug() << m_sourceField << m_targetField;
        repaint();
    }
}

bool GraphWidget::pointToNode(const QPoint &p, Graph_t::node_descriptor &nodeIndex) {
    auto x = static_cast<unsigned int>(p.x() / m_cellWidth);
    auto y = static_cast<unsigned int>(p.y() / m_cellHeight);

    nodeIndex = y * m_numCellsX + x;

    return true;
}

void GraphWidget::emitChangedGraph() {
    emit changedGraph(m_graph);
}

void GraphWidget::createGraph(int numX, int numY) {
    QSize size = this->size();
    m_cellWidth = static_cast<float>(size.width()) / numX;
    m_cellHeight = static_cast<float>(size.height()) / numY;
    m_numCellsX = numX;
    m_numCellsY = numY;
    GraphGridHelper::Create(m_graph, m_terrain, size.width(), size.height(), numX, numY);
    m_targetField = m_graph.num_nodes() - 1;
    emitChangedGraph();
    repaint();
}

void GraphWidget::createPathAStar() {
    m_currAlgorithm = algorithm_type::search_astar;
    m_path.clear();

    stopwatch watch;
    watch.start();

    watch.stop();
    m_elapsedTime = watch.elapsedTime();
    repaint();
}

void GraphWidget::createPathBFS() {
    m_currAlgorithm = algorithm_type::search_bfs;
    m_path.clear();

    stopwatch watch;
    watch.start();
    breadth_first_search(m_graph, m_sourceField, MyBFSVisitor<Graph_t>(m_graph, m_targetField, m_path));
    watch.stop();
    m_elapsedTime = watch.elapsedTime();

    m_costToTarget = 0.0;
    repaint();
}

void GraphWidget::createPathDijkstra() {
    m_currAlgorithm = algorithm_type::search_dijkstra;
    m_path.clear();

    stopwatch watch;
    watch.start();

    Dijkstra<Graph_t, float> dijk(m_graph, m_sourceField, m_targetField);
    m_path = dijk.getPathToTarget();

    watch.stop();
    m_elapsedTime = watch.elapsedTime();
    repaint();
}

float GraphWidget::getTerrainCost(const field_type field) {
    float cost = 0.0;

    switch(field) {
        case field_type::planar:
            cost = Config::PlanarCost;
            break;
        case field_type::water:
            cost = Config::WaterCost;
            break;
        case field_type::hill:
            cost = Config::HillCost;
            break;
        default:
            cost = Config::PlanarCost;
    }

    return cost;
}

void GraphWidget::updateGraphFromTerrain(Node node, field_type field) {
    m_terrain[node] = m_curTerrain;

    if (m_terrain[node] == field_type::wall) {
        // delete all incoming and outgoing edges from the selected node.
        m_graph.clear_node(node);
    } else {
        if (m_graph.out_degree(node) == 0) {
            // reset edges
            int row = node / m_numCellsY;
            int col = node - (row * m_numCellsY);
            GraphGridHelper::AddAllNeighbours(std::forward<Graph_t>(m_graph), m_terrain, row, col, m_numCellsX,
                                              m_numCellsY);
        }
    }
    GraphGridHelper::WeightGraphEdges(m_graph, node, getTerrainCost(field));
}

void GraphWidget::updateAlgorithm() {
    switch(m_currAlgorithm) {
        case algorithm_type::none:
            break;
        case algorithm_type::search_astar:
            createPathAStar();
            break;
        case algorithm_type::search_bfs:
            createPathBFS();
            break;
        case algorithm_type::search_dijkstra:
            createPathDijkstra();
            break;
        default: break;
    }
}

