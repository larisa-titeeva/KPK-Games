#include "TXLib.h"

void BackgroundDraw();
void BallMove();
bool Collision (int xA, int yA, int xB, int yB, int rA, int rB);
void BallDraw    (int  x, int  y, int r, COLORREF color, COLORREF fillcolor);

void PhysicsBall (int* x, int* y, int* vx, int* vy, int ax, int ay, int r, int dt);

void BallsCollision (int  xA,  int   xB, int yA,    int yB,    int* vxA,
                     int* vxB, int* vyA, int* vyB);

int main()
    {
    txCreateWindow (1000, 600);
    BallMove();

    return 0;
    }


void BallMove()
    {
    int x1 = 200, y1 = 300,
       vx1 = 2,  vy1 = 1,
       ax1 = 0,  ay1 = 0,
        r1 = 40;

    int x2 = 500, y2 = 160,
       vx2 = 2,  vy2 = 1,
       ax2 = 0,  ay2 = 0,
        r2 = 40;

    int x3 = 600, y3 = 60,
       vx3 = -1,  vy3 = -2,
       ax3 = 0,  ay3 = 0,
        r3 = 40;

    int dt = 1;
    HDC Background  = txLoadImage ("images\\phon.bmp");

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txBitBlt (txDC(), 0, 0, 1000, 600, Background, 0, 0);

        BallDraw (x1, y1, r1, TX_LIGHTGREEN, TX_GREEN);
        BallDraw (x2, y2, r2, TX_LIGHTBLUE,  TX_BLUE);
        BallDraw (x3, y3, r3, TX_LIGHTRED,   TX_RED);

        PhysicsBall (&x1, &y1, &vx1, &vy1, ax1, ay1, r1, dt);
        PhysicsBall (&x2, &y2, &vx2, &vy2, ax2, ay2, r2, dt);
        PhysicsBall (&x3, &y3, &vx3, &vy3, ax3, ay3, r3, dt);

// в поисках функции по уменьшению количества "if"
        if (Collision (x1, y1, x2, y2, r1, r2))
            {
            BallsCollision (x1, x2, y1, y2, &vx1, &vx2, &vy1, &vy2);
            }
        if (Collision (x1, y1, x3, y3, r1, r3))
            {
            BallsCollision (x1, x3, y1, y3, &vx1, &vx3, &vy1, &vy3);
            }
        if (Collision (x3, y3, x2, y2, r3, r2))
            {
            BallsCollision (x3, x2, y3, y2, &vx3, &vx2, &vy3, &vy2);
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


void BallsCollision (int  xA,  int   xB, int yA,    int yB,    int* vxA,
                     int* vxB, int* vyA, int* vyB)
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

bool Collision (int xA, int yA, int xB, int yB, int rA, int rB)
    {
    return (sqrt ((xA - xB)*(xA - xB) + (yA - yB)*(yA - yB)) <= (rA + rB));
    }

/*bool Collision (int xA, int yA, int xB, int yB, int vxA, int vyA, int vxB, int vyB, int dt)
    {
    double T = ((yA - yB)*vxB*dt - (xA - xB)*vyB*dt) / (vyB*dt*vxA*dt - vxB*dt*vyA*dt);
    return ((T >= 0) and (T <= 1));
    }
 */



