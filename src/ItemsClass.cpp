//ItemsClass.cpp
#include "ItemsClass.h"

ItemsClass::ItemsClass()
{
    speed = 1.2;
    frameSpeed = 0.3;
    frame = 0;
    falling = false;
    canEnter = false;       // analyse situation: bool canPickUp, bool canUse...
                            // instead of a whole byte for each action
    alive = true;
    loopAnimation = true;
    drawTop = false;
    actionDoable = 0x1000;  // by default we can walk to things

    // clear all responses to avoid any rubbish in them
    for (int i=0; i<NUMBER_ACTIONS; i++)
    {
      responseNo[i][0] = 0;
      responseYes[i][0] = 0;
    }
}

void ItemsClass::DrawAnim(BITMAP *buffer, BITMAP *sprite, float offsetX, float offsetY, int animW, int animH, int framesAnim)
{
    frames = framesAnim;
    masked_blit(sprite, buffer, (int)frame*animW, 0, (int)x - (int)offsetX, (int)y - (int)offsetY - correctY, animW, animH);
}

void ItemsClass::Update()
{
    NextFrame();
}

void ItemsClass::NextFrame()
{
     if (frame <= frames)
     {
         if (falling)
           frame = frames;
         else
           frame += frameSpeed;

         if ( frame > frames && loopAnimation)
           frame = 0;
     }
}
