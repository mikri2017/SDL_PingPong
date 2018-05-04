#ifndef IBALLMGR_H_INCLUDED
#define IBALLMGR_H_INCLUDED

#include "DebugParams.h"

class SDL_Renderer;
class RectMgr;

enum CollisionType {
    none,
    leftRight,
    topBottom,
};

struct IBallMgr
{
    virtual ~IBallMgr() {};
    virtual void reinit() = 0;
    virtual void draw(SDL_Renderer *renderer, bool clean = false) = 0;
    virtual void flipVertically() = 0;
    virtual void flipHorizontally() = 0;
    virtual CollisionType checkCollisionWithScreen() = 0;
    virtual bool checkCollisionWithRect(RectMgr *rect) = 0;
};

#endif
