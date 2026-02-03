#ifndef BallMgrSimple_H_INCLUDED
#define BallMgrSimple_H_INCLUDED

#include "DebugParams.h"
#include <SDL3/SDL_video.h>
#include <memory>
#include "IBallManager.h"
#include "Ball.h"

class RectMgr;

class BallMgrSimple : public IBallMgr
{
private:
    std::unique_ptr<Ball> ball;
    float yspeed;
    float xspeed;
    float bounce;
    SDL_FRect ball_cleaner;
    SDL_Point ball_point;

    BallMgrSimple () {};

public:
    explicit BallMgrSimple(size_t radius);
    ~BallMgrSimple();
    void reinit();
    void draw(SDL_Renderer *r, bool clean = false);
    void flipVertically();
    void flipHorizontally();
    CollisionType checkCollisionWithScreen();
    bool checkCollisionWithRect(RectMgr *rect);
};


#endif // BallMgrSimple_H_INCLUDED
