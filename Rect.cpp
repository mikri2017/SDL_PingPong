#include "Rect.h"

Rect::Rect()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
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

void Rect::setWidth(int w)
{
    if(w < 0)
        w = 0;
    rect.w = w;
}

void Rect::setHeight(int h)
{
    if(h < 0)
        h = 0;
    rect.h = h;
}

void Rect::draw(SDL_Renderer *renderer)
{
    SDL_RenderFillRect(renderer, &rect);
}
