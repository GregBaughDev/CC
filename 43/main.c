#include <stdio.h>
#include "main.h"
#include "initialise.h"
#include "mainmenu.h"

Color BG_COLOUR = BLACK;
Color TEXT_COLOUR = WHITE;
Color BUTTON_HIGHLIGHT = DARKBLUE;
int FONT_SIZE = 30;
int FONT_SIZE_SECONDARY = 20;
int FONT_SIZE_THIRD = 15;

enum screen { MAIN_MENU, HELP, GAME };
int currScreen = MAIN_MENU;

int main(void) 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
    initialise();

    // screen is displayed depending on the enum using switch
    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BG_COLOUR);

        switch (currScreen)
        {
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
