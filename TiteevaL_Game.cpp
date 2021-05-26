#include "TXLib.h"

void BackgroundDraw();
void BallDraw(int x, int y, int vx, int vy, int dt, COLORREF OutLine, COLORREF BallColor);

int main()
    {
    txCreateWindow (1000, 600);

    BackgroundDraw();
    BallDraw(200, 300, 5, 6, 1, TX_PINK, TX_RED);

    return 0;
    }

void BackgroundDraw()
    {
    txSetColor (TX_BLUE, 5);
    txSetFillColor (TX_BLACK);

    txRectangle (100, 100, 900, 500);
    }

void BallDraw(int x, int y, int vx, int vy, int dt, COLORREF OutLine, COLORREF BallColor)
    {
    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetColor (OutLine, 3);
        txSetFillColor (BallColor);

        txCircle (x, y, 20);

        x += vx * dt;
        y += vy * dt;

        if (x > 890)
            {
            vx = -vx;
            x = 1780 - x;
            }

        if (y > 490)
            {
            vy = -vy;
            y = 980 - y;
            }

        if (x < 110)
            {
            vx = -vx;
            x = 220 - x;
            }

        if (y < 110)
            {
            vy = -vy;
            y = 220 - y;
            }
        txSleep (10);
        }
    }
