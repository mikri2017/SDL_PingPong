#ifndef BALLMGR2_H_INCLUDED
#define BALLMGR2_H_INCLUDED

#include "IBallManager.h"

class BallMgr2 : public IBallMgr
{
public:
    void reinit();
    void draw(SDL_Renderer *renderer, bool clean = false);
    void flipVertically();
    void flipHorizontally();
    bool checkCollisionWithScreen();
    void checkCollisionWithRect(RectMgr *rect);
};


#endif // BALLMGR2_H_INCLUDED