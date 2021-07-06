#include "TXLib.h"

//void BirdDraw (double x, double y, double Size);

//void BirdSpeed (double* vx, double* vy);

//void PhysicsBird (double* x, double* y, double* vx, double* vy, int* ay, int dt, double Size);

struct Bird
    {
    double x, y;
    double vx, vy;
    int ay;

    //int anim;

    //int live;
    //int glass;

    void Draw (int frame);
    void Physics (int dt);
    void Speed ();
    };

//{-----------------------------------------------------------------------------
//! Функция рисования заданного кадра персонажа при помощи спрайтовой анимации
//!
//! @param frame  кадр анимации персонажа при движении
//!
//}-----------------------------------------------------------------------------
void Bird::Draw (int frame)
    {
    txTransparentBlt (txDC(), x, y, X_BIRD, Y_BIRD, SPRITE_BIRD, (frame % 5)*X_BIRD, 0*Y_BIRD, RGB(192,192,192));
    }
/*
//{-----------------------------------------------------------------------------
//! Функция управления движением персонажа
//!
//! @param frame  кадр анимации персонажа при движении
//!
//}-----------------------------------------------------------------------------
void Bird::Control ()
    {
    if (txGetAsyncKeyState (VK_RIGHT) )
        {
        (*this).x += STEP;
        (*this).anim = PERSON_RIGHT;
        }
    if (txGetAsyncKeyState (VK_LEFT ) )
        {
        (*this).x -= STEP;
        (*this).anim = PERSON_LEFT;
        }
    if (txGetAsyncKeyState (VK_UP   ) )
        {
        (*this).y -= STEP;
        (*this).anim = PERSON_UP;
        }
    if (txGetAsyncKeyState (VK_DOWN ) )
        {
        (*this).y += STEP;
        (*this).anim = PERSON_DOWN;
        }
    }*/

void Bird::Physics (int dt)
    {
    (*this).vy += (*this).ay * dt;

    (*this).x += (*this).vx * dt;
    (*this).y += (*this).vy * dt;

    (*this).vx = ((*this).vx) * 0.99;  // уменьшение по 0X всегда за счет сопротивления воздуха
    (*this).vy = ((*this).vy) * 0.99;  // уменьшение по 0Y
    // при полете вверх замедляющая составляющая: ay + a(сопротивления воздуха)
    // при полете вниз ускоряющая составляющая: ay - a(сопротивления воздуха)

    if ((*this).x > (1000 - X_BIRD))
        {
        (*this).vx = - (*this).vx;
        (*this).x  = 2 * (1000 - X_BIRD) - (*this).x;
        }

    if ((*this).y > (550 - X_BIRD))
        {
        (*this).vy = - (*this).vy;
        (*this).y  = 2 * (550 - X_BIRD) - (*this).y;
        }

    if ((*this).x < (0 + X_BIRD))
        {
        (*this).vx = - (*this).vx;
        (*this).x  = 2 * X_BIRD - (*this).x;
        }

    if ((*this).y < (0 + X_BIRD))
        {
        (*this).vy = - (*this).vy;
        (*this).y  = 2 * X_BIRD - (*this).y;
        }

    if (((*this).vy > - 0.06) && ((*this).vy < 0.06) && ((*this).y > (550 - X_BIRD)))
        {
        (*this).ay = 0;
        (*this).vx = 0;
        }
    }

void Bird::Speed ()
    {
    if (txGetAsyncKeyState (VK_UP))    (*this).vy -=1;
    if (txGetAsyncKeyState (VK_DOWN))  (*this).vy +=1;
    if (txGetAsyncKeyState (VK_LEFT))  (*this).vx -=1;
    if (txGetAsyncKeyState (VK_RIGHT)) (*this).vx +=1;
    }

/*void BirdDraw (double x, double y, double Size)
    {
    txSetColor (RGB (100, 0, 0));
    txSetFillColor (TX_RED);
    txEllipse (x - 18*Size, y - 90*Size, x -  5*Size, y - 55*Size);
    txEllipse (x - 40*Size, y - 75*Size, x - 10*Size, y - 65*Size);

    txSetFillColor (RGB (50, 0, 0));
    POINT tail1[] ={ {ROUND(x - 85*Size), ROUND(y + 2*Size)},
                     {ROUND(x - 79*Size), ROUND(y - 7*Size)},
                     {ROUND(x - 67*Size), ROUND(y + 5*Size)} };
    txPolygon (tail1, 3);

    POINT tail2[] ={ {ROUND(x -  94*Size), ROUND(y +  4*Size)},
                     {ROUND(x -  64*Size), ROUND(y + 12*Size)},
                     {ROUND(x - 100*Size), ROUND(y + 23*Size)} };
    txPolygon (tail2,3);

    POINT tail3[] ={ {ROUND(x - 81*Size), ROUND(y + 21*Size)},
                     {ROUND(x - 64*Size), ROUND(y + 15*Size)},
                     {ROUND(x - 78*Size), ROUND(y + 32*Size)} };
    txPolygon (tail3, 3);

    txSetFillColor (TX_RED);
    txCircle (x, y, 70*Size);

    txSetFillColor (RGB(220, 190, 165));
    txPie (x - 70*Size, y - 70*Size, x + 70*Size, y + 70*Size, 230, 120);

    txSetColor (TX_RED);
    txSetFillColor (TX_RED);
    POINT belly[] ={ {ROUND(x - 35*Size), ROUND(y + 36*Size)},
                     {ROUND(x + 69*Size), ROUND(y + 12*Size)},
                     {ROUND(x),            ROUND(y)} };
    txPolygon (belly, 3);


    txSetColor (RGB (100, 0, 0));
    txSetFillColor (TX_WHITE);
    txCircle (x + 44*Size, y + 3*Size, 15*Size);
    txCircle (x + 15*Size, y + 3*Size, 15*Size);

    txSetFillColor (TX_BLACK);
    txCircle (x + 20*Size, y + 2*Size, 5*Size);
    txCircle (x + 41*Size, y + 2*Size, 5*Size);

    txSetFillColor (TX_WHITE);
    txCircle (x + 22*Size, y, 2*Size);
    txCircle (x + 43*Size, y, 2*Size);

    txSetFillColor (RGB (50, 0, 0));
    POINT eyebrows[] ={ {ROUND(x -  6*Size), ROUND(y - 23*Size)},
                        {ROUND(x -  6*Size), ROUND(y -  3*Size)},
                        {ROUND(x + 62*Size), ROUND(y -  3*Size)},
                        {ROUND(x + 61*Size), ROUND(y - 23*Size)},
                        {ROUND(x + 31*Size), ROUND(y - 13*Size)} };
    txPolygon (eyebrows, 5);

    txSetFillColor (TX_ORANGE);
    POINT beak1[] ={ {ROUND(x +  12*Size), ROUND(y + 24*Size)},
                     {ROUND(x +  48*Size), ROUND(y + 27*Size)},
                     {ROUND(x +  25*Size), ROUND(y + 32*Size)} };
    txPolygon (beak1, 3);
    POINT beak2[] ={ {ROUND(x +  8*Size), ROUND(y + 24*Size)},
                     {ROUND(x + 59*Size), ROUND(y + 30*Size)},
                     {ROUND(x + 29*Size), ROUND(y +  6*Size)} };
    txPolygon (beak2, 3);
    }
*/
