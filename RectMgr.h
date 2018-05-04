#ifndef RECTMGR_H_INCLUDED
#define RECTMGR_H_INCLUDED

#include "DebugParams.h"
#include "MainConstants.h"
#include "Rect.h"

class RectMgr
{
private:
    Rect *rect, *rect_cleaner;
public:
    RectMgr();
    ~RectMgr();
    void setBeginXY(int x, int y);
    void setWidth(int w);
    void setHeight(int h);
    void draw(SDL_Renderer *renderer, bool clean = false);
    SDL_Rect getRect();
};


#endif // RECTMGR_H_INCLUDED
