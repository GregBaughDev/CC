#ifndef BUTTONS_H
#define BUTTONS_H
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

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 50;

// Main Menu Buttons
const char* MAINMENU_START = "Start";
const char* MAINMENU_HELP = "Help";
const int ROUNDNESS = 2;
int FONT_SIZE = 20;

const int BUTTON_POS = (WINDOW_WIDTH / 2) - (BUTTON_WIDTH / 2);

Button createButton(int buttonYPos, char *labelText, int textYPos) {
    Button button = {
        .rect = {
            .x = BUTTON_POS,
            .y = buttonYPos,
            .width = BUTTON_WIDTH,
            .height = BUTTON_HEIGHT
        },
        .inactiveColour = GRAY,
        .activeColour = DARKBLUE,
        .roundness = ROUNDNESS,
        .buttonText = &(ButtonText){
            .labelText = labelText,
            .textColour = TEXT_COLOUR,
            .textX = (WINDOW_WIDTH / 2) - (MeasureText(labelText, FONT_SIZE_SECONDARY) / 2),
            .textY = textYPos,
            .fontSize = FONT_SIZE_SECONDARY
        }
    };
    return button;
}

// move this all to initialise and create the buttons and pass
// around the buttons list.
// Button startButton = createStackButton(150, MAINMENU_START, 165);

// const Button *buttons = {};

// const Button startButton = { 
//     .rect = { 
//         .x = BUTTON_POS, 
//         .y = 150, 
//         .width = BUTTON_WIDTH, 
//         .height = BUTTON_HEIGHT
//     },
//     .inactiveColour = GRAY,
//     .activeColour = DARKBLUE,
//     .roundness = ROUNDNESS,
//     .buttonText = &(ButtonText){ 
//         .labelText = "Start", 
//         .textColour = TEXT_COLOUR,
//         .textX = (WINDOW_WIDTH / 2) - (MeasureText("Start", FONT_SIZE_SECONDARY) / 2),
//         .textY = 165,
//         .fontSize = FONT_SIZE_SECONDARY
//     }
// };

// const Button helpButton = {
//     .rect = {
//         .x = BUTTON_POS,
//         .y = 250,
//         .width = BUTTON_WIDTH,
//         .height = BUTTON_HEIGHT
//     },
//     .inactiveColour = GRAY,
//     .activeColour = DARKBLUE,
//     .roundness = ROUNDNESS,
//     .buttonText = {
//         .labelText = MAINMENU_HELP,
//         .textColour = TEXT_COLOUR,
//         .textX = (WINDOW_WIDTH / 2) - (MeasureText(MAINMENU_HELP, FONT_SIZE_SECONDARY) / 2),
//         .textY = 265,
//         .fontSize = FONT_SIZE_SECONDARY
//     }
// };

// const Button *buttons[] = { &startButton, &helpButton };
// const int buttonCount = 2;

#endif