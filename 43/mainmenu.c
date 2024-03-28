#include <raylib.h>
#include "main.h"
#include "initialise.h"

char* MAINMENU_WELCOME = "Welcome to Tetris";
char* MAINMENU_SCORES = "High Scores";

int WINDOW_WIDTH_HALF = WINDOW_WIDTH / 2;

void handleMainMenu() 
{
    DrawText(
        MAINMENU_WELCOME, 
        WINDOW_WIDTH_HALF - (MeasureText(MAINMENU_WELCOME, FONT_SIZE) / 2), 
        50, 
        30, 
        TEXT_COLOUR
    );
    DrawLine(100, 350, 700, 350, TEXT_COLOUR);
    DrawText(
        MAINMENU_SCORES, 
        WINDOW_WIDTH_HALF - (MeasureText(MAINMENU_SCORES, FONT_SIZE_SECONDARY) / 2),
        400, 
        FONT_SIZE_SECONDARY,
        TEXT_COLOUR
    );
    // placeholder high scores TODO
    DrawText("GRB - 4004", 350, 450, FONT_SIZE_THIRD, TEXT_COLOUR);
    DrawText("GRB - 3003", 350, 475, FONT_SIZE_THIRD, TEXT_COLOUR);
    DrawText("GRB - 2002", 350, 500, FONT_SIZE_THIRD, TEXT_COLOUR);
    DrawText("GRB - 1001", 350, 525, FONT_SIZE_THIRD, TEXT_COLOUR);
    DrawText("GRB - 987", 350, 550, FONT_SIZE_THIRD, TEXT_COLOUR);
    handleButtons();
}