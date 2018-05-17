//
// Created by janne on 17.05.2018.
//

#include <iostream>
#include <climits>
#include "Maze.h"


Maze::Maze(std::string serialization) {
    int width = serialization.find(NEW_LINE);
    int height = (serialization.length() + 1) / (width + 1);

    graph = new Graph_base<Field, no_property>();
    auto fieldMatrix = new Graph_base<Field, no_property>::node_descriptor *[height];
    fieldMatrix[0] = new Graph_base<Field, no_property>::node_descriptor[width];
    int y = 0;
    int x = 0;
    const Graph_base<Field, no_property>::node_descriptor wall = UINT_MAX;

    for (std::string::iterator it = serialization.begin(); it != serialization.end(); ++it) {
        auto field = graph->add_node(Field(x, y));
        switch (*it) {
            case START:
                start = graph->get(field);
                fieldMatrix[y][x] = field;
                break;
            case END:
                end = graph->get(field);
                fieldMatrix[y][x] = field;
                break;
            case FIELD:
                fieldMatrix[y][x] = field;
                break;
            case WALL:
                fieldMatrix[y][x] = wall;
                break;
            case NEW_LINE:
                y++;
                x = -1;
                fieldMatrix[y] = new Graph_base<Field, no_property>::node_descriptor[width];
                break;
        }
        x++;
    }


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (fieldMatrix[y][x] != wall) {
                if (y > 0 && fieldMatrix[y - 1][x] != wall) {
                    graph->add_edge(fieldMatrix[y][x], fieldMatrix[y - 1][x]);
                    //graph->add_edge(fieldMatrix[y - 1][x], fieldMatrix[y][x]);
                }
                if (y < height - 1 && fieldMatrix[y + 1][x] != wall) {
                    graph->add_edge(fieldMatrix[y][x], fieldMatrix[y + 1][x]);
                    //graph->add_edge(fieldMatrix[y + 1][x], fieldMatrix[y][x]);
                }

                if (x > 0 && fieldMatrix[y][x - 1] != wall) {
                    graph->add_edge(fieldMatrix[y][x], fieldMatrix[y][x - 1]);
                    //graph->add_edge(fieldMatrix[y][x - 1], fieldMatrix[y][x]);
                }
                if (y < width - 1 && fieldMatrix[y][x + 1] != wall) {
                    graph->add_edge(fieldMatrix[y][x], fieldMatrix[y][x + 1]);
                    //graph->add_edge(fieldMatrix[y][x + 1], fieldMatrix[y][x]);
                }
            }
        }
    }
}
