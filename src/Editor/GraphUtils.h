#ifndef ALOGDAT_LABYRINTH_GRAPHUTILS_H
#define ALOGDAT_LABYRINTH_GRAPHUTILS_H

#include "config.h"


struct GraphGridHelper {
    /**
     *
     * @tparam TGraph
     * @param graph
     * @param width bound
     * @param height bound
     * @param numCellsX
     * @param numCellsY
     */
    template <typename TGraph>
    static void Create(TGraph&& graph, std::vector<field_type>& terrain, int width, int height, int numCellsX, int numCellsY) {
        float cellWidth = static_cast<float>(width) / static_cast<float>(numCellsX);
        float cellHeight = static_cast<float>(height) / static_cast<float>(numCellsY);
        float cellMidX = cellWidth/2;
        float cellMidY = cellHeight/2;
        terrain.assign(Config::NumCellsX * Config::NumCellsY, field_type::planar);

        // add nodes to the graph
        for (int row = 0; row < numCellsY; ++row) {
            for (int col = 0; col < numCellsX; ++col) {
                graph.add_node(Vector2f(cellMidX + (col*cellWidth),
                               cellMidY + (row*cellHeight)));
            }
        }

        for (int row = 0; row < numCellsY; ++row) {
            for (int col = 0; col < numCellsX; ++col) {
                AddAllNeighbours(std::forward<TGraph>(graph), terrain, row, col, numCellsX, numCellsY);
            }
        }

        printGraphDebugInfo(std::forward<TGraph>(graph));
    }

    static bool IsValidNeighbour(int x, int y, std::vector<field_type>& fields, int numCellsX, int numCellsY) {
        return !((x < 0) || (x >= numCellsX) || (y < 0) || (y >= numCellsY) || (fields[y*numCellsX+x]==field_type::wall));
    }

    template <typename TGraph>
    static void printGraphDebugInfo(TGraph&& graph) {
        auto nodeit = graph.nodes();

        for (auto i = nodeit.first; i != nodeit.second; ++i) {
            Vector2f vec = graph.get(*i);
            qDebug() << *i << ": (" << vec.x << "/" << vec.y << ")";
        }

        auto edgeit = graph.edges();

        for (auto ei = edgeit.first; ei != edgeit.second; ++ei) {
            qDebug() << (*ei).source() << (*ei).target();
        }

        qDebug() << "Number of Nodes:" << graph.num_nodes();
        qDebug() << "Number of Edges:" << graph.num_edges();
    }

    template<typename TGraph>
    static void AddAllNeighbours(TGraph &&graph, std::vector<field_type>& fields, int row, int col, int numCellsX, int numCellsY) {
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j<2; ++j) {
                // skip if current node.
                if ((i==0) && (j==0)) continue;

                int nodeX = col+j;
                int nodeY = row+i;

                if (IsValidNeighbour(nodeX, nodeY, fields, numCellsX, numCellsY)) {
                    Vector2f vec1 = graph.get(row*numCellsX+col);
                    Vector2f vec2 = graph.get(nodeY*numCellsX + nodeX);

                    float dist = Distance(vec1, vec2);

                    graph.add_edge(row*numCellsX+col,
                    nodeY*numCellsX + nodeX,
                    dist);
                }
            }
        }
    }

    /**
     * Draws a graph.
     * @tparam TGraph The type of the graph.
     * @param painter The QT Painter to draw the graph, usually called in the paintEvent() function.
     * @param graph The Graph to be drawn.
     */
    template<typename TGraph>
    static void Draw(QPainter& painter, TGraph&& graph)  {
        if (graph.num_nodes() == 0) return;

        auto nodeit = graph.nodes();
        auto edgeit = graph.edges();

        painter.setRenderHint(QPainter::Antialiasing, true);
        QColor nodesColor(0, 255, 0);
        QPen pen(Qt::gray, 1);
        painter.setPen(pen);

        for (auto ei = edgeit.first; ei != edgeit.second; ++ei) {
            Vector2f vec = graph.get((*ei).source());
            Vector2f vec1 = graph.get((*ei).target());
            painter.drawLine(vec.x, vec.y, vec1.x, vec1.y);
        }

        painter.setPen(Qt::NoPen);
        for (auto i = nodeit.first; i != nodeit.second; ++i) {
            Vector2f vec = graph.get(*i);
            QBrush brush(nodesColor);
            painter.setBrush(brush);
            painter.drawEllipse(QPointF(vec.x, vec.y), Config::NodeRadius, Config::NodeRadius);
        }
    }
};

#endif //ALOGDAT_LABYRINTH_GRAPHUTILS_H
