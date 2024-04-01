#include <stdlib.h>
#include <stdio.h>
#include "tetromino.h"

Tetromino *createTetromino(int numStructures, Color colour)
{
    Tetromino *tetro = malloc(sizeof(Tetromino));
    if (tetro == NULL) {
        printf("Malloc tetro failed");
        exit(-1);
    }

    tetro->numStructures = numStructures;
    tetro->currStructure = 0;
    tetro->xPos = 0;
    tetro->yPos = 0;
    tetro->colour = colour;
}

Tetromino *addStructure(Tetromino *tetro, const int **structureArr, int maxY, int maxX, int numStruct)
{
    Structure *structure = malloc(sizeof(Structure));
    if (structure == NULL) {
        printf("Malloc structure failed");
        exit(-1);
    }
    
    structure->maxX = maxX;
    structure->maxY = maxY;
    
    int x, y;
    for (x = 0; x < 4; x++) {
        for (y = 0; y < 4; y++) {
            structure->structure[x][y] = structureArr[x][y];
        }
    }
    tetro->structure[numStruct] = structure;
    return tetro;
}

int ITetro1[4][4] = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}};
int ITetro2[1][4] = {{1, 1, 1, 1}};

// TO DO NEXT TIME
// CREATE FIRST TETRO
// DISPLAY IT
// TURN IT