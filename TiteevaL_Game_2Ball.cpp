#include "TXLib.h"

void BackgroundDraw();
void BallMove();
void TextDraw    (int x);
void BallDraw    (int x, int y, int vx, int vy, int ax, int ay, int r, COLORREF color, COLORREF fillcolor);
void PhysicsBall (int* x, int* y, int* vx, int* vy, int ax, int ay, int r, int dt);

int main()
    {
    txCreateWindow (1000, 600);

    BackgroundDraw();
    BallMove();

    return 0;
    }

void BackgroundDraw()
    {
    txSetColor     (TX_BLUE, 5);
    txSetFillColor (TX_BLACK);

    txRectangle (100, 100, 900, 500);

    }

void BallMove()
    {
    int x1 = 200, y1 = 300,
       vx1 = 4,  vy1 = 3,
       ax1 = 0,  ay1 = 0,
        r1 = 10;

    int x2 = 500, y2 = 160,
       vx2 = 6,  vy2 = 4,
       ax2 = 0,  ay2 = 1,
        r2 = 10;

    int x3 = 300, y3 = 350,
       vx3 = 2,  vy3 = 4,
       ax3 = 0,  ay3 = 0,
        r3 = 15;

    int dt = 1;

    while  (!txGetAsyncKeyState (VK_ESCAPE))
        {
        BallDraw (x1, y1, vx1, vy1, ax1, ay1, r1, TX_LIGHTGREEN, TX_GREEN);
        BallDraw (x2, y2, vx2, vy2, ax2, ay2, r2, TX_LIGHTBLUE, TX_BLUE);
        BallDraw (x3, y3, vx3, vy3, ax3, ay3, r3, TX_LIGHTRED, TX_RED);

        PhysicsBall (&x1, &y1, &vx1, &vy1, ax1, ay1, r1, dt);
        PhysicsBall (&x2, &y2, &vx2, &vy2, ax2, ay2, r2, dt);
        PhysicsBall (&x3, &y3, &vx3, &vy3, ax3, ay3, r3, dt);

        TextDraw (x1);
        txSleep (10);
        }
    }

void BallDraw(int x, int y, int vx, int vy, int ax, int ay, int r, COLORREF color, COLORREF fillcolor)
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

    if (*x > (900 - r))
        {
        *vx = - *vx;
        *x  = 2 * (900 - r) - *x;
        }

    if (*y > (500 - r))
        {
        *vy = - *vy;
        *y  = 2 * (500 - r) - *y;
        }

    if (*x < (100 + r))
        {
        *vx = - *vx;
        *x  = 2 * (100 + r) - *x;
        }

    if (*y < (100 + r))
        {
        *vy = - *vy;
        *y  = 2 * (100 + r) - *y;
        }
    }

void TextDraw (int x)
    {
    char strX[10] = "";
    sprintf (strX, "x = %d", x);

    txSetColor (TX_GREEN);
    txSetFillColor (TX_BLACK);
    txRectangle (0, 0, 100, 100);

    txTextOut (10, 50, strX);
    }
