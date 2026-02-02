#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED

#include "DebugParams.h"
#include <SDL3/SDL.h>

class Rect
{
private:
    SDL_FRect frect;
public:
    Rect();
    ~Rect();
    void setBeginXY(int x, int y);
    SDL_Point getBeginXY();
    void setWidth(int w);
    int getWidth();
    void setHeight(int h);
    int getHeight();
    void draw(SDL_Renderer *renderer);
};

#endif // RECT_H_INCLUDED
