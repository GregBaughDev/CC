#include "buttons.h"
#include <stdio.h>

Button *buttons[];
int buttonCount = 2;

void initialise(void) {
    Button *startButton = malloc(sizeof(Button));
    if (startButton == NULL) {
        printf("Malloc startButton failed");
        return -1;
    }
    *startButton = createButton(150, MAINMENU_START, 165);

    Button *helpButton = malloc(sizeof(Button));
    if (helpButton == NULL) {
        printf("Malloc helpButton failed");
        return -1;
    }
    *helpButton = createButton(250, MAINMENU_HELP, 265);

    *buttons[0] = *startButton;
    *buttons[1] = *helpButton;
}

void handleButtons(void) {
    handleMainMenuButtons(buttons, buttonCount);
}