#include "buttons.h"
#include "raylib.h"

void handleMainMenuButtons(Button *buttonList[], int buttonCount) {
    int i;
    for (i = 0; i < buttonCount; i++) {
        Button *currButton = *(buttonList + i);
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
    }
}