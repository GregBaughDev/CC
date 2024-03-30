#include <raylib.h>
#include "tetromino.h"

void drawGameArea();
void setupGame();
void drawNextPieceArea();

void handleGameScreen() {
    // this funtion should just handle the game play
    setupGame(); // this should be moved so it's not repeatedly called
}

void setupGame() {
    drawGameArea();
    // create button
    // initiate scoring
    drawNextPieceArea();
}

void drawGameArea() {
    int x, y;
    for (y = 100; y <= 650; y += TETRO_HEIGHT) {
        for (x = 250; x <= 525; x += TETRO_WIDTH) {
            if (x == 250 || x == 525 || y == 100 || y == 650) {
                DrawRectangleGradientH(x, y, TETRO_WIDTH, TETRO_HEIGHT, GRAY, DARKBLUE);
            }
        }
    }
}

void drawNextPieceArea() { // move all drawing into function and constantise the magic nums
    int x, y;
    for (y = 100; y <= 250; y += TETRO_HEIGHT) {
        for (x = 50; x <= 200; x += TETRO_WIDTH) {
            if (x == 50 || x == 200 || y == 100 || y == 250) {
                DrawRectangleGradientH(x, y, TETRO_WIDTH, TETRO_HEIGHT, GRAY, DARKBLUE);
            }
        }
    }
}

// we should call initialise with other initialise in c - all memory stuff should be loaded on start up

