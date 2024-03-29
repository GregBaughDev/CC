#include <raylib.h>
#include <stdlib.h>
#include "main.h"
#include "buttons.h"

char* MAINMENU_WELCOME = "Welcome to Tetris";
char* MAINMENU_SCORES = "High Scores";

const int buttonCount = 2;
Button *buttons[2];

char* MAINMENU_START = "Start";
char* MAINMENU_HELP = "Help";

void handleMainMenuButtons(Button *buttonList[], int buttonCount);

int initialise() 
{
    Button *startButton = createButton(150, MAINMENU_START, 165);
    Button *helpButton = createButton(250, MAINMENU_HELP, 265);

    buttons[0] = startButton;
    buttons[1] = helpButton;

    return 0;
}

void freeButtons() 
{
    int i;
    for (i = 0; i < buttonCount; i++) {
        free(buttons[i]->buttonText);
        free(buttons[i]);
    }
}

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
    handleMainMenuButtons(buttons, buttonCount);
}

void handleMainMenuButtons(Button *buttonList[], int buttonCount) 
{
    int i;
    for (i = 0; i < buttonCount; i++) {
        Button *currButton = buttonList[i];
        DrawRectangleRounded(
            currButton->rect, 
            currButton->roundness, 
            0, 
            CheckCollisionPointRec(GetMousePosition(), currButton->rect) ? currButton->activeColour : currButton->inactiveColour
        );
        DrawText(
            currButton->buttonText->labelText, 
            currButton->buttonText->textX,
            currButton->buttonText->textY,
            currButton->buttonText->fontSize,
            currButton->buttonText->textColour
        );

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), currButton->rect)) {
            if (currButton->buttonText->labelText == MAINMENU_START) {
                setScreenToGame();
            }
            if (currButton->buttonText->labelText == MAINMENU_HELP) {
                setScreenToHelp();
            }
        }
    }
}