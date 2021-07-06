#include "TXLib.h"


const HDC SPRITE_BIRD  = txLoadImage ("images\\bird.bmp");
const int X_BIRD = txGetExtentX (SPRITE_BIRD)/5,
          Y_BIRD = txGetExtentY (SPRITE_BIRD);
const int SIZE_BIRD = 47;

const HDC SPRITE_PIG  = txLoadImage ("images\\pig.bmp");
const int X_PIG = txGetExtentX (SPRITE_PIG)/3,
          Y_PIG = txGetExtentY (SPRITE_PIG);
const int SIZE_PIG = 64;


# include "Bird.h"
# include "Pig.h"

struct Sprite
    {
    HDC img;
    int xSize;
    int ySize;

    void Load (const char namefile []);
    void Delete ();
    };

struct Resourses
    {
    Sprite bird;
    Sprite pig;

    void Load ();
    void Delete ();
    };

void GameMove();
void TitlesBegin();

void TabloScore (int* score);

bool WasCollision (double x, double y, double r, double xP, double yP, double rP);

void Collision    (double  x,  double y,  double* vx,  double* vy,
                   double  xP, double yP, double* vxP, double* vyP);

void CursorDraw (int x, int y);

int main ()
    {
    txCreateWindow (1000, 600);

    TitlesBegin();

    return 0;
    }

// разбить на функции???
void GameMove()
    {
    int score = 5;
    Pig pig1 = {.xP = 500, .yP = 300, .vxP =  0, .vyP =  0};
    Pig pig2 = {.xP = 400, .yP = 100, .vxP =  0, .vyP =  0};

    HDC Background  = txLoadImage ("images\\background.bmp");

    while (score >= 1)
        {
        Bird bird = {.x = 70, .y = 300, .vx =  0, .vy =  0, .ay = 1};
        int  t = 0;
        int dt = 1;

        while (!txGetAsyncKeyState (VK_LMENU))
            {
            txBitBlt (txDC(), 0, 0, 1000, 600, Background, 0, 0);

            bird.Draw (t);

            pig1.Draw (t);
            pig2.Draw (t);

            bird.Speed ();

            txLine (110, 400, 110 + bird.vx, 400 + bird.vy);

            TabloScore (&score);
            txSleep (100);
            t ++;
            }

        score -= 1;
        txPlaySound ("sound/birdMove.wav");
        t = 0;
        while (!txGetAsyncKeyState (VK_ESCAPE))
            {
            txBitBlt (txDC(), 0, 0, 1000, 600, Background, 0, 0);

            TabloScore (&score);
            bird.Draw (t);

            pig1.Draw (t);
            pig2.Draw (t);

            bird.Physics (dt);
            pig1.Physics (dt);
            pig2.Physics (dt);

// если свинок много, уменьшить количество if
            if (WasCollision (bird.x, bird.y, SIZE_BIRD, pig1.xP, pig1.yP, SIZE_PIG))
                {
                Collision (bird.x, bird.y, &bird.vx, &bird.vy, pig1.xP, pig1.yP, &pig1.vxP, &pig1.vyP);
                }
            if (WasCollision (bird.x, bird.y, SIZE_BIRD, pig2.xP, pig2.yP, SIZE_PIG))
                {
                Collision (bird.x, bird.y, &bird.vx, &bird.vy, pig2.xP, pig2.yP, &pig2.vxP, &pig2.vyP);
                }

// остановить игру. исчезновение свинки, с которой столкнулась птичка
            if ((bird.vy > - 0.09) && (bird.vy < 0.09) && (bird.y > (500 - X_BIRD)))
                {
                break;
                }
            t ++;
            txSleep (100);
            }
        }
    txDeleteDC (Background);
    txDeleteDC (SPRITE_BIRD);
    txDeleteDC (SPRITE_PIG);
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

void CursorDraw (int x, int y)
    {
    txSetColor (RGB (100, 0, 0));
    txSetFillColor (TX_RED);
    POINT cursor[] ={ {x, y}, {x + 20, y - 20}, {x + 20, y - 10}, {x + 40, y - 10},
                              {x + 40, y + 10}, {x + 20, y + 10}, {x + 20, y + 20} };
    txPolygon (cursor, 7);
    }

void TabloScore (int* score)
    {
    txSetColor(TX_BLACK);
    txSelectFont ("Arial Black", 30);
    txTextOut (850, 25, "ЖИЗНИ : ");

    char strScore [20] = "";
    sprintf (strScore, "%d", *score);

    txSetColor(TX_BROWN);
    txSelectFont ("Arial Black", 30);
    txTextOut (950, 25, strScore);
    }

void TitlesBegin()
    {
    int x = 620, y = 385;

    txPlaySound ("sound/AngryBirds.wav");
    HDC BeginTitles  = txLoadImage ("images\\BeginTitles.bmp");

    while (!txGetAsyncKeyState (VK_RMENU))
        {
        txBitBlt (txDC(), 0, 0, 1000, 600, BeginTitles, 0, 0);
        CursorDraw (x, y);

        if ((y == 385) && (txGetAsyncKeyState (VK_DOWN)) )
            {
            y = y + 120;
            }
        if ((y == 505) && (txGetAsyncKeyState (VK_UP)) )
            {
            y = y - 120;
            }
        txSleep (50);
        }
    //COLORREF color = txFetPixel (x, y);
    if (y == 385)
        {
        GameMove();
        }
    if (y == 505)
        {
        txMessageBox ("КОНЕЦ ИГРЫ");;
        }
    txDeleteDC (BeginTitles);
    txSleep (3000);
    }
