#include <raylib.h>
#include "main.h"

char* HELP_HEADING = "Help";
char* HELP_TEXT = "The aim of the game is to create full lines from the\ndropping pieces.\nUse the spacebar to turn the shapes and use the left\nand right keys to move the pieces. Holding the down\narrow will make the pieces drop quickly.\nThe game is over when there's no more space for\nthe pieces.";
char* HELP_EXIT = "Press mouse button to return to main menu";

void handleHelpScreen()
{
    SetTextLineSpacing(30);
    DrawText(
        HELP_HEADING, 
        WINDOW_WIDTH_HALF - (MeasureText(HELP_HEADING, FONT_SIZE) / 2),
        50,
        FONT_SIZE,
        TEXT_COLOUR
    );
    Rectangle popup = { .height = 450, .width = 600, .x = 100, .y = 100 };
    DrawRectangleRounded(popup, 0.25, 0, DARKBLUE);
    DrawText(HELP_TEXT, 120, 150, FONT_SIZE_SECONDARY, TEXT_COLOUR);
    DrawText(
        HELP_EXIT, 
        WINDOW_WIDTH_HALF - (MeasureText(HELP_EXIT, FONT_SIZE_SECONDARY) / 2), 
        500, 
        FONT_SIZE_SECONDARY, 
        TEXT_COLOUR
    );

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        setScreenToMainMenu();
    }
}