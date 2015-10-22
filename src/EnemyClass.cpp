//EnemyClass.cpp
#include "EnemyClass.h"

EnemyClass::EnemyClass()
{
    speed = 1.2;
    frame = 0;
    dir = RIGHT;
    jumping = doubleJumping = false;
    falling = true;
    dying = false;
    jumpMax = 50;
    justKilledTime = 0;
    alive = true;
    loopAnimation = true;
}

void EnemyClass::Draw(BITMAP *buffer, BITMAP *sprite, float offsetX, float offsetY)
{
    if ( dir == LEFT )
        masked_blit(sprite, buffer, (int)frame*w, 0, x - offsetX, y - offsetY - correctY, w, h);
    else
        masked_blit(sprite, buffer, (int)frame*w, h, x - offsetX, y - offsetY - correctY, w, h);
}

void EnemyClass::DrawAnim(BITMAP *buffer, BITMAP *sprite, float offsetX, float offsetY, int animW, int animH, int framesAnim)
{
    frames = framesAnim;
    if ( dir == LEFT )
        masked_blit(sprite, buffer, (int)frame*w, 0, x - offsetX, y - offsetY - correctY, animW, animH);
    else
        masked_blit(sprite, buffer, (int)frame*w, animH, x - offsetX, y - offsetY - correctY, animW, animH);
}


void EnemyClass::Update()
{
	// TBD
}

void EnemyClass::Move(int direction)
{
    dir = direction;
    NextFrame();
    if ( direction == LEFT && alive)
    {
        x -= speed;
    }
    else if ( direction == RIGHT && alive)
    {
        x += speed;
    }
}

void EnemyClass::NextFrame()
{
     if (frame <= frames)
     {
         if (falling)
           frame = frames;
         else
           frame += 0.1;
           if ( frame > frames && loopAnimation)
             frame = 0;
     }
}
