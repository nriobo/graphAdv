//LevelClass.h
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <allegro.h>
#include "TileClass.h"
#include <stdio.h>
#include "Constants.h"

#define posYphrase1 300
#define posYphrase2 320
#define posYphrase3 340
#define posYphrase4 360

using namespace std;

const int TILEX = 20;
const int TILEY = 9;
const int LAYERS = 3;

const int SCR_W = 640;
const int SCR_H = 400;

typedef struct
{
       int item; // item to interact with
       int serial; // serial # of that phrase
       char *phrase;
       bool alreadySaid;
       int nextAnswer;
       bool everlasting;
} playerPhrases;

typedef struct
{
       int serial;
       char *phrase;
       bool alreadySaid;       
       bool continueDialog;
} itemPhrases;

typedef struct
{
       char texto[10];
       int x, y, w, h, binary;
} Action;

typedef struct
{
       char texto[80];
       int x, y, w, h, serial;
} PhraseToSay;



class LevelClass
{
    public:
        Action Actions[NUMBER_ACTIONS];
        PhraseToSay PhrasesShown[4];
        TileClass tile[LAYERS][TILEX][TILEY];
        BITMAP *background;
        void LoadMap(string filename, int level);
        void DrawBottom(BITMAP *buffer, float, float);
        void DrawItems(BITMAP *buffer, char *textLives, char *textCoins);
        void WriteLine(BITMAP *buffer, char *text);
        void WriteLine(BITMAP *buffer, char *text, bool line2);
        void WriteLine(BITMAP *buffer, char *text, int r, int g, int b);
        void WriteLine(BITMAP *buffer, char *text, bool line2, int r, int g, int b);
        void setBackground(BITMAP *newBg);
        char* GetActionName(int actionNumber);
        void createActions(void);
        void createPhrases(playerPhrases *plPh, int theItem, int length);
        int CheckCollisionPhrases(int mouseX, int mouseY);
        void ShowPhrases(BITMAP *buffer);
        void ShowActions(BITMAP *buffer);
        int CheckCollisionActions(int mouseX, int mouseY);
        int CheckCollisionCollected(int mouseX, int mouseY, int itemsSoFar);
        int CheckCollisionArrows(int mouseX, int mouseY, int gameTimer, int itemsSoFar);
        bool scrollableScreen;
        int centerText(char *text);
        int centerAction(char *text, int column);
        int GetActionBinary(int actionNumber);
        void DrawCollected(BITMAP *buffer, BITMAP *sprite, int *itemsCollected, int itemsSoFar);
        FONT *theFont;        
        FONT *theFontSmaller;
        BITMAP *spriteArrowU, *spriteArrowD;
        int itemsCollectedStartPosition;
        int gameTimerTemp;
};
