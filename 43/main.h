#ifndef _MAIN_H
#define _MAIN_H
#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH_HALF 400

extern Color TEXT_COLOUR;
extern int FONT_SIZE;
extern int FONT_SIZE_SECONDARY;
extern int FONT_SIZE_THIRD;

void setScreenToMainMenu(void);
void setScreenToGame(void);
void setScreenToHelp(void);

#endif