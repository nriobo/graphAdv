//ItemsClass.h
#pragma once
#include <allegro.h>
#include "Constants.h"

struct Responses
{
  char texto[80];
  int action;
};

class ItemsClass
{
    public:
        float x, y, speed, maxSpeed, frame;
        float frameSpeed;
        int correctY;      // factor de correccion para las Y
        int frames;
        int w, h;
        int dir, nextRoom;
        int actionDoable; 
        bool alive;
        bool canEnter;
        bool falling;
        bool loopAnimation;
        bool drawTop;
        void DrawAnim(BITMAP*, BITMAP*, float, float, int animW, int animH, int framesAnim);
        void NextFrame();
        void Update();
        ItemsClass();
        char responseNo[NUMBER_ACTIONS][80];
        char responseYes[NUMBER_ACTIONS][80];
        char name[20];
};
