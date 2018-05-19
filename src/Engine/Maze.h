//
// Created by janne on 17.05.2018.
//

#ifndef ALOGDAT_LABYRINTH_MAZE_H
#define ALOGDAT_LABYRINTH_MAZE_H


#include <utility>
#include "Graph.h"

class Maze {
public:
    struct Field {
        int _x;
        int _y;
        bool _visited = false;
        bool _inShortestPath = false;

        Field(int x, int y) : _x(x), _y(y) {};

        Field() : _x(0), _y(0) {};

        void visit(){
            _visited = true;
        }

        void setInShortestPath(){
            _inShortestPath = true;
        }
    };

    Graph_base<Field*, no_property>::node_descriptor getStart();

    Graph_base<Field*, no_property>::node_descriptor getEnd();

    Graph_base<Field*, no_property> *getGraph();

    int getWidth();

    int getHeight();

    Maze(std::string serialization);


private:
    Graph_base<Field*, no_property>::node_descriptor start;
    Graph_base<Field*, no_property>::node_descriptor end;
    Graph_base<Field*, no_property> *graph;
    int height;
    int width;

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
};


#endif //ALOGDAT_LABYRINTH_MAZE_H
