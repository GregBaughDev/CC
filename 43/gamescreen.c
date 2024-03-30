#include <raylib.h>
#include "tetromino.h"
#include "main.h"

int GAMEAREA_START_X = 250;
int GAMEAREA_START_Y = 100;
int GAMEAREA_END_X = 525;
int GAMEAREA_END_Y = 650;

int NEXTPIECE_START_X = 50;
int NEXTPIECE_START_Y = 100;
int NEXTPIECE_END_X = 200;
int NEXTPIECE_END_Y = 250;

int SCOREAREA_START_X = 575;
int SCOREAREA_START_Y = 100;
int SCOREAREA_END_X = 750;
int SCOREAREA_END_Y = 200;
char* SCOREAREA_LABEL = "Score";
int SCOREAREA_LABEL_Y_POS = 130; 

void drawArea(int startX, int startY, int endX, int endY);
void setupGame();

void handleGameScreen() {
    // this funtion should just handle the game play
    setupGame(); // this should be moved so it's not repeatedly called
}

void setupGame() {
    drawArea(GAMEAREA_START_X, GAMEAREA_START_Y, GAMEAREA_END_X, GAMEAREA_END_Y);
    drawArea(NEXTPIECE_START_X, NEXTPIECE_START_Y, NEXTPIECE_END_X, NEXTPIECE_END_Y);
    // TO DO - Add "Next" text 
    drawArea(SCOREAREA_START_X, SCOREAREA_START_Y, SCOREAREA_END_X, SCOREAREA_END_Y);
    DrawText(
        SCOREAREA_LABEL, 
        675 - (MeasureText(SCOREAREA_LABEL, FONT_SIZE_SECONDARY) / 2),
        SCOREAREA_LABEL_Y_POS,
        FONT_SIZE_SECONDARY, 
        TEXT_COLOUR
    );
    // create button
}

void drawArea(int startX, int startY, int endX, int endY) {
    int x, y;
    for (y = startY; y <= endY; y += TETRO_HEIGHT) {
        for (x = startX; x <= endX; x += TETRO_WIDTH) {
            if (x == startX || x == endX || y == startY || y == endY) {
                DrawRectangleGradientH(x, y, TETRO_WIDTH, TETRO_HEIGHT, GRAY, DARKBLUE);
            }
        }
    }
}

// we should call initialise with other initialise in c - all memory stuff should be loaded on start up

