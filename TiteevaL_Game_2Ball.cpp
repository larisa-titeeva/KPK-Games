#include "TXLib.h"

void BackgroundDraw();
void BallMove();
bool Collision (int xA, int yA, int xB, int yB, int rA, int rB);
void BallDraw    (int  x, int  y, int r, COLORREF color, COLORREF fillcolor);

void PhysicsBall (int* x, int* y, int* vx, int* vy, int ax, int ay, int r, int dt);

void BallsCollision (int  x1,  int   x2, int y1,    int y2,    int* vx1,
                     int* vx2, int* vy1, int* vy2,  int r1,    int r2);

int main()
    {
    txCreateWindow (1000, 600);
    BallMove();

    return 0;
    }


void BallMove()
    {
    int x1 = 200, y1 = 300,
       vx1 = 4,  vy1 = 3,
       ax1 = 0,  ay1 = 0,
        r1 = 80;

    int x2 = 500, y2 = 160,
       vx2 = 3,  vy2 = 4,
       ax2 = 0,  ay2 = 0,
        r2 = 80;

    int x3 = 600, y3 = 60,
       vx3 = 3,  vy3 = -2,
       ax3 = 0,  ay3 = 0,
        r3 = 80;

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

        if (Collision (x1, y1, x2, y2, r1, r2))
            {
            BallsCollision (x1, x2, y1, y2, &vx1, &vx2, &vy1, &vy2, r1, r2);
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


void BallsCollision (int  x1,  int   x2, int y1,    int y2,    int* vx1,
                     int* vx2, int* vy1, int* vy2,  int r1,    int r2)
    {
    int dx = x1 - x2, dy = y1 - y2;
    int sinA = ROUND (dx / sqrt (dx * dx + dy * dy));
    int cosA = ROUND (dy / sqrt (dx * dx + dy * dy));

    int vn1 =  (*vx2) * sinA + (*vy2) * cosA;
    int vn2 =  (*vx1) * sinA + (*vy1) * cosA;
    int vt1 = -(*vx2) * cosA + (*vy2) * sinA;
    int vt2 = -(*vx1) * cosA + (*vy1) * sinA;

    int exc = vn1;
    vn1 = vn2;
    vn2 = exc;

    *vx1 = vn2 * sinA - vt2 * cosA;
    *vy1 = vn2 * cosA + vt2 * sinA;
    *vx2 = vn1 * sinA - vt1 * cosA;
    *vy2 = vn1 * cosA + vt1 * sinA;
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



