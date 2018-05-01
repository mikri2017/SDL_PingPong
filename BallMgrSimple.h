#ifndef BallMgrSimple_H_INCLUDED
#define BallMgrSimple_H_INCLUDED

#include "IBallManager.h"
#include <SDL2/SDL_video.h>

class Ball;
class RectMgr;

class BallMgrSimple : public IBallMgr
{
private:
    Ball *ball;
    float yspeed;
    float xspeed;
    float bounce;
    SDL_Rect ball_cleaner;
    SDL_Point ball_point;

    BallMgrSimple () {};

public:
    explicit BallMgrSimple(size_t radius);
    void reinit();
    void draw(SDL_Renderer *renderer, bool clean = false);
    void flipVertically();
    void flipHorizontally();
    bool checkCollisionWithScreen();
    bool checkCollisionWithRect(RectMgr *rect);
};


#endif // BallMgrSimple_H_INCLUDED