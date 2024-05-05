#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
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

const int gridYMax = 21;
const int gridXMax = 10;
GridTetro *gameGrid[gridYMax][gridXMax]; // y, x
// We will need an array with dynamic memory to store the currTets
Tetromino **tetroArray;
int currTet = 0;
int tetArrayCap = 10; // will use for realloc tetroArray

int fallCounter = 0;

int currStructure;
int lookahead;
int isXTurnSafe;
int isYTurnSafe;
int isTurnSafe;

Tetromino *createTetromino(int numStructures, Color colour);
GridTetro *createGridTetro(int x, int y, int arrPos);
void addStructure(Tetromino *tetro, int maxX, int maxY, const int structureArr[maxY][maxX], int numStruct);
int convertXGridCoordsToPos(int x);
int convertYGridCoordsToPos(int y);
// void drawTetrominos();
// void handleTetroMovement();
void createNextTetro();
bool isTetroCollision(int plusY, int plusX);
void lineCheck();

const int gridX = (GAMEAREA_END_X - GAMEAREA_START_X - TETRO_WIDTH) / TETRO_WIDTH;
const int gridY = (GAMEAREA_END_Y - GAMEAREA_START_Y - TETRO_HEIGHT) / TETRO_HEIGHT;

void initialiseTetromino() 
{
    // initialise gameGrid with null
    int y, x;
    for (y = 0; y < gridYMax; y++) {
        for (x = 0; x < gridXMax; x++) {
            gameGrid[y][x] = NULL;
        }
    }
    
    // malloc tetroArray with 10 spaces
    tetroArray = malloc(sizeof(Tetromino * ) * 10);
    if (tetroArray == NULL) {
        printf("Malloc tetroArray failed");
        exit(1);
    }

    createNextTetro();
}

void createNextTetro()
{
    int randTet = rand() % 7;

    switch (randTet)
    {
        case 0: 
        {
            Tetromino *iTetro = createTetromino(2, SKYBLUE);
            addStructure(iTetro, 4, 1, iTetroArr1, 0);
            addStructure(iTetro, 1, 4, iTetroArr2, 1);
            tetroArray[currTet] = iTetro;
            break;
        }
        case 1:
        {
            Tetromino *sqTetro = createTetromino(1, YELLOW);
            addStructure(sqTetro, 2, 2, sqTetroArr, 0);
            tetroArray[currTet] = sqTetro;
            break;
        }
        case 2:
        {
            Tetromino *revLTetro = createTetromino(4, DARKBLUE);
            addStructure(revLTetro, 2, 3, revLTetroArr1, 0);
            addStructure(revLTetro, 3, 2, revLTetroArr2, 1);
            addStructure(revLTetro, 2, 3, revLTetroArr3, 2);
            addStructure(revLTetro, 3, 2, revLTetroArr4, 3);
            tetroArray[currTet] = revLTetro;
            break;
        }
        case 3:
        {
            Tetromino *lTetro = createTetromino(4, ORANGE);
            addStructure(lTetro, 2, 3, lTetroArr1, 0);
            addStructure(lTetro, 3, 2, lTetroArr2, 1);
            addStructure(lTetro, 2, 3, lTetroArr3, 2);
            addStructure(lTetro, 3, 2, lTetroArr4, 3);
            tetroArray[currTet] = lTetro;
            break;
        }
        case 4:
        {
            Tetromino *zzTetro = createTetromino(2, GREEN);
            addStructure(zzTetro, 3, 2, zzTetroArr1, 0);
            addStructure(zzTetro, 2, 3, zzTetroArr2, 1);
            tetroArray[currTet] = zzTetro;
            break;
        }
        case 5:
        {
            Tetromino *revZzTetro = createTetromino(2, RED);
            addStructure(revZzTetro, 3, 2, revZzTetroArr1, 0);
            addStructure(revZzTetro, 2, 3, revZzTetroArr2, 1);
            tetroArray[currTet] = revZzTetro;
            break;
        }
        case 6:
        {
            Tetromino *tTetro = createTetromino(4, PURPLE);
            addStructure(tTetro, 3, 2, tTetroArr1, 0);
            addStructure(tTetro, 2, 3, tTetroArr2, 1);
            addStructure(tTetro, 3, 2, tTetroArr3, 2);
            addStructure(tTetro, 2, 3, tTetroArr4, 3);
            tetroArray[currTet] = tTetro;
            break;
        } 
        default:
            break;
    }
}

void freeTetromino() 
{
    int i, j;
    for (i = 0; i <= currTet; i++) {
        for (j = 0; j < tetroArray[i]->numStructures; j++) {
            free(tetroArray[i]->structure[j]);
        }
        free(tetroArray[i]);
    }
}

void drawTetrominos()
{
    int i, y, x;
    for (i = 0; i <= currTet; i++) {
        int currStructure = tetroArray[i]->currStructure;
        for (y = 0; y < tetroArray[i]->structure[currStructure]->maxY; y++) {
            for (x = 0; x < tetroArray[i]->structure[currStructure]->maxX; x++) {
                if (tetroArray[i]->structure[currStructure]->structure[y][x]) {
                    DrawRectangle(
                        convertXGridCoordsToPos(tetroArray[i]->xPos + x),
                        convertYGridCoordsToPos(tetroArray[i]->yPos + y),
                        TETRO_WIDTH,
                        TETRO_HEIGHT,
                        tetroArray[i]->colour
                    );
                }
            }
        }
    }
}

int convertXGridCoordsToPos(int x) {
    return (GAMEAREA_START_X + TETRO_WIDTH) + (x * TETRO_WIDTH);
}

int convertYGridCoordsToPos(int y) {
    return (GAMEAREA_START_Y + TETRO_HEIGHT) + (y * TETRO_HEIGHT);
}

void lineCheck()
{
    // check if any completed lines
    // loop through the gameGrid
    int y, x;
    for (y = gridYMax - 1; y >= 0; y--) {
        for (x = 0; x < gridXMax; x++) {
            int isLineComplete = 1;
            if (gameGrid[y][x] == NULL) { // there's an empty position in the line so continue with the loop
                isLineComplete = 0;
                continue;
            }
            if (isLineComplete && x == gridXMax - 1) {
                int xToRemove;
                for (xToRemove = 0; xToRemove < gridXMax; x++) {
                    int structureToRemove = tetroArray[gameGrid[y][xToRemove]->arrPos]->currStructure;
                    tetroArray[gameGrid[y][xToRemove]->arrPos]->structure[structureToRemove]->structure[gameGrid[y][xToRemove]->y][gameGrid[y][xToRemove]->x] = 0;
                    // up to here - but we're in some sort of issue
                }

                // if a line is removed go through and add one to all lines less than length
                
                // then copy everything from the above line to the below line

                // free everything removed
                
                // free everything in prev position
            }
        }
    }
}

bool isTetroCollision(int plusY, int plusX)
{
    int currStructureCollision = tetroArray[currTet]->currStructure;
    int y, x;
    for (y = 0; y < tetroArray[currTet]->structure[currStructureCollision]->maxY; y++) {
        for (x = 0; x < tetroArray[currTet]->structure[currStructureCollision]->maxX; x++) {
            if (tetroArray[currTet]->structure[currStructureCollision]->structure[y][x]) {
                if (gameGrid[tetroArray[currTet]->yPos + y + plusY][tetroArray[currTet]->xPos + x + plusX] != NULL) {
                    return true;
                }
            }
        }
    }
    return false;
}

void handleTetroMovement()
{
    lineCheck();
    currStructure = tetroArray[currTet]->currStructure;
    // handle falling
    int canTetroFall = 
        tetroArray[currTet]->yPos < gridYMax - 1 && 
        tetroArray[currTet]->yPos + tetroArray[currTet]->structure[currStructure]->maxY < gridYMax && !isTetroCollision(1, 0);

    if (canTetroFall) {
        fallCounter++;
        if (fallCounter >= FALL_SPEED) {
            tetroArray[currTet]->yPos++;
            fallCounter = 0;
        }
    } else {
        tetroArray[currTet]->isFalling = 0;
        int y, x;
        for (y = 0; y < tetroArray[currTet]->structure[currStructure]->maxY; y++) {
            for (x = 0; x < tetroArray[currTet]->structure[currStructure]->maxX; x++) {
                if (tetroArray[currTet]->structure[currStructure]->structure[y][x]) {
                    int yPos = tetroArray[currTet]->yPos + y;
                    int xPos = tetroArray[currTet]->xPos + x;
                    gameGrid[yPos][xPos] = createGridTetro(x, y, currTet);
                }
            }
        }
        currTet++;
        createNextTetro();
    }

    lookahead = tetroArray[currTet]->currStructure + 1 == tetroArray[currTet]->numStructures ? 0 : tetroArray[currTet]->currStructure + 1;
    isXTurnSafe = tetroArray[currTet]->xPos + 
        tetroArray[currTet]->structure[lookahead]->maxX <= gridXMax;
    isYTurnSafe = tetroArray[currTet]->yPos + tetroArray[currTet]->structure[lookahead]->maxY <= gridYMax;
    // Turning is still nqr for collision check
    isTurnSafe = isXTurnSafe && isYTurnSafe && !isTetroCollision(tetroArray[currTet]->structure[lookahead]->maxY, tetroArray[currTet]->structure[lookahead]->maxX);

    if (IsKeyPressed(KEY_RIGHT) && tetroArray[currTet]->xPos + (tetroArray[currTet]->structure[currStructure]->maxX) < gridXMax && !isTetroCollision(0, 1)) {
        tetroArray[currTet]->xPos++;
    } 
    
    if (IsKeyPressed(KEY_LEFT) && tetroArray[currTet]->xPos > 0 && !isTetroCollision(0, -1)) {
        tetroArray[currTet]->xPos--;
    } 
    
    if (IsKeyPressed(KEY_DOWN) && tetroArray[currTet]->isFalling && canTetroFall) { // need to do the isFalling update elsewhere
        tetroArray[currTet]->yPos++;
    }
    
    if (IsKeyPressed(KEY_UP) && tetroArray[currTet]->isFalling && isTurnSafe) {
        if (tetroArray[currTet]->currStructure + 1 == tetroArray[currTet]->numStructures) {
            tetroArray[currTet]->currStructure = 0;
        } else {
            tetroArray[currTet]->currStructure++;
        }
    }
}

void handleTetromino() 
{ 
    handleTetroMovement();
    drawTetrominos();
}

Tetromino *createTetromino(int numStructures, Color colour)
{
    Tetromino *tetro = malloc(sizeof(Tetromino));
    if (tetro == NULL) {
        printf("Malloc tetro failed");
        exit(1);
    }

    tetro->numStructures = numStructures;
    tetro->currStructure = 0;
    tetro->xPos = 2;
    tetro->yPos = 0;
    tetro->colour = colour;
    tetro->isFalling = 1;
    return tetro;
}

GridTetro *createGridTetro(int x, int y, int arrPos) {
    GridTetro *gridTetro = malloc(sizeof(GridTetro));
    if (gridTetro == NULL) {
        printf("Malloc gridTetro failed");
        exit(1);
    }

    gridTetro->x = x;
    gridTetro->y = y;
    gridTetro->arrPos = arrPos;
    return gridTetro;
}

void addStructure(Tetromino *tetro, int maxX, int maxY, const int structureArr[maxY][maxX], int numStruct)
{
    Structure *structure = malloc(sizeof(Structure));
    if (structure == NULL) {
        printf("Malloc structure failed");
        exit(1);
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
