#include <stdlib.h>
#include <stdio.h>
#include "buttons.h"
#include "main.h"

const int BUTTON_WIDTH = 300;
int BUTTON_HEIGHT = 50;
int ROUNDNESS = 2;
int BUTTON_POS = (WINDOW_WIDTH / 2) - (BUTTON_WIDTH / 2);

Button *createButton(int buttonYPos, char *labelText) 
{
    Button *button = malloc(sizeof(Button));
    if (button == NULL) {
        printf("Malloc startButton failed");
        exit(-1);
    }

    button->buttonText = malloc(sizeof(ButtonText));
    if (button->buttonText == NULL) {
        printf("Malloc buttonText failed");
        exit(-1);
    }

    button->rect.x = BUTTON_POS;
    button->rect.y = buttonYPos;
    button->rect.width = BUTTON_WIDTH;
    button->rect.height = BUTTON_HEIGHT;
    button->inactiveColour = GRAY;
    button->activeColour = DARKBLUE;
    button->roundness = ROUNDNESS;
    button->buttonText->labelText = labelText;
    button->buttonText->textColour = TEXT_COLOUR;
    button->buttonText->textX = (WINDOW_WIDTH / 2) - (MeasureText(labelText, FONT_SIZE_SECONDARY) / 2);
    button->buttonText->textY = buttonYPos + 15;
    button->buttonText->fontSize = FONT_SIZE_SECONDARY;

    return button;
}

void drawButton(Button *button) 
{
    DrawRectangleRounded(
        button->rect, 
        button->roundness, 
        0, 
        CheckCollisionPointRec(GetMousePosition(), button->rect) ? button->activeColour : button->inactiveColour
    );
    DrawText(
        button->buttonText->labelText, 
        button->buttonText->textX,
        button->buttonText->textY,
        button->buttonText->fontSize,
        button->buttonText->textColour
    );
}