#include <stdio.h>
#include "raylib.h"

static const Color BG_COLOUR = BLACK;
static const Color TEXT_COLOUR = WHITE;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 650;
const int centrePointButton = (WINDOW_WIDTH / 2) - 150;
const Rectangle button = { .x = centrePointButton, .y = 150, .width = 300, .height = 50};
const Rectangle button2 = { .x = centrePointButton, .y = 250, .width = 300, .height = 50};
const char* MAINMENU_WELCOME = "Welcome to Tetris";
const char* MAINMENU_START = "Start";
const char* MAINMENU_HELP = "Help";
const int FONT_SIZE = 30;
const int FONT_SIZE_SECONDARY = 20;

int main(void) 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");

    int strMeasure = MeasureText(MAINMENU_WELCOME, FONT_SIZE) / 2;
    int centrePoint = (WINDOW_WIDTH / 2) - strMeasure; 
    int startButtonStrMeasure = MeasureText(MAINMENU_START, FONT_SIZE_SECONDARY) / 2;
    int startButtonCentrePoint = (WINDOW_WIDTH / 2) - startButtonStrMeasure;
    int helpButtonStrMeasure = MeasureText(MAINMENU_HELP, FONT_SIZE_SECONDARY) / 2;
    int helpButtonCentrePoint = (WINDOW_WIDTH / 2) - helpButtonStrMeasure;

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BG_COLOUR);
        DrawText(MAINMENU_WELCOME, centrePoint, 50, 30, TEXT_COLOUR);
        DrawRectangleRoundedLines(button, 2, 0, 2, TEXT_COLOUR);
        DrawText(MAINMENU_START, startButtonCentrePoint, 165, 20, TEXT_COLOUR);
        DrawRectangleRoundedLines(button2, 2, 0, 2, TEXT_COLOUR);
        DrawText(MAINMENU_HELP, helpButtonCentrePoint, 265, 20, TEXT_COLOUR);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
