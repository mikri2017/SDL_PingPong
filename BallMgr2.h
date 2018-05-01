#ifndef BALLMGR2_H_INCLUDED
#define BALLMGR2_H_INCLUDED

#include "IBallManager.h"
#include <SDL2/SDL_video.h>

class Ball;
class RectMgr;

class BallMgr2 : public IBallMgr
{
private:
    Ball *ball;
    float yspeed;
    float xspeed;
    float bounce;
    SDL_Rect ball_cleaner;
    SDL_Point ball_point;

    BallMgr2 () {};

public:
    explicit BallMgr2(size_t radius);
    void reinit();
    void draw(SDL_Renderer *renderer, bool clean = false);
    void flipVertically();
    void flipHorizontally();
    bool checkCollisionWithScreen();
    void checkCollisionWithRect(RectMgr *rect);
};


#endif // BALLMGR2_H_INCLUDED