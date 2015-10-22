//main.h
#pragma once
#include <iostream>
#include <allegro.h>
#include "Constants.h"
#include "LevelClass.h"
#include "PlayerClass.h"
#include "ItemsClass.h"

volatile long speedCounter = 0;
bool musicOn;
bool showActions = true;
bool showPhrases = false;
MIDI *the_music;
char itemSelected[20];
int itemSelectedNumber;
int itemClickedNumber;
int itemToUseNumber = -1;
char actionSelected[20];
char actionDebug[80];
char actionDebugLine2[80];
int actionResult;
char textShown[40];
int actionSelectedNumber;
int itemCollectedSelected = -1;
int activeLevel = 0;
ItemsClass mousePointer;
int itemsInLevel[NUMBER_LEVELS][ITEMS_PER_LEVEL];
int itemsUsable [][2]= {{9, 0}, {7, 5}};

void showMouse(void);
void hideMouse(void);
void incrementCounter();
void initCrap(bool);
bool CheckCollision(const PlayerClass *player, int direction, const LevelClass *level);
bool checkCollisionItem(const PlayerClass *player, const ItemsClass *item);
bool checkCollisionItem(int mouseX, int mouseY, int mouseW, int mouseH, const ItemsClass *item);
bool checkCanUse(int item1, int onItem2, bool *gameActions, ItemsClass *item);
void Update(float *offsetX, float *offsetY, PlayerClass *player);
void startMusic(void);
void stopMusic(void);
BITMAP *createMouse(BITMAP *originalMouse);
BITMAP *changeMousePointer(BITMAP*, int*, int);

