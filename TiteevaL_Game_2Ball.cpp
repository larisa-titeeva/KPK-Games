#include "TXLib.h"

void BackgroundDraw();
void BallMove();
void TextDraw    (int r1, int r2, double d, int *count);
void BallDraw    (int  x, int  y, int r, COLORREF color, COLORREF fillcolor);

void PhysicsBall (int* x, int* y, int* vx, int* vy, int ax, int ay, int r, int dt);

void BallsCollision (int  x1,  int   x2, int y1,    int y2,    int* vx1,
                     int* vx2, int* vy1, int* vy2,  int r1,    int r2,
                     int* dx,  int*  dy, double* d, int* sinA, int* cosA,
                     int* vn1, int* vn2, int* vt1,  int* vt2,  int* exc);

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

    int dt = 1;
    int count = 0;

    int dx, dy; double  d;
    int sinA, cosA;

    int vn1, vn2, vt1, vt2, exc;

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txClear();
        BallDraw (x1, y1, r1, TX_LIGHTGREEN, TX_GREEN);
        BallDraw (x2, y2, r2, TX_LIGHTBLUE,  TX_BLUE);

        PhysicsBall (&x1, &y1, &vx1, &vy1, ax1, ay1, r1, dt);
        PhysicsBall (&x2, &y2, &vx2, &vy2, ax2, ay2, r2, dt);

        BallsCollision (x1, x2, y1, y2, &vx1, &vx2, &vy1, &vy2, r1, r2,
                        &dx, &dy, &d, &sinA, &cosA, &vn1, &vn2, &vt1, &vt2, &exc);

        TextDraw (r1, r2, d, &count);

        txSleep (10);
        }
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

void TextDraw (int r1, int r2, double d, int *count)
    {
    char strCount[10] = "";

    if (d < (r1 + r2))
        {
        *count = *count + 1;
        }

    sprintf (strCount, "*count = %d", *count);

    txSetColor (TX_GREEN);
    txSetFillColor (TX_BLACK);
    txRectangle (0, 0, 100, 100);

    txTextOut (10, 50, strCount);
    }

void BallsCollision (int  x1,  int   x2, int y1,    int y2,    int* vx1,
                     int* vx2, int* vy1, int* vy2,  int r1,    int r2,
                     int* dx,  int*  dy, double* d, int* sinA, int* cosA,
                     int* vn1, int* vn2, int* vt1,  int* vt2,  int* exc)
    {
    *dx = x1 - x2;
    *dy = y1 - y2;
    *d  = sqrt ((*dx) * (*dx) + (*dy) * (*dy));

    *sinA = ROUND (*dx / *d);
    *cosA = ROUND (*dy / *d);

    if (*d < (r1 + r2))
        {
        *vn1 =  (*vx2) * (*sinA) + (*vy2) * (*cosA);
        *vn2 =  (*vx1) * (*sinA) + (*vy1) * (*cosA);
        *vt1 = -(*vx2) * (*cosA) + (*vy2) * (*sinA);
        *vt2 = -(*vx1) * (*cosA) + (*vy1) * (*sinA);

        *exc = *vn1;
        *vn1 = *vn2;
        *vn2 = *exc;

        *vx1 = (*vn2) * (*sinA) - (*vt2) * (*cosA);
        *vy1 = (*vn2) * (*cosA) + (*vt2) * (*sinA);
        *vx2 = (*vn1) * (*sinA) - (*vt1) * (*cosA);
        *vy2 = (*vn1) * (*cosA) + (*vt1) * (*sinA);
        }
    }
