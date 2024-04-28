#ifndef _TETROMINO_H
#define _TETROMINO_H
#include <raylib.h>

#define TETRO_HEIGHT 25
#define TETRO_WIDTH 25

typedef struct Structure
{
    int structure[4][4];
    int maxY;
    int maxX;
} Structure;

typedef struct Tetromino
{
    int xPos;
    int yPos;
    Color colour;
    struct Structure *structure[4];
    int numStructures;
    int currStructure;
    int isFalling;
} Tetromino;

typedef struct GridTetro
{
    int x;
    int y;
    int arrPos;
} GridTetro;

void initialiseTetromino();
void handleTetromino();
void freeTetromino();

/**
 * iTetro
 *  X 0 0 0 | X X X X
 *  X 0 0 0 | 0 0 0 0
 *  X 0 0 0 | 0 0 0 0
 *  X 0 0 0 | 0 0 0 0 
*/

/**
 * sqTetro
 * X X 0 0
 * X X 0 0
 * 0 0 0 0
 * 0 0 0 0
*/

/**
 * revLTetro
 * 0 X 0 0 | X 0 0 0 | X X 0 0 | X X X 0
 * 0 X 0 0 | X X X 0 | X 0 0 0 | 0 0 X 0
 * X X 0 0 | 0 0 0 0 | X 0 0 0 | 0 0 0 0
 * 0 0 0 0 | 0 0 0 0 | 0 0 0 0 | 0 0 0 0 
*/

/**
 * lTetro
 * X 0 0 0 | X X X 0 | X X 0 0 | 0 0 X 0
 * X 0 0 0 | X 0 0 0 | 0 X 0 0 | X X X 0
 * X X 0 0 | 0 0 0 0 | 0 X 0 0 | 0 0 0 0
 * 0 0 0 0 | 0 0 0 0 | 0 0 0 0 | 0 0 0 0
*/

/**
 * zzTetro
 * 0 X X 0 | X 0 0 0
 * X X 0 0 | X X 0 0
 * 0 0 0 0 | 0 X 0 0 
 * 0 0 0 0 | 0 0 0 0
*/

/**
 * revZzTetro
 * X X 0 0 | 0 X 0 0
 * 0 X X 0 | X X 0 0 
 * 0 0 0 0 | X 0 0 0
 * 0 0 0 0 | 0 0 0 0
*/

/**
 * tTetro
 * X X X 0 | 0 X 0 0 | 0 X 0 0 | X 0 0 0 
 * 0 X 0 0 | X X 0 0 | X X X 0 | X X 0 0 
 * 0 0 0 0 | 0 X 0 0 | 0 0 0 0 | X 0 0 0 
 * 0 0 0 0 | 0 0 0 0 | 0 0 0 0 | 0 0 0 0
*/
#endif