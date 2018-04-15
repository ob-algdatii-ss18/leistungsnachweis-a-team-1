//
// Created by nikita hans on 15/04/2018.
//

#include "labyrinthFactory.h"
#include <cstdlib>
#include <ctime>


class LabyrinthFactory {

    int labyrinthFactory::createRandom(labyrinth *labyrinth, int xSize, int ySize) {
        int x, y;
        labyrinth = new labyrinth(xSize, ySize);
        for (x = 0; x < xSize; x++) {
            for (y = 0; y < ySize; y++) {
                labyrinth->array[x][y] = getRandomBinaryValue();
            }
        }
        return 0;
    }

    int labyrinthFactory::getRandomBinaryValue() {
        srand((unsigned int) time(NULL));
        double r = ((double) rand() / (RAND_MAX));
        return int(r);
    }
};



