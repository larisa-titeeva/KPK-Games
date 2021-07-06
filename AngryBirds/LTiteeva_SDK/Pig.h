#include "TXLib.h"

//void PigDraw  (double x, double y, double Size);
//void PhysicsPig  (double* x, double* y, double* vx, double* vy, int* ay, int dt, double Size);

struct Pig
    {
    double xP, yP;
    double vxP, vyP;
    int ayP;

    void Draw (int frame);
    void Physics (int dt);
    };

//{-----------------------------------------------------------------------------
//! Функция рисования подарка при помощи спрайтовой анимации
//!
//! @param frame  кадр анимации персонажа при движении
//!
//}-----------------------------------------------------------------------------
void Pig::Draw (int frame)
    {
    txTransparentBlt (txDC(), xP, yP, X_PIG, Y_PIG, SPRITE_PIG, (frame % 3)*X_PIG, 0*Y_PIG, RGB(192,192,192));
    }

// Должны стоять на месте до столкновения
void Pig::Physics (int dt)
    {
    (*this).vyP += (*this).ayP * dt;

    (*this).xP += (*this).vxP * dt;
    (*this).yP += (*this).vyP * dt;

    (*this).vxP = ((*this).vxP) * 0.99;  // уменьшение по 0X всегда за счет сопротивления воздуха
    (*this).vyP = ((*this).vyP) * 0.99;  // уменьшение по 0Y
    // при полете вверх замедляющая составляющая: ay + a(сопротивления воздуха)
    // при полете вниз ускоряющая составляющая: ay - a(сопротивления воздуха)

    if ((*this).xP > (1000 - X_PIG))
        {
        (*this).vxP = - (*this).vxP;
        (*this).xP  = 2 * (1000 - X_PIG) - (*this).xP;
        }

    if ((*this).yP > (560 - X_PIG))
        {
        (*this).vyP = - (*this).vyP;
        (*this).yP  = 2 * (560 - X_PIG) - (*this).yP;
        }

    if ((*this).xP < (0 + X_PIG))
        {
        (*this).vxP = - (*this).vxP;
        (*this).xP  = 2 * X_PIG - (*this).xP;
        }

    if ((*this).yP < (0 + X_PIG))
        {
        (*this).vyP = - (*this).vyP;
        (*this).yP  = 2 * X_PIG - (*this).yP;
        }

     if (((*this).vyP > - 0.06) && ((*this).vyP < 0.06) && ((*this).yP > (550 - X_PIG)))
        {
        (*this).ayP = 0;
        (*this).vxP = 0;
        }

    }

/*void PigDraw (double x, double y, double Size)
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
          */
