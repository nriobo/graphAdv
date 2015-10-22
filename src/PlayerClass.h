//PlayerClass.h
#pragma once
#include <allegro.h>
#include "Constants.h"

class PlayerClass
{
    public:
        float x, y, speed, maxSpeed, frame, frameSpeaking;
        float destX, destY, lastPosX, lastPosY;
        int w, h;
        int dir;
        int correctY;      // factor de correccion para las Y
        int frames;
        int framesSpeaking;
        int speakTime;

        int itemSpeakTime;
        bool itemSpeaking;
        
        int itemsCollected[MAX_ITEMS_COLLECTED];
        int itemsSoFar;
        bool walking;
        bool speaking;
        bool alive;
        void Draw(BITMAP*, BITMAP*, float, float);
        void DrawSpeaking(BITMAP *buffer, BITMAP *sprite, float offsetX, float offsetY);
        void Move(int);
        void NextFrame();
        void Update();
        PlayerClass();
        void AddItemCollected(int itemNumber);
};
