#include "TXLib.h"

struct Pig
    {
    double xP,  yP,
          vxP, vyP;
    double SizeP;
    };

void BirdDraw    (double x, double y, double Size);
void PigDraw     (double x, double y, double Size);

void PhysicsBird (double* x, double* y, double* vx, double* vy, int ay, int dt, double Size);
void PhysicsPig  (double* x, double* y, double* vx, double* vy, int ay, int dt, double Size);

void BirdMove();



int main ()
    {
    txCreateWindow (1000, 600);
    BirdMove();
    return 0;
    }

void BirdMove()
    {
    double x = 270, y = 270,
       vx = 0,  vy = 0;
    int Size = 1;
    int ay = 1;
    int dt = 1;

    Pig pig1 = {.xP = 200, .yP = 300, .vxP =  0, .vyP =  0, .SizeP = 1};
    Pig pig2 = {.xP = 100, .yP = 100, .vxP =  0, .vyP =  0, .SizeP = 0.5};

    HDC Background  = txLoadImage ("images\\phon.bmp");

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txBitBlt (txDC(), 0, 0, 1000, 600, Background, 0, 0);

        BirdDraw (x, y, Size);
        PigDraw (pig1.xP, pig1.yP, pig1.SizeP);
        PigDraw (pig2.xP, pig2.yP, pig2.SizeP);
        PhysicsBird (&x, &y, &vx, &vy, ay, dt, Size);
        txSleep (10);
        }
    txDeleteDC (Background);
    }

void PhysicsBird (double* x, double* y, double* vx, double* vy, int ay, int dt, double Size)
    {
    *vy += ay * dt;

    *x += *vx * dt;
    *y += *vy * dt;

    *vx = (*vx) * 0.99;  // уменьшение по 0X всегда за счет сопротивления воздуха
    *vy = (*vy) * 0.99;  // уменьшение по 0Y
    // при полете вверх замедляющая составляющая: ay + a(сопротивления воздуха)
    // при полете вниз ускоряющая составляющая: ay - a(сопротивления воздуха)

    if (*x > (1000 - 70*Size))
        {
        *vx = - *vx;
        *x  = 2 * (1000 - 70*Size) - *x;
        }

    if (*y > (600 - 70*Size))
        {
        *vy = - *vy;
        *y  = 2 * (600 - 70*Size) - *y;
        }

    if (*x < (0 + 70*Size))
        {
        *vx = - *vx;
        *x  = 2 * 70*Size - *x;
        }

    if (*y < (0 + 70*Size))
        {
        *vy = - *vy;
        *y  = 2 * 70*Size - *y;
        }
    }

void PhysicsPig (double* x, double* y, double* vx, double* vy, int ay, int dt, double Size)
    {
    *vy += ay * dt;

    *x += *vx * dt;
    *y += *vy * dt;

    *vx = (*vx) * 0.99;  // уменьшение по 0X всегда за счет сопротивления воздуха
    *vy = (*vy) * 0.99;  // уменьшение по 0Y
    // при полете вверх замедляющая составляющая: ay + a(сопротивления воздуха)
    // при полете вниз ускоряющая составляющая: ay - a(сопротивления воздуха)

    if (*x > (1000 - 70*Size))
        {
        *vx = - *vx;
        *x  = 2 * (1000 - 70*Size) - *x;
        }

    if (*y > (600 - 70*Size))
        {
        *vy = - *vy;
        *y  = 2 * (600 - 70*Size) - *y;
        }

    if (*x < (0 + 70*Size))
        {
        *vx = - *vx;
        *x  = 2 * 70*Size - *x;
        }

    if (*y < (0 + 70*Size))
        {
        *vy = - *vy;
        *y  = 2 * 70*Size - *y;
        }

    }

void BirdDraw (double x, double y, double Size)
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

void PigDraw (double x, double y, double Size)
    {
    txSetColor (RGB (0, 100, 0));
    txSetFillColor (TX_GREEN);
    txEllipse (x - 32*Size, y - 60*Size, x - 18*Size, y - 35*Size);
    txEllipse (x + 32*Size, y - 60*Size, x + 18*Size, y - 35*Size);

    txSetFillColor (TX_BLACK);
    txEllipse (x - 36*Size, y - 55*Size, x - 14*Size, y + 8*Size);
    txEllipse (x + 36*Size, y - 55*Size, x + 14*Size, y + 8*Size);

    txSetFillColor (TX_GREEN);
    txCircle (x, y, 50*Size);

    txSetColor (RGB (0, 100, 0));
    txSetFillColor (TX_WHITE);
    txCircle (x + 40*Size, y - 5*Size, 10*Size);
    txCircle (x - 40*Size, y - 5*Size, 10*Size);

    txSetFillColor (TX_BLACK);
    txCircle (x - 43*Size, y - 5*Size, 5*Size);
    txCircle (x + 43*Size, y - 5*Size, 5*Size);

    txSetFillColor (RGB(100, 200, 100));
    txEllipse (x - 28*Size, y - 20*Size, x + 28*Size, y + 25*Size);

    txSetFillColor (TX_BLACK);
    txEllipse (x - 15*Size, y - 7*Size, x -  3*Size, y + 8*Size);
    txEllipse (x +  4*Size, y - 2*Size, x + 11*Size, y + 8*Size);

    txSetFillColor (TX_RED);
    txCircle (x - 6*Size, y + 35*Size, 5*Size);
    }
