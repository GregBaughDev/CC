#include <raylib.h>
#include <stdlib.h>
#include "tetromino.h"
#include "main.h"
#include "buttons.h"
#include "gamescreen.h"

char* NEXTPIECE_LABEL = "Next";

int SCOREAREA_START_X = 575;
int SCOREAREA_START_Y = 100;
int SCOREAREA_END_X = 750;
int SCOREAREA_END_Y = 200;
char* SCOREAREA_LABEL = "Score";

int LABEL_Y_POS = 130; 

Button *exitButton;

void drawArea(int startX, int startY, int endX, int endY);

void initialiseGameScreen() 
{
    exitButton = createButton(700, "Exit");
    initialiseTetromino();
}

void handleGame() 
{
    handleTetromino();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), exitButton->rect)) {
        setScreenToMainMenu();
    }
}

void freeGame() 
{
    free(exitButton);
    freeTetromino();
}

void drawGame() 
{
    drawArea(GAMEAREA_START_X, GAMEAREA_START_Y, GAMEAREA_END_X, GAMEAREA_END_Y);
    drawArea(NEXTPIECE_START_X, NEXTPIECE_START_Y, NEXTPIECE_END_X, NEXTPIECE_END_Y);
    DrawText(
        NEXTPIECE_LABEL,
        140 - (MeasureText(NEXTPIECE_LABEL, FONT_SIZE_SECONDARY) / 2),
        LABEL_Y_POS,
        FONT_SIZE_SECONDARY, 
        TEXT_COLOUR
    );
    drawArea(SCOREAREA_START_X, SCOREAREA_START_Y, SCOREAREA_END_X, SCOREAREA_END_Y);
    DrawText(
        SCOREAREA_LABEL, 
        675 - (MeasureText(SCOREAREA_LABEL, FONT_SIZE_SECONDARY) / 2),
        LABEL_Y_POS,
        FONT_SIZE_SECONDARY, 
        TEXT_COLOUR
    );
    drawButton(exitButton);
}

void drawArea(int startX, int startY, int endX, int endY) 
{
    int x, y;
    for (y = startY; y <= endY; y += TETRO_HEIGHT) {
        for (x = startX; x <= endX; x += TETRO_WIDTH) {
            if (x == startX || x == endX || y == startY || y == endY) {
                DrawRectangleGradientH(x, y, TETRO_WIDTH, TETRO_HEIGHT, GRAY, DARKBLUE);
            }
        }
    }
}

