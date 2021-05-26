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
    txSetColor (TX_BLUE, 5);
    txSetFillColor (TX_BLACK);

    txRectangle (100, 100, 900, 500);

    }

void BallDraw()
    {
    int x = 200,  y = 300,
       vx =   4, vy =   3,
       ax =   0, ay =   1,
        r =  10;

    int dt = 1;

    txSetColor     (TX_PINK);
    txSetFillColor (TX_RED);
    while  (!txGetAsyncKeyState (VK_ESCAPE))
    {txCircle (x, y, r);

    x  += vx * dt;
    y  += vy * dt;

    vx += ax * dt;
    vy += ay * dt;

    if (x > (900 - r))
        {
        vx = -vx;
        x  = 2 * (900 - r) - x;
        }

    if (y > (500 - r))
        {
        vy = -vy;
        y  = 2 * (500 - r) - y;
        }

    if (x < (100 + r))
        {
        vx = -vx;
        x  = 2 * (100 + r) - x;
        }

    if (y < (100 + r))
        {
        vy = -vy;
        y  = 2 * (100 + r) - y;
        }
    txSleep (10);
    }
    }

