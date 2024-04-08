#include <stdio.h>
#include "main.h"
#include "mainmenu.h"
#include "helpscreen.h"
#include "gamescreen.h"

Color BG_COLOUR = BLACK;
Color TEXT_COLOUR = WHITE;
Color BUTTON_HIGHLIGHT = DARKBLUE;
int FONT_SIZE = 30;
int FONT_SIZE_SECONDARY = 20;
int FONT_SIZE_THIRD = 15;

enum screen { MAIN_MENU, HELP, GAME };
int currScreen = MAIN_MENU;

void setScreenToMainMenu() 
{
    currScreen = MAIN_MENU;
}

void setScreenToGame() 
{
    currScreen = GAME;
}

void setScreenToHelp() 
{
    currScreen = HELP;
}

void initialise() 
{
    initialiseMainMenu();
    initialiseGameScreen();
}

int main(void) 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
    SetWindowState(FLAG_VSYNC_HINT);
    initialise();

    while (!WindowShouldClose()) 
    {
        BeginDrawing(); // only call this once everything is loaded
        ClearBackground(BG_COLOUR);

        switch (currScreen)
        {
        case GAME:
            drawGame();
            handleGame();
            break;
        case HELP:
            drawHelpScreen();
            break;
        case MAIN_MENU:
            drawMainMenu();
            break;
        default:
            break;
        }
        
        EndDrawing();
    }

    CloseWindow();
    freeMainMenu();
    freeGame();

    return 0;
}
