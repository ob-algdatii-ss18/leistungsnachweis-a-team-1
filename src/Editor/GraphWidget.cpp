#include <QtGui/QPainter>
#include <QLayout>
#include "GraphWidget.h"
#include <QDebug>
#include "GraphUtils.h"
#include "config.h"

GraphWidget::GraphWidget() : m_showGraph(true), m_curTerrain(field_type::planar) {
    QSize size = this->size();
    setFixedSize(size.width(), size.height());
    m_cellWidth = static_cast<float>(size.width()) / Config::NumCellsX;
    m_cellHeight = static_cast<float>(size.height()) / Config::NumCellsY;
    m_numCellsX = Config::NumCellsX;
    m_numCellsY = Config::NumCellsY;
    GraphGridHelper::Create(m_graph, m_terrain, size.width(), size.height(), Config::NumCellsX, Config::NumCellsY);
}

void GraphWidget::paintEvent(QPaintEvent * event) {
    QWidget::paintEvent(event);
    QPainter painter(this);

    auto nodeiter = m_graph.nodes();

    QColor fieldBackground;
    QPen pen(QColor(0,0,0), 3);
    painter.setPen(pen);

    for (auto ni = nodeiter.first; ni != nodeiter.second; ++ni)
    {
        int left = static_cast<int>(m_graph.get(*ni).x - m_cellWidth/2.0f);
        int top = static_cast<int>(m_graph.get(*ni).y - m_cellHeight/2.0f);
        int right = static_cast<int>(m_graph.get(*ni).x + m_cellWidth/2.0f);
        int bottom = static_cast<int>(m_graph.get(*ni).y + m_cellHeight/2.0f);

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
                fieldBackground = QColor(31,96,157);
                break;
            default:
                fieldBackground = Qt::red;
        }
        QBrush brush(fieldBackground);

        painter.fillRect(left, top, right-left, bottom-top, brush);
        painter.drawRect(left, top, right-left, bottom-top);
    }

    if (m_showGraph)
        GraphGridHelper::Draw(painter, m_graph);
}

void GraphWidget::showGraph(bool visible) {
    m_showGraph = visible;
    repaint();
}

void GraphWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);

    if (event->button() == Qt::LeftButton) {
        Node node = 0;
        pointToNode(event->pos(), node);
        m_terrain[node] = m_curTerrain;
        if (m_terrain[node] == field_type::wall) {
            // delete all incoming and outgoing edges from the selected node.
            m_graph.clear_node(node);
        }
        else {
            if (m_graph.out_degree(node) == 0) {
                // reset edges
                int row = node / m_numCellsY;
                int col = node - (row*m_numCellsY);
                GraphGridHelper::AddAllNeighbours(std::forward<Graph_t>(m_graph), m_terrain, row, col, m_numCellsX, m_numCellsY);
            }
        }
        emitChangedGraph();
        repaint();
    }
}

bool GraphWidget::pointToNode(const QPoint& p, Graph_t::node_descriptor & nodeIndex) {
        auto x = static_cast<unsigned int>(p.x()/m_cellWidth);
    auto y = static_cast<unsigned int>(p.y()/m_cellHeight);

    nodeIndex = y * m_numCellsX + x;

    return true;
}

void GraphWidget::emitChangedGraph() {
    emit changedGraph(m_graph);
}

