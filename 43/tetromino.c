#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include "tetromino.h"
#include "gamescreen.h"

int iTetroArr1[1][4] = {{1, 1, 1, 1}};
int iTetroArr2[4][1] = {{1}, {1}, {1}, {1}};

int sqTetroArr[2][2] = {{1, 1}, {1, 1}};

int revLTetroArr1[3][2] = {{0, 1}, {0, 1}, {1, 1}};
int revLTetroArr2[2][3] = {{1}, {1, 1, 1}};
int revLTetroArr3[3][2] = {{1, 1}, {1}, {1}};
int revLTetroArr4[2][3] = {{1, 1, 1}, {0, 0, 1}};

int lTetroArr1[3][2] = {{1}, {1}, {1, 1}};
int lTetroArr2[2][3] = {{1, 1, 1}, {1}};
int lTetroArr3[3][2] = {{1, 1}, {0, 1}, {0, 1}};
int lTetroArr4[2][3] = {{0, 0, 1}, {1, 1, 1}};

int zzTetroArr1[2][3] = {{0, 1, 1}, {1, 1}};
int zzTetroArr2[3][2] = {{1}, {1, 1}, {0, 1}};

int revZzTetroArr1[2][3] = {{1, 1}, {0, 1, 1}};
int revZzTetroArr2[3][2] = {{0, 1}, {1, 1}, {1}};

int tTetroArr1[2][3] = {{1, 1, 1}, {0, 1}};
int tTetroArr2[3][2] = {{0, 1}, {1, 1}, {0, 1}};
int tTetroArr3[2][3] = {{0, 1}, {1, 1, 1}};
int tTetroArr4[3][2] = {{1}, {1, 1}, {1}};

Tetromino *iTetro;
Tetromino *sqTetro;
Tetromino *revLTetro;
Tetromino *lTetro;
Tetromino *zzTetro;
Tetromino *revZzTetro;
Tetromino *tTetro;
Tetromino *tetrominos[7];

Tetromino *createTetromino(int numStructures, Color colour);
void addStructure(Tetromino *tetro, int maxX, int maxY, const int structureArr[maxY][maxX], int numStruct);

int currTet = 6; // used for debugging

void initialiseTetromino() 
{
    iTetro = createTetromino(2, SKYBLUE);
    addStructure(iTetro, 4, 1, iTetroArr1, 0);
    addStructure(iTetro, 1, 4, iTetroArr2, 1);
    tetrominos[0] = iTetro;

    sqTetro = createTetromino(1, YELLOW);
    addStructure(sqTetro, 2, 2, sqTetroArr, 0);
    tetrominos[1] = sqTetro;

    revLTetro = createTetromino(4, DARKBLUE);
    addStructure(revLTetro, 2, 3, revLTetroArr1, 0);
    addStructure(revLTetro, 3, 2, revLTetroArr2, 1);
    addStructure(revLTetro, 2, 3, revLTetroArr3, 2);
    addStructure(revLTetro, 3, 2, revLTetroArr4, 3);
    tetrominos[2] = revLTetro;

    lTetro = createTetromino(4, ORANGE);
    addStructure(lTetro, 2, 3, lTetroArr1, 0);
    addStructure(lTetro, 3, 2, lTetroArr2, 1);
    addStructure(lTetro, 2, 3, lTetroArr3, 2);
    addStructure(lTetro, 3, 2, lTetroArr4, 3);
    tetrominos[3] = lTetro;

    zzTetro = createTetromino(2, GREEN);
    addStructure(zzTetro, 3, 2, zzTetroArr1, 0);
    addStructure(zzTetro, 2, 3, zzTetroArr2, 1);
    tetrominos[4] = zzTetro;

    revZzTetro = createTetromino(2, RED);
    addStructure(revZzTetro, 3, 2, revZzTetroArr1, 0);
    addStructure(revZzTetro, 2, 3, revZzTetroArr2, 1);
    tetrominos[5] = revZzTetro;

    tTetro = createTetromino(4, PURPLE);
    addStructure(tTetro, 3, 2, tTetroArr1, 0);
    addStructure(tTetro, 2, 3, tTetroArr2, 1);
    addStructure(tTetro, 3, 2, tTetroArr3, 2);
    addStructure(tTetro, 2, 3, tTetroArr4, 3);
    tetrominos[6] = tTetro;
}

void freeTetromino() 
{
    int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < tetrominos[i]->numStructures; j++) {
            free(tetrominos[i]->structure[j]);
        }
        free(tetrominos[i]);
    }
}

void handleTetromino() 
{
    //debugging
    if (IsKeyPressed(KEY_SPACE)) {
        if (currTet == 6) {
            currTet = 0;
        } else {
            currTet++;
        }
    }

    int xIsSafeRight = tetrominos[currTet]->xPos + tetrominos[currTet]->structure[tetrominos[currTet]->currStructure]->maxX * TETRO_WIDTH < GAMEAREA_END_X;
    int xIsSafeLeft = tetrominos[currTet]->xPos > GAMEAREA_START_X + TETRO_WIDTH;
    // int isSafeTurn = NEXT TIME: Logic for checking if tetro can turn
    // https://github.com/raysan5/raylib/issues/217 - see if helps with high cpu usage
    if (IsKeyPressed(KEY_RIGHT) && xIsSafeRight) {
        tetrominos[currTet]->xPos += TETRO_WIDTH;
    } else if (IsKeyPressed(KEY_LEFT) && xIsSafeLeft) {
        tetrominos[currTet]->xPos -= TETRO_WIDTH;
    } else if (IsKeyPressed(KEY_DOWN)) {
        tetrominos[currTet]->yPos += TETRO_HEIGHT;
    } else if (IsKeyPressed(KEY_UP)) {
        if (tetrominos[currTet]->currStructure + 1 == tetrominos[currTet]->numStructures) {
            tetrominos[currTet]->currStructure = 0;
        } else {
            tetrominos[currTet]->currStructure++;
        }
    }
    
    int y, x;
    for (y = 0; y < tetrominos[currTet]->structure[tetrominos[currTet]->currStructure]->maxY; y++) {
        for (x = 0; x < tetrominos[currTet]->structure[tetrominos[currTet]->currStructure]->maxX; x++) {
            if (tetrominos[currTet]->structure[tetrominos[currTet]->currStructure]->structure[y][x]) {
                DrawRectangle(
                    tetrominos[currTet]->xPos + (x * TETRO_WIDTH),
                    tetrominos[currTet]->yPos + (y * TETRO_HEIGHT),
                    TETRO_WIDTH,
                    TETRO_HEIGHT,
                    tetrominos[currTet]->colour
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

void addStructure(Tetromino *tetro, int maxX, int maxY, const int structureArr[maxY][maxX], int numStruct)
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
}
