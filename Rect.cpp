#include "Rect.h"
#include <iostream>

Rect::Rect()
{
    frect.x = 0;
    frect.y = 0;
    frect.w = 0;
    frect.h = 0;
}

Rect::~Rect()
{
#ifdef DEBUG_MESSAGES_SHOW
    std::cout << "Rect end\n";
#endif // DEBUG_MESSAGES_SHOW
}

void Rect::setBeginXY(int x, int y)
{
    // x и y должны быть неотрицательны
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    frect.x = x;
    frect.y = y;
}

SDL_Point Rect::getBeginXY()
{
    SDL_Point p_begin_xy;
    p_begin_xy.x = frect.x;
    p_begin_xy.y = frect.y;
    return p_begin_xy;
}

void Rect::setWidth(int w)
{
    if(w < 0)
        w = 0;
    frect.w = w;
}

int Rect::getWidth()
{
    return frect.w;
}

void Rect::setHeight(int h)
{
    if(h < 0)
        h = 0;
    frect.h = h;
}

int Rect::getHeight()
{
    return frect.h;
}

void Rect::draw(SDL_Renderer *renderer)
{
    SDL_RenderFillRect(renderer, &frect);
}
