//PlayerClass.cpp
#include "PlayerClass.h"

PlayerClass::PlayerClass()
{
    speed = 1.3;
    frame = 0;
    frameSpeaking = 0;
    dir = RIGHT;
    speaking = false;
    alive = true;
    speakTime = 0;
    itemsCollected[0] = -1;
    itemsSoFar = 0;
    framesSpeaking = 2;

    itemSpeakTime = 0;
    itemSpeaking = false;
        
}

void PlayerClass::Draw(BITMAP *buffer, BITMAP *sprite, float offsetX, float offsetY)
{
    //void masked_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
    if ( dir == LEFT )
        masked_blit(sprite, buffer, (int)frame*w, 0, (int)x - (int)offsetX, (int)y - (int)offsetY - correctY, w, h);
    else if ( dir == DOWN )
        masked_blit(sprite, buffer, (int)frame*w, h, (int)x - (int)offsetX, (int)y - (int)offsetY - correctY, w, h);
    else if ( dir == RIGHT )
        masked_blit(sprite, buffer, (int)frame*w, 2*h, (int)x - (int)offsetX, (int)y - (int)offsetY - correctY, w, h);
    else if ( dir == UP )
        masked_blit(sprite, buffer, (int)frame*w, 3*h, (int)x - (int)offsetX, (int)y - (int)offsetY - correctY, w, h);
//    rect(buffer, x - offsetX, y - offsetY, x+w - offsetX, y+h - offsetY, makecol(255, 255, 0));        // debug
}

void PlayerClass::DrawSpeaking(BITMAP *buffer, BITMAP *sprite, float offsetX, float offsetY)
{
     // toDo...
//     if (walking)
//     {
//        //void masked_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
//        if ( dir == LEFT )
//            masked_blit(sprite, buffer, (int)frameSpeaking*40, 0, x - offsetX, y - offsetY - correctY, 40, h);
//        else if ( dir == DOWN )
//            masked_blit(sprite, buffer, (int)frameSpeaking*40, h, x - offsetX, y - offsetY - correctY, 40, h);
//        else if ( dir == RIGHT )
//            masked_blit(sprite, buffer, (int)frameSpeaking*40, 2*h, x - offsetX, y - offsetY - correctY, 40, h);
//        else if ( dir == UP )
//            masked_blit(sprite, buffer, (int)frameSpeaking*40, 3*h, x - offsetX, y - offsetY - correctY, 40, h);
//     }
//     else
     if (!walking)
     {
         if ( dir == UP )
           masked_blit(sprite, buffer, (int)frameSpeaking*40, 3*h, (int)x - (int)offsetX, (int)y - (int)offsetY - correctY, 40, h);
         else
           masked_blit(sprite, buffer, (int)frameSpeaking*40, h, (int)x - (int)offsetX, (int)y - (int)offsetY - correctY, 40, h);
     }
//    rect(buffer, x - offsetX, y - offsetY, x+w - offsetX, y+h - offsetY, makecol(255, 255, 0));
}

void PlayerClass::Update()
{
     NextFrame();
}

void PlayerClass::Move(int direction)
{
    walking = true;
    dir = direction;
    NextFrame();
    
    lastPosX = x;
    lastPosY = y;
    
    if ( direction == LEFT )
    {
        x -= speed;
    }
    else if ( direction == RIGHT )
    {
        x += speed;
    }
    else if ( direction == DOWN )
    {
        y += speed;
    }
    else if ( direction == UP )
    {
        y -= speed;
    }
}

void PlayerClass::NextFrame()
{
   if (walking)
   {
       frame += 0.1;
       if ( frame > frames )
         frame = 0;
   }
   else
     frame = frames;
   
   if (speaking)
   {
     frameSpeaking += 0.1;
     if (frameSpeaking > framesSpeaking)
       frameSpeaking = 0;           
   }
}

void PlayerClass::AddItemCollected(int itemNumber)
{
     for (int i=0; i<MAX_ITEMS_COLLECTED; i++)
     {
         if (itemsCollected[i] == -1)
         {
           itemsCollected[i] = itemNumber;
           itemsCollected[i+1] = -1;
           i = MAX_ITEMS_COLLECTED;
         }
     }
}
