//
// Created by janne on 18.05.2018.
//

#ifndef ALOGDAT_LABYRINTH_MAZEASCIIVISUALIZER_H
#define ALOGDAT_LABYRINTH_MAZEASCIIVISUALIZER_H

#include <Maze.h>

class MazeAsciiVisualizer {
    enum VisualizationConstants {
        VISUALIZATION_SCALE_X = 3,
        VISUALIZATION_SCALE_Y = 2,
        VISUALIZATION_FIELD_UNVISITED = ' ',
        VISUALIZATION_FIELD_VISITED = '.',
        VISUALIZATION_FIELD_IN_SHORTEST_PATH = 'o',
        VISUALIZATION_WALL = '#',
        VISUALIZATION_START = 'S',
        VISUALIZATION_END = 'E',
        VISUALIZATION_NEW_LINE = '\n',
    };
    QPlainTextEdit *textField;

public:
    MazeAsciiVisualizer(QPlainTextEdit *textField);

    void visualize(Maze *maze);

private:
    std::string getVisualizationString(Maze *maze);

    char **getAsVisualizationMatrix(Maze *maze);

    void fillVisualizationMatrix(Maze *maze, char **matrix,
                                 Graph_base<Maze::Field*, no_property>::node_descriptor fieldPointer);
};


#endif //ALOGDAT_LABYRINTH_MAZEASCIIVISUALIZER_H
