#ifndef _BUTTONS_H
#define _BUTTONS_H
#include "raylib.h"
#include "main.h"

typedef struct ButtonText {
    Color textColour;
    int textX;
    int textY;
    int fontSize;
    const char* labelText;
} ButtonText;

typedef struct Button {
    Rectangle rect;
    Color inactiveColour;
    Color activeColour;
    float roundness;
    ButtonText *buttonText;
} Button;

void handleMainMenuButtons(Button *buttonList[], int buttonCount);
Button *createButton(int buttonYPos, char *labelText, int textYPos);

#endif