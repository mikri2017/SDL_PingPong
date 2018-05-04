#include "Rect.h"
#include <iostream>

Rect::Rect()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
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
    rect.x = x;
    rect.y = y;
}

SDL_Point Rect::getBeginXY()
{
    SDL_Point p_begin_xy;
    p_begin_xy.x = rect.x;
    p_begin_xy.y = rect.y;
    return p_begin_xy;
}

void Rect::setWidth(int w)
{
    if(w < 0)
        w = 0;
    rect.w = w;
}

int Rect::getWidth()
{
    return rect.w;
}

void Rect::setHeight(int h)
{
    if(h < 0)
        h = 0;
    rect.h = h;
}

int Rect::getHeight()
{
    return rect.h;
}

void Rect::draw(SDL_Renderer *renderer)
{
    SDL_RenderFillRect(renderer, &rect);
}
