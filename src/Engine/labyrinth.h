//
// Created by nikit on 16/04/2018.
//

#ifndef ALGODAT_LABYRINTH_H
#define ALGODAT_LABYRINTH_H
// source https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
class labyrinth {
    int* array;
    int xSize, ySize, m_width;
public:
    labyrinth( int w, int h ) : m_width( w ), array( new int[ w * h ] ) {
        xSize = w;
        ySize = h;
    }
    ~labyrinth() { delete[] array; }

    int at( int x, int y ) const {
        return array[ index( x, y ) ];
    }

    int fillRandom() {
        for(int i = 0; i < xSize; ++i){
            for(int j = 0; j < ySize; ++j){
                array[ index( i, j) ] = randomize();
            }
        }
    }

protected:
    int index( int x, int y ) const {
        return x + m_width * y;
    }
    int randomize() {
        srand((unsigned int) nullptr );
        return rand()&1;
    }
};

#endif //ALGODAT_LABYRINTH_H
