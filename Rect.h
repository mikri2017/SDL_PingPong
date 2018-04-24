#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED

#include <SDL2/SDL.h>

class Rect
{
private:
    SDL_Rect rect;
public:
    Rect();
    void setBeginXY(int x, int y);
    void setWidth(int w);
    void setHeight(int h);
    void draw(SDL_Renderer *renderer);
};

#endif // RECT_H_INCLUDED
