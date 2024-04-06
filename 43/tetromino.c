#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include "tetromino.h"

int iTetroArr1[1][4] = {{1, 1, 1, 1}};
int iTetroArr2[4][1] = {{1}, {1}, {1}, {1}};

int sqTetroArr[2][2] = {{1, 1}, {1, 1}};

int revLTetroArr1[3][2] = {{0, 1}, {0, 1}, {1, 1}};
int revLTetroArr2[2][3] = {{1}, {1, 1, 1}};
int revLTetroArr3[3][2] = {{1, 1}, {1}, {1}};
int revLTetroArr4[2][3] = {{1, 1, 1}, {0, 0, 1}};

Tetromino *iTetro;
Tetromino *sqTetro;
Tetromino *revLTetro;

// create all then add to array which can be freed

Tetromino *createTetromino(int numStructures, Color colour);
Tetromino *addStructure(Tetromino *tetro, int maxX, int maxY, const int structureArr[maxX][maxY], int numStruct);

void initialiseTetromino() 
{
    iTetro = createTetromino(2, SKYBLUE);
    addStructure(iTetro, 4, 1, iTetroArr1, 0);
    addStructure(iTetro, 1, 4, iTetroArr2, 1);

    sqTetro = createTetromino(1, YELLOW);
    addStructure(sqTetro, 2, 2, sqTetroArr, 0);

    revLTetro = createTetromino(4, DARKBLUE);
    addStructure(revLTetro, 2, 3, revLTetroArr1, 0);
    addStructure(revLTetro, 3, 2, revLTetroArr2, 1);
    addStructure(revLTetro, 2, 3, revLTetroArr3, 2);
    addStructure(revLTetro, 3, 2, revLTetroArr4, 3);
}

void freeTetromino() 
{
    int i;
    for (i = 0; i < revLTetro->numStructures; i++) {
        free(revLTetro->structure[i]);
    }
    free(revLTetro);
}

void handleTetromino() 
{
    if (IsKeyPressed(KEY_RIGHT)) {
        revLTetro->xPos += TETRO_WIDTH;
    } else if (IsKeyPressed(KEY_LEFT)) {
        revLTetro->xPos -= TETRO_WIDTH;
    } else if (IsKeyPressed(KEY_DOWN)) {
        revLTetro->yPos += TETRO_HEIGHT;
    } else if (IsKeyPressed(KEY_UP)) {
        if (revLTetro->currStructure + 1 == revLTetro->numStructures) {
            revLTetro->currStructure = 0;
        } else {
            revLTetro->currStructure++;
        }
    }
    
    int y, x;
    for (y = 0; y < revLTetro->structure[revLTetro->currStructure]->maxY; y++) {
        for (x = 0; x < revLTetro->structure[revLTetro->currStructure]->maxX; x++) {
            if (revLTetro->structure[revLTetro->currStructure]->structure[y][x]) {
                DrawRectangle(
                    revLTetro->xPos + (x * TETRO_WIDTH),
                    revLTetro->yPos + (y * TETRO_HEIGHT),
                    TETRO_WIDTH,
                    TETRO_HEIGHT,
                    revLTetro->colour
                );
            }
        }
    }
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

Tetromino *addStructure(Tetromino *tetro, int maxX, int maxY, const int structureArr[maxY][maxX], int numStruct)
{
    Structure *structure = malloc(sizeof(Structure));
    if (structure == NULL) {
        printf("Malloc structure failed");
        exit(-1);
    }
    
    structure->maxX = maxX;
    structure->maxY = maxY;
    
    int x, y;
    for (y = 0; y < maxY; y++) {
        for (x = 0; x < maxX; x++) {
            structure->structure[y][x] = structureArr[y][x];
        }
    }
    tetro->structure[numStruct] = structure;
    
    return tetro;
}
