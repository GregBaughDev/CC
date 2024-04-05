#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include "tetromino.h"

int ITetro1[1][4] = {{1, 1, 1, 1}};
int ITetro2[4][1] = {{1}, {1}, {1}, {1}};

Tetromino *first;

Tetromino *createTetromino(int numStructures, Color colour);
Tetromino *addStructure(Tetromino *tetro, int maxX, int maxY, const int structureArr[maxX][maxY], int numStruct);

void initialiseTetromino() 
{
    first = createTetromino(2, SKYBLUE);
    addStructure(first, 4, 1, ITetro1, 0);
    addStructure(first, 1, 4, ITetro2, 1);
}

void freeTetromino() 
{
    int i;
    for (i = 0; i < first->numStructures; i++) {
        free(first->structure[i]);
    }
    free(first);
}

void handleTetromino() 
{
    if (IsKeyPressed(KEY_RIGHT)) {
        first->xPos += TETRO_WIDTH;
    } else if (IsKeyPressed(KEY_LEFT)) {
        first->xPos -= TETRO_WIDTH;
    } else if (IsKeyPressed(KEY_DOWN)) {
        first->yPos += TETRO_HEIGHT;
    } else if (IsKeyPressed(KEY_UP)) {
        if (first->currStructure + 1 == first->numStructures) {
            first->currStructure = 0;
        } else {
            first->currStructure++;
        }
    }
    DrawRectangle(
        first->xPos, 
        first->yPos, 
        first->structure[first->currStructure]->maxX * TETRO_WIDTH, 
        first->structure[first->currStructure]->maxY * TETRO_HEIGHT, 
        first->colour
    );
}

Tetromino *createTetromino(int numStructures, Color colour)
{
    Tetromino *tetro = malloc(sizeof(Tetromino));
    if (tetro == NULL) {
        printf("Malloc tetro failed");
        exit(-1);
    }

    tetro->numStructures = numStructures;
    tetro->currStructure = 0;
    tetro->xPos = 300;
    tetro->yPos = 150;
    tetro->colour = colour;
    return tetro;
}

Tetromino *addStructure(Tetromino *tetro, int maxX, int maxY, const int structureArr[maxX][maxY], int numStruct)
{
    Structure *structure = malloc(sizeof(Structure));
    if (structure == NULL) {
        printf("Malloc structure failed");
        exit(-1);
    }
    
    structure->maxX = maxX;
    structure->maxY = maxY;
    
    int x, y;
    for (x = 0; x < maxX; x++) {
        for (y = 0; y < maxY; y++) {
            structure->structure[x][y] = structureArr[x][y];
        }
    }
    tetro->structure[numStruct] = structure;
    return tetro;
}
