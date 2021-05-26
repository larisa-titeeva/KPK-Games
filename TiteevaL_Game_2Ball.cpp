#include "TXLib.h"

void BackgroundDraw();
void BallDraw();

int main()
    {
    txCreateWindow (1000, 600);

    BackgroundDraw();
    BallDraw();

    return 0;
    }

void BackgroundDraw()
    {
    txSetColor     (TX_BLUE, 5);
    txSetFillColor (TX_BLACK);

    txRectangle (100, 100, 900, 500);

    }

void BallDraw()
    {
    int x1 = 200, y1 = 300,
       vx1 = 4,  vy1 = 3,
        r1 = 10;

    int x2 = 500, y2 = 160,
       vx2 = 6,  vy2 = 4,
        r2 = 20;

    int dt = 1;


    while  (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetColor     (TX_PINK);
        txSetFillColor (TX_RED);
        txCircle (x1, y1, r1);

        txSetColor     (TX_LIGHTBLUE);
        txSetFillColor (TX_BLUE);
        txCircle (x2, y2, r2);

        x1 += vx1 * dt;
        y1 += vy1 * dt;

        x2 += vx2 * dt;
        y2 += vy2 * dt;

        if (x1 > (900 - r1))
            {
            vx1 = -vx1;
            x1  = 2 * (900 - r1) - x1;
            }

        if (y1 > (500 - r1))
            {
            vy1 = -vy1;
            y1  = 2 * (500 - r1) - y1;
            }

        if (x1 < (100 + r1))
            {
            vx1 = -vx1;
            x1  = 2 * (100 + r1) - x1;
            }

        if (y1 < (100 + r1))
            {
            vy1 = -vy1;
            y1  = 2 * (100 + r1) - y1;
            }

        if (x2 > (900 - r2))
            {
            vx2 = -vx2;
            x2  = 2 * (900 - r2) - x2;
            }

        if (y2 > (500 - r2))
            {
            vy2 = -vy2;
            y2  = 2 * (500 - r2) - y2;
            }

        if (x2 < (100 + r2))
            {
            vx2 = -vx2;
            x2  = 2 * (100 + r2) - x2;
            }

        if (y2 < (100 + r2))
            {
            vy2 = -vy2;
            y2  = 2 * (100 + r2) - y2;
            }

        txSleep (10);
        }
    }

