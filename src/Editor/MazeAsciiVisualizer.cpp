//
// Created by janne on 18.05.2018.
//

#include <Maze.h>
#include <QtCore/QString>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QPlainTextEdit>
#include "MazeAsciiVisualizer.h"


MazeAsciiVisualizer::MazeAsciiVisualizer(QPlainTextEdit *textField) {
    this->textField = textField;
    this->textField->setReadOnly(true);
    this->textField->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
}

void MazeAsciiVisualizer::visualize(Maze *maze) {
    this->textField->setPlainText(QString::fromStdString(getVisualizationString(maze)));
}

std::string MazeAsciiVisualizer::getVisualizationString(Maze *maze) {
    auto visualizationMatrix = getAsVisualizationMatrix(maze);
    std::string result = "";
    for (int y = 0; y < maze->getHeight(); y++) {
        for (int i = 0; i < VISUALIZATION_SCALE_Y; i++) {
            for (int x = 0; x < maze->getWidth(); x++) {
                for (int j = 0; j < VISUALIZATION_SCALE_X; j++) {
                    result += visualizationMatrix[y][x];
                }
            }
            result += VISUALIZATION_NEW_LINE;
        }
    }
    return result;
}

char **MazeAsciiVisualizer::getAsVisualizationMatrix(Maze *maze) {
    auto visualizationMatrix = new char *[maze->getHeight()];
    for (int y = 0; y < maze->getHeight(); y++) {
        visualizationMatrix[y] = new char[maze->getWidth()];
        for (int x = 0; x < maze->getWidth(); x++) {
            visualizationMatrix[y][x] = VISUALIZATION_WALL;
        }
    }
    fillVisualizationMatrix(maze, visualizationMatrix, maze->getStart());
    return visualizationMatrix;
}

void MazeAsciiVisualizer::fillVisualizationMatrix(Maze *maze, char **matrix, Graph_base<Maze::Field*, no_property>::node_descriptor fieldPointer) {
    auto field = maze->getGraph()->get(fieldPointer);
    if (matrix[field->_y][field->_x] == VISUALIZATION_WALL) {
        if (fieldPointer == maze->getStart()) {
            matrix[field->_y][field->_x] = VISUALIZATION_START;
        } else if (fieldPointer == maze->getEnd()) {
            matrix[field->_y][field->_x] = VISUALIZATION_END;
        } else if (field->_inShortestPath) {
            matrix[field->_y][field->_x] = VISUALIZATION_FIELD_IN_SHORTEST_PATH;
        } else if (field->_visited) {
            matrix[field->_y][field->_x] = VISUALIZATION_FIELD_VISITED;
        } else {
            matrix[field->_y][field->_x] = VISUALIZATION_FIELD_UNVISITED;
        }

        for (auto const edge : maze->getGraph()->out_edge_list(fieldPointer)) {
            fillVisualizationMatrix(maze, matrix, edge._to);
        }
    }
}