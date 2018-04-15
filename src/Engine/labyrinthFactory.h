//
// Created by nikit on 15/04/2018.
//

#ifndef ALGODATII_LABYRINTHFACTORY_H
#define ALGODATII_LABYRINTHFACTORY_H

typedef struct labyrinth {
    const int firstDimensionSize;
    const int secondDimensionSize;
    const int freeField = 0;
    const int filledField = 1;
    int array [firstDimensionSize][secondDimensionSize];
};

class labyrinthFactory {
public:
    //creates a randomly filled labyrinth object in given sizes
    int createRandom(labyrinth *labyrinth, int xSize, int ySize);
    //returns a integer of values 0 to 1
    int getRandomBinaryValue();
};


#endif //ALGODATII_LABYRINTHFACTORY_H
