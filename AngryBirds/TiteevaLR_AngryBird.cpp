#include "TXLib.h"

struct Pig
    {
    double xP,  yP,
          vxP, vyP;
    double SizeP;
    };
void TabloScore (int* score);

void BirdDraw (double x, double y, double Size);
void PigDraw  (double x, double y, double Size);

void BirdSpeed (double* vx, double* vy);

void PhysicsBird (double* x, double* y, double* vx, double* vy, int* ay, int dt, double Size);
void PhysicsPig  (double* x, double* y, double* vx, double* vy, int* ay, int dt, double Size);

bool WasCollision (double x, double y, double r, double xP, double yP, double rP);

void Collision    (double  x,  double y,  double* vx,  double* vy,
                   double  xP, double yP, double* vxP, double* vyP);

void GameMove();



int main ()
    {
    txCreateWindow (1000, 600);

    GameMove();

    return 0;
    }

void GameMove()
    {
    int score = 5;
    Pig pig1 = {.xP = 500, .yP = 300, .vxP =  0, .vyP =  0, .SizeP = 1};
    Pig pig2 = {.xP = 400, .yP = 100, .vxP =  0, .vyP =  0, .SizeP = 0.5};

    HDC Background  = txLoadImage ("images\\background.bmp");
    while (score >= 1)
        {
        double x = 110, y = 400,
           vx = 0,  vy = 0;
        double Size = 0.5;
        int ay = 1;
        int dt = 1;

        while (!txGetAsyncKeyState (VK_LMENU))
            {
            txBitBlt (txDC(), 0, 0, 1000, 600, Background, 0, 0);

            BirdDraw (x, y, Size);

            PigDraw (pig1.xP, pig1.yP, pig1.SizeP);
            PigDraw (pig2.xP, pig2.yP, pig2.SizeP);

            BirdSpeed(&vx, &vy);

            txLine (x, y, x + vx, y + vy);

            TabloScore (&score);
            txSleep (10);
            }
        score -= 1;

        while (!txGetAsyncKeyState (VK_ESCAPE))
            {
            txBitBlt (txDC(), 0, 0, 1000, 600, Background, 0, 0);

            TabloScore (&score);
            BirdDraw (x, y, Size);

            PigDraw (pig1.xP, pig1.yP, pig1.SizeP);
            PigDraw (pig2.xP, pig2.yP, pig2.SizeP);

            PhysicsBird (&x, &y, &vx, &vy, &ay, dt, Size);
            PhysicsPig (&pig1.xP, &pig1.yP, &pig1.vxP, &pig1.vyP, &ay, dt, pig1.SizeP);
            PhysicsPig (&pig2.xP, &pig2.yP, &pig2.vxP, &pig2.vyP, &ay, dt, pig2.SizeP);

            if (WasCollision (x, y, 70*Size, pig1.xP, pig1.yP, 50*pig1.SizeP))
                {
                Collision (x, y, &vx, &vy, pig1.xP, pig1.yP, &pig1.vxP, &pig1.vyP);
                }
            if (WasCollision (x, y, 70*Size, pig2.xP, pig2.yP, 50*pig2.SizeP))
                {
                Collision (x, y, &vx, &vy, pig2.xP, pig2.yP, &pig2.vxP, &pig2.vyP);
                }

            if ((vy > - 0.09) && (vy < 0.09) && (y > (500 - 50*Size)))
                {
                break;
                }
            txSleep (10);
            }
        }
    txDeleteDC (Background);
    txSetColor(TX_MAGENTA);
    txSelectFont ("Arial Black", 70);
    txTextOut (100, 350, "GAME OVER");
    }

void Collision (double  x, double y, double* vx, double* vy, double  xP, double yP, double* vxP, double* vyP)
    {
    double dx = x - xP, dy = y - yP;
    double sinA = dx / sqrt (dx * dx + dy * dy);
    double cosA = dy / sqrt (dx * dx + dy * dy);

    double vn  =  (*vxP) * sinA + (*vyP) * cosA;
    double vnP =  (*vx)  * sinA + (*vy)  * cosA;
    double vt  = -(*vxP) * cosA + (*vyP) * sinA;
    double vtP = -(*vx)  * cosA + (*vy)  * sinA;

    double exc = vn;
    vn = vnP;
    vnP = exc;

    *vx  = vnP * sinA - vtP * cosA;
    *vy  = vnP * cosA + vtP * sinA;
    *vxP = vn  * sinA - vt  * cosA;
    *vyP = vn  * cosA + vt  * sinA;
    }

bool WasCollision   (double x, double y, double r, double xP, double yP, double rP)
    {
    return (sqrt ((x - xP)*(x - xP) + (y - yP)*(y - yP)) <= (r + rP));
    }

void PhysicsBird (double* x, double* y, double* vx, double* vy, int* ay, int dt, double Size)
    {
    *vy += *ay * dt;

    *x += *vx * dt;
    *y += *vy * dt;

    *vx = (*vx) * 0.99;  // уменьшение по 0X всегда за счет сопротивлени€ воздуха
    *vy = (*vy) * 0.99;  // уменьшение по 0Y
    // при полете вверх замедл€юща€ составл€юща€: ay + a(сопротивлени€ воздуха)
    // при полете вниз ускор€юща€ составл€юща€: ay - a(сопротивлени€ воздуха)

    if (*x > (1000 - 70*Size))
        {
        *vx = - *vx;
        *x  = 2 * (1000 - 70*Size) - *x;
        }

    if (*y > (550 - 70*Size))
        {
        *vy = - *vy;
        *y  = 2 * (550 - 70*Size) - *y;
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

    if ((*vy > - 0.06) && (*vy < 0.06) && (*y > (550 - 70*Size)))
        {
        *ay = 0;
        *vx = 0;
        }
    }

void PhysicsPig (double* x, double* y, double* vx, double* vy, int* ay, int dt, double Size)
    {
    *vy += *ay * dt;

    *x += *vx * dt;
    *y += *vy * dt;

    *vx = (*vx) * 0.99;  // уменьшение по 0X всегда за счет сопротивлени€ воздуха
    *vy = (*vy) * 0.99;  // уменьшение по 0Y
    // при полете вверх замедл€юща€ составл€юща€: ay + a(сопротивлени€ воздуха)
    // при полете вниз ускор€юща€ составл€юща€: ay - a(сопротивлени€ воздуха)

    if (*x > (1000 - 50*Size))
        {
        *vx = - *vx;
        *x  = 2 * (1000 - 50*Size) - *x;
        }

    if (*y > (560 - 50*Size))
        {
        *vy = - *vy;
        *y  = 2 * (560 - 50*Size) - *y;
        }

    if (*x < (0 + 50*Size))
        {
        *vx = - *vx;
        *x  = 2 * 50*Size - *x;
        }

    if (*y < (0 + 50*Size))
        {
        *vy = - *vy;
        *y  = 2 * 50*Size - *y;
        }

     if ((*vy > - 0.06) && (*vy < 0.06) && (*y > (550 - 50*Size)))
        {
        *ay = 0;
        *vx = 0;
        }

    }

void BirdSpeed(double* vx, double* vy)
    {
    if (txGetAsyncKeyState (VK_UP))    *vy -=1;
    if (txGetAsyncKeyState (VK_DOWN))  *vy +=1;
    if (txGetAsyncKeyState (VK_LEFT))  *vx -=1;
    if (txGetAsyncKeyState (VK_RIGHT)) *vx +=1;
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

void TabloScore (int* score)
    {
    txSetColor(TX_BLACK);
    txSelectFont ("Arial Black", 30);
    txTextOut (850, 25, "∆»«Ќ» : ");

    char strScore [20] = "";
    sprintf (strScore, "%d", *score);

    txSetColor(TX_BROWN);
    txSelectFont ("Arial Black", 30);
    txTextOut (950, 25, strScore);
    }
