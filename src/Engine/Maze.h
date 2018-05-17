//
// Created by janne on 17.05.2018.
//

#ifndef ALOGDAT_LABYRINTH_MAZE_H
#define ALOGDAT_LABYRINTH_MAZE_H


#include <utility>
#include "Graph.h"

class Maze {
    struct Field {
        int _x;
        int _y;
        bool _visited = false;

        Field(int x, int y) : _x(x), _y(y) {};

        Field() : _x(0), _y(0) {};
    };

    Field start;
    Field end;
    Graph_base<Field, no_property> *graph;

    //serialization protocol
    /* Example:
     * #############
     * #S# #   ###E#
     * #     #     #
     * #############
     * */
    enum SerializationChars {
        FIELD = ' ',
        START = 'S',
        WALL = '#',
        END = 'E',
        NEW_LINE = '\n'
    };

public:

    Maze(std::string serialization);
};


#endif //ALOGDAT_LABYRINTH_MAZE_H
