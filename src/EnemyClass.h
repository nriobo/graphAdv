//EnemyClass.h
#pragma once
#include <allegro.h>

#define LEFT          4
#define RIGHT        6
#define DOWN        2
#define UP              8

class EnemyClass
{
    public:
        float x, y, speed, maxSpeed, frame;
        int w, h;
        int dir;
        int jumpTime;
        int jumpMax;
        int airTime;
        int correctY;      // factor de correccion para las Y
        int frames;
        bool alive;
        bool jumping;
        bool doubleJumping;
        bool falling;
        bool dying;
        bool loopAnimation;
        int justKilledTime;
        void Draw(BITMAP*, BITMAP*, float, float);
        void DrawAnim(BITMAP*, BITMAP*, float, float, int animW, int animH, int framesAnim);
        void Move(int);
        void NextFrame();
        void Update();
        void Animate(BITMAP *buffer, BITMAP *sprite, int framesAnim, int wAnim, int hAnim, float offsetX, float offsetY);
        EnemyClass();
};




