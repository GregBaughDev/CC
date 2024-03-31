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

void setScreenToMainMenu() {
    currScreen = MAIN_MENU;
}

void setScreenToGame() {
    currScreen = GAME;
}

void setScreenToHelp() {
    currScreen = HELP;
}

int main(void) 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
    initialise();

    while (!WindowShouldClose()) 
    {
        BeginDrawing(); // only call this once everything is loaded
        ClearBackground(BG_COLOUR);

        switch (currScreen)
        {
        case GAME:
            handleGameScreen();
            break;
        case HELP:
            handleHelpScreen();
            break;
        case MAIN_MENU:
            handleMainMenu();
            break;
        default:
            break;
        }
        
        EndDrawing();
    }

    CloseWindow();
    freeButtons(); // could also free buttons when game started?

    return 0;
}
