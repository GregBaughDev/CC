#include <stdio.h>
#include "raylib.h"
#include "main.h"
#include "initialise.h"

int main(void) 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");

    int strMeasure = MeasureText(MAINMENU_WELCOME, FONT_SIZE) / 2;
    int centrePoint = (WINDOW_WIDTH / 2) - strMeasure;

    initialise();

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BG_COLOUR);
        DrawText(MAINMENU_WELCOME, centrePoint, 50, 30, TEXT_COLOUR);
        handleButtons();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
