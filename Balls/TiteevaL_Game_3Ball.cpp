#include "TXLib.h"

void BackgroundDraw();
void BallMove();
void BallControl (int* vxA, int* vyA);
bool Collision   (int xA, int yA, int rA, int xB, int yB, int rB);
void BallDraw    (int  x, int  y, int r,  COLORREF color, COLORREF fillcolor);

void PhysicsBall (int* x, int* y, int* vx, int* vy, int ax, int ay, int r, int dt);

void BallsCollision (int  xA, int yA, int* vxA, int* vyA,
                     int  xB, int yB, int* vxB, int* vyB);

int main()
    {
    txCreateWindow (1000, 600);
    BallMove();

    return 0;
    }

struct Ball
    {
    int x,  y,
        vx, vy;

    int r;

    COLORREF color;
    COLORREF fillcolor;
    };

void BallMove()
    {
    int ax = 0, ay = 0;
    int dt = 1;

    Ball ball1 = {.x = 200, .y = 300, .vx =  1, .vy =  1, .r = 40, .color = TX_LIGHTGREEN, .fillcolor = TX_GREEN};
    Ball ball2 = {.x = 500, .y = 160, .vx =  2, .vy =  1, .r = 40, .color = TX_LIGHTBLUE,  .fillcolor = TX_BLUE};
    Ball ball3 = {.x = 600, .y =  60, .vx = -1, .vy = -2, .r = 40, .color = TX_LIGHTRED,   .fillcolor = TX_RED};

    HDC Background  = txLoadImage ("images\\phon.bmp");

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txBitBlt (txDC(), 0, 0, 1000, 600, Background, 0, 0);

        BallDraw (ball1.x, ball1.y, ball1.r, ball1.color, ball1.fillcolor);
        BallDraw (ball2.x, ball2.y, ball2.r, ball2.color, ball2.fillcolor);
        BallDraw (ball3.x, ball3.y, ball3.r, ball3.color, ball3.fillcolor);

        PhysicsBall (&ball1.x, &ball1.y, &ball1.vx, &ball1.vy, ax, ay, ball1.r, dt);
        PhysicsBall (&ball2.x, &ball2.y, &ball2.vx, &ball2.vy, ax, ay, ball2.r, dt);
        PhysicsBall (&ball3.x, &ball3.y, &ball3.vx, &ball3.vy, ax, ay, ball3.r, dt);

        BallControl(&ball1.vx, &ball1.vy);

// â ïîèñêàõ ôóíêöèè ïî óìåíüøåíèþ êîëè÷åñòâà "if"
        if (Collision (ball1.x, ball1.y, ball1.r, ball2.x, ball2.y, ball2.r))
            {
            BallsCollision (ball1.x, ball1.y, &ball1.vx, &ball1.vy, ball2.x, ball2.y, &ball2.vx, &ball2.vy);
            }
        if (Collision (ball1.x, ball1.y, ball1.r, ball3.x, ball3.y, ball3.r))
            {
            BallsCollision (ball1.x, ball1.y, &ball1.vx, &ball1.vy, ball3.x, ball3.y, &ball3.vx, &ball3.vy);
            }
        if (Collision (ball3.x, ball3.y, ball3.r, ball2.x, ball2.y, ball2.r))
            {
            BallsCollision (ball3.x, ball3.y, &ball3.vx, &ball3.vy, ball2.x, ball2.y, &ball2.vx, &ball2.vy);
            }

        txSleep (10);
        }
    txDeleteDC (Background);
    }

void BallDraw(int x, int y, int r, COLORREF color, COLORREF fillcolor)
    {
    txSetColor     (color);
    txSetFillColor (fillcolor);
    txCircle (x, y, r);
    }

void PhysicsBall (int* x, int* y, int* vx, int* vy, int ax, int ay, int r, int dt)
    {
    *x += *vx * dt;
    *y += *vy * dt;

    *vx += ax * dt;
    *vy += ay * dt;

    if (*x > (1000 - r))
        {
        *vx = - *vx;
        *x  = 2 * (1000 - r) - *x;
        }

    if (*y > (600 - r))
        {
        *vy = - *vy;
        *y  = 2 * (600 - r) - *y;
        }

    if (*x < (0 + r))
        {
        *vx = - *vx;
        *x  = 2 * r - *x;
        }

    if (*y < (0 + r))
        {
        *vy = - *vy;
        *y  = 2 * r - *y;
        }
    }

void BallControl(int* vxA, int* vyA)
    {
    if (txGetAsyncKeyState (VK_UP))    *vyA +=1;
    if (txGetAsyncKeyState (VK_DOWN))  *vyA -=1;
    if (txGetAsyncKeyState (VK_LEFT))  *vxA -=1;
    if (txGetAsyncKeyState (VK_RIGHT)) *vxA +=1;
    }

void BallsCollision (int  xA, int yA, int* vxA, int* vyA,
                     int  xB, int yB, int* vxB, int* vyB)
    {
    int dx = xA - xB, dy = yA - yB;
    int sinA = ROUND (dx / sqrt (dx * dx + dy * dy));
    int cosA = ROUND (dy / sqrt (dx * dx + dy * dy));

    int vnA =  (*vxB) * sinA + (*vyB) * cosA;
    int vnB =  (*vxA) * sinA + (*vyA) * cosA;
    int vtA = -(*vxB) * cosA + (*vyB) * sinA;
    int vtB = -(*vxA) * cosA + (*vyA) * sinA;

    int exc = vnA;
    vnA = vnB;
    vnB = exc;

    *vxA = vnB * sinA - vtB * cosA;
    *vyA = vnB * cosA + vtB * sinA;
    *vxB = vnA * sinA - vtA * cosA;
    *vyB = vnA * cosA + vtA * sinA;
    }

bool Collision (int xA, int yA, int rA, int xB, int yB, int rB)
    {
    return (sqrt ((xA - xB)*(xA - xB) + (yA - yB)*(yA - yB)) <= (rA + rB));
    }
/*
bool Collision (int xA, int yA, int xB, int yB, int vxA, int vyA, int vxB, int vyB, int dt)
    {
    double T1 = (xB - xA) / (vxA*dt - vxB*dt);
    double T2 = (yB - yA) / (vyA*dt - vyB*dt);
    return ((T1 >= 0) and (T1 <= 1)) or ((T2 >= 0) and (T2 <= 1));
    }
*/



