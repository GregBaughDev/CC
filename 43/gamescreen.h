#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#define GAMEAREA_START_X 250
#define GAMEAREA_START_Y 100
#define GAMEAREA_END_X 525
#define GAMEAREA_END_Y 650
#define NEXTPIECE_START_X 50
#define NEXTPIECE_START_Y 100
#define NEXTPIECE_END_X 200
#define NEXTPIECE_END_Y 250

void initialiseGameScreen();
void drawGame();
void handleGame();
void freeGame();

#endif