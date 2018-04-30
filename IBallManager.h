#ifndef IBALLMGR_H_INCLUDED
#define IBALLMGR_H_INCLUDED

class SDL_Renderer;
class RectMgr;

struct IBallMgr
{
    virtual void reinit() = 0;
    virtual void draw(SDL_Renderer *renderer, bool clean = false) = 0;
    virtual void flipVertically() = 0;
    virtual void flipHorizontally() = 0;
    virtual bool checkCollisionWithScreen() = 0;
    virtual void checkCollisionWithRect(RectMgr *rect) = 0;
};

#endif