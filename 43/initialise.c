#include <stdio.h>
#include <stdlib.h>
#include "buttons.h"
#include "initialise.h"

const int buttonCount = 2;
Button *buttons[2];

char* MAINMENU_START = "Start";
char* MAINMENU_HELP = "Help";

int initialise() 
{
    // Create main menu buttons
    Button *startButton = createButton(150, MAINMENU_START, 165);
    Button *helpButton = createButton(250, MAINMENU_HELP, 265);

    buttons[0] = startButton;
    buttons[1] = helpButton;

    return 0;
}

void handleButtons() 
{
    handleMainMenuButtons(buttons, buttonCount);
}

void freeButtons() 
{
    int i;
    for (i = 0; i < buttonCount; i++) {
        free(buttons[i]->buttonText);
        free(buttons[i]);
    }
}