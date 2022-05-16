#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <cstring>
class Rect {
public:
    float X;
    float Y;
    float W;
    float H;
    Rect()
            : X(0)
            , Y(0)
            , W(0)
            , H(0)
    {
    }
    Rect(float x1, float y1, float w1, float h1)
            : X(x1)
            , Y(y1)
            , W(w1)
            , H(h1)
    {
    }
    Rect(const Rect& v);
    ~Rect();
};
Rect::Rect(const Rect& v)
        : X(v.X)
        , Y(v.Y)
        , W(v.W)
        , H(v.H)
{
}
Rect::~Rect() {}