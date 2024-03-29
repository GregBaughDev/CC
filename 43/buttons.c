#include <stdlib.h>
#include <stdio.h>
#include "buttons.h"
#include "main.h"

const int BUTTON_WIDTH = 300;
int BUTTON_HEIGHT = 50;
int ROUNDNESS = 2;
int BUTTON_POS = (WINDOW_WIDTH / 2) - (BUTTON_WIDTH / 2);

Button *createButton(int buttonYPos, char *labelText, int textYPos) 
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
    button->buttonText->textY = textYPos;
    button->buttonText->fontSize = FONT_SIZE_SECONDARY;

    return button;
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
            printf("Button pressed!: %s\n", currButton->buttonText->labelText); // check the button against string enum
        }
    }
}