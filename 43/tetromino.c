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

int currTet = 0; // points to active tetro in gameTetros array
int gameTetroCount = 0;
Tetromino **gameTetros;

Tetromino *createTetromino(int numStructures, Color colour);
void addStructure(Tetromino *tetro, int maxX, int maxY, const int structureArr[maxY][maxX], int numStruct);
void drawTetrominos();
void handleTetroMovement();
void createNextTetro();
bool isTetroBlocking(int currX, int currY);

int lookahead;
int xIsSafeRight;
int xIsSafeLeft;
int isXSafeTurn;
int isYSafeTurn;
int isDownSafe;

const int gridX = (GAMEAREA_END_X - GAMEAREA_START_X - TETRO_WIDTH) / TETRO_WIDTH;
const int gridY = (GAMEAREA_END_Y - GAMEAREA_START_Y - TETRO_HEIGHT) / TETRO_HEIGHT;

void resizeGameTetrominoList() 
{
    Tetromino **copyGameTetros = realloc(gameTetros, sizeof(Tetromino *) * (gameTetroCount * 2));
    if (copyGameTetros == NULL) {
        printf("resizeGameTetrominoList failed\n");
        exit(1);
    }
    gameTetros = copyGameTetros;
    free(copyGameTetros);
}

void initialiseTetromino() 
{
    gameTetros = malloc(sizeof(Tetromino *) * 10);
    if (gameTetros == NULL) {
        printf("Malloc gameTetros failed\n");
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
            gameTetros[gameTetroCount] = iTetro;
            break;
        }
        case 1:
        {
            Tetromino *sqTetro = createTetromino(1, YELLOW);
            addStructure(sqTetro, 2, 2, sqTetroArr, 0);
            gameTetros[gameTetroCount] = sqTetro;
            break;
        }
        case 2:
        {
            Tetromino *revLTetro = createTetromino(4, DARKBLUE);
            addStructure(revLTetro, 2, 3, revLTetroArr1, 0);
            addStructure(revLTetro, 3, 2, revLTetroArr2, 1);
            addStructure(revLTetro, 2, 3, revLTetroArr3, 2);
            addStructure(revLTetro, 3, 2, revLTetroArr4, 3);
            gameTetros[gameTetroCount] = revLTetro;
            break;
        }
        case 3:
        {
            Tetromino *lTetro = createTetromino(4, ORANGE);
            addStructure(lTetro, 2, 3, lTetroArr1, 0);
            addStructure(lTetro, 3, 2, lTetroArr2, 1);
            addStructure(lTetro, 2, 3, lTetroArr3, 2);
            addStructure(lTetro, 3, 2, lTetroArr4, 3);
            gameTetros[gameTetroCount] = lTetro;
            break;
        }
        case 4:
        {
            Tetromino *zzTetro = createTetromino(2, GREEN);
            addStructure(zzTetro, 3, 2, zzTetroArr1, 0);
            addStructure(zzTetro, 2, 3, zzTetroArr2, 1);
            gameTetros[gameTetroCount] = zzTetro;
            break;
        }
        case 5:
        {
            Tetromino *revZzTetro = createTetromino(2, RED);
            addStructure(revZzTetro, 3, 2, revZzTetroArr1, 0);
            addStructure(revZzTetro, 2, 3, revZzTetroArr2, 1);
            gameTetros[gameTetroCount] = revZzTetro;
            break;
        }
        case 6:
        {
            Tetromino *tTetro = createTetromino(4, PURPLE);
            addStructure(tTetro, 3, 2, tTetroArr1, 0);
            addStructure(tTetro, 2, 3, tTetroArr2, 1);
            addStructure(tTetro, 3, 2, tTetroArr3, 2);
            addStructure(tTetro, 2, 3, tTetroArr4, 3);
            gameTetros[gameTetroCount] = tTetro;
            break;
        } 
        default:
            break;
    } 
    
    gameTetroCount++;
}

void freeTetromino() 
{
    int i, j;
    for (i = 0; i <= currTet; i++) {
        for (j = 0; j < gameTetros[i]->numStructures; j++) {
            free(gameTetros[i]->structure[j]);
        }
        free(gameTetros[i]);
    }
}

void drawTetrominos()
{
    int i, y, x;
    for (i = 0; i < gameTetroCount; i++) {
        int y, x;
        for (y = 0; y < gameTetros[i]->structure[gameTetros[i]->currStructure]->maxY; y++) {
            for (x = 0; x < gameTetros[i]->structure[gameTetros[i]->currStructure]->maxX; x++) {
                if (gameTetros[i]->structure[gameTetros[i]->currStructure]->structure[y][x]) {
                    DrawRectangle(
                        gameTetros[i]->xPos + (x * TETRO_WIDTH),
                        gameTetros[i]->yPos + (y * TETRO_HEIGHT),
                        TETRO_WIDTH,
                        TETRO_HEIGHT,
                        gameTetros[i]->colour
                    );
                }
            }
        }
    }
}

bool isTetroBlocking(int currX, int currY)
{
    // TO DO - Fix the collision
    int i, y, x;
    for (i = 0; i < currTet; i++) {
        int y, x;
        int currMaxY = gameTetros[i]->structure[gameTetros[i]->currStructure]->maxY;
        int currMaxX = gameTetros[i]->structure[gameTetros[i]->currStructure]->maxX;
        printf("CURRTETY: %d, CURRY: %d\n", gameTetros[i]->yPos, currY);
        printf("CURRTETX: %d, CURRX: %d\n", gameTetros[i]->xPos, currX);
        for (y = 0; y < currMaxY; y++) {
            for (x = 0; x < currMaxX; x++) {
                if (
                    currY >= gameTetros[i]->yPos && 
                    currY <= gameTetros[i]->yPos + (currMaxY * TETRO_HEIGHT) &&
                    currX >= gameTetros[i]->xPos &&
                    currX <= gameTetros[i]->xPos + (currMaxX * TETRO_WIDTH)) {
                    printf("is collision\n");
                    return true;
                }
            }
        }
    }
    return false;
}

void handleTetroMovement()
{
    /**
    * Move and turn logic 
    */
    lookahead = gameTetros[currTet]->currStructure + 1 == gameTetros[currTet]->numStructures ? 0 : gameTetros[currTet]->currStructure + 1;
    xIsSafeRight = gameTetros[currTet]->xPos + gameTetros[currTet]->structure[gameTetros[currTet]->currStructure]->maxX * TETRO_WIDTH < GAMEAREA_END_X;
    xIsSafeLeft = gameTetros[currTet]->xPos > GAMEAREA_START_X + TETRO_WIDTH;
    isXSafeTurn = gameTetros[currTet]->xPos + gameTetros[currTet]->structure[lookahead]->maxX * TETRO_WIDTH <= GAMEAREA_END_X;
    isYSafeTurn = gameTetros[currTet]->yPos + gameTetros[currTet]->structure[lookahead]->maxY * TETRO_HEIGHT <= GAMEAREA_END_Y;
    isDownSafe = gameTetros[currTet]->yPos + gameTetros[currTet]->structure[gameTetros[currTet]->currStructure]->maxY * TETRO_HEIGHT < (GAMEAREA_END_Y - TETRO_HEIGHT);

    if (IsKeyPressed(KEY_RIGHT) && xIsSafeRight) {
        gameTetros[currTet]->xPos += TETRO_WIDTH;
    } 
    
    if (IsKeyPressed(KEY_LEFT) && xIsSafeLeft) {
        gameTetros[currTet]->xPos -= TETRO_WIDTH;
    } 
    
    if (IsKeyPressed(KEY_DOWN) && isDownSafe) {
        gameTetros[currTet]->yPos += TETRO_HEIGHT;
    }
    
    if (IsKeyPressed(KEY_UP) && isXSafeTurn && isYSafeTurn) {
        if (gameTetros[currTet]->currStructure + 1 == gameTetros[currTet]->numStructures) {
            gameTetros[currTet]->currStructure = 0;
        } else {
            gameTetros[currTet]->currStructure++;
        }
    }
}

void handleTetromino() 
{ 
    int canTetroFall = gameTetros[currTet]->yPos +
        (gameTetros[currTet]->structure[gameTetros[currTet]->currStructure]->maxY * TETRO_HEIGHT) < GAMEAREA_END_Y;
    int isTetroBlocked = isTetroBlocking(gameTetros[currTet]->xPos, gameTetros[currTet]->yPos);

    if (canTetroFall && !isTetroBlocked) {
        gameTetros[currTet]->yPos += 1;
    } else {
        // the tetro has stopped falling
        gameTetros[currTet]->isFalling = 0;
    }
    
    if (gameTetros[currTet]->isFalling) {
        handleTetroMovement();
    } else {
        // TO DO - This is the culprit!
        // if (sizeof(gameTetros) / sizeof(gameTetros[0]) == gameTetroCount) {
        //     resizeGameTetrominoList();
        // }
        createNextTetro();
        currTet++;
    }

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
    tetro->xPos = 300;
    tetro->yPos = 150;
    tetro->colour = colour;
    tetro->isFalling = 1;
    return tetro;
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
