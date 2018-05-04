#ifndef BallMgrSimple_H_INCLUDED
#define BallMgrSimple_H_INCLUDED

#include "IBallManager.h"
#include <SDL2/SDL_video.h>
#include <memory>

#include "Ball.h"

class RectMgr;

class BallMgrSimple : public IBallMgr
{
private:
    std::unique_ptr<Ball> ball;
    float yspeed;
    float xspeed;
    float bounce;
    SDL_Rect ball_cleaner;
    SDL_Point ball_point;

    BallMgrSimple () {};

public:
    explicit BallMgrSimple(size_t radius);
    ~BallMgrSimple();
    void reinit();
    void draw(SDL_Renderer *renderer, bool clean = false);
    void flipVertically();
    void flipHorizontally();
    CollisionType checkCollisionWithScreen();
    bool checkCollisionWithRect(RectMgr *rect);
};


#endif // BallMgrSimple_H_INCLUDED
