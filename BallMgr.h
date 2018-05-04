#ifndef BALLMGR_H_INCLUDED
#define BALLMGR_H_INCLUDED

#include "DebugParams.h"
#include <math.h>
#include "Ball.h"
#include "RectMgr.h"
#include "IBallManager.h"

class BallMgr : public IBallMgr
{
private:
    Ball *ball;
    SDL_Rect ball_cleaner;
    int dir_angle;
    int checkCollisionAngles[3];
    float dir_angle_cos, dir_angle_sin;

    std::vector<SDL_Point> linePath;
    size_t linePath_iter;

    void updateLinePath(SDL_Point p_first, SDL_Point p_second);
    void genLinePath(int x1, int y1, int x2, int y2);
public:
    BallMgr(int radius);
    ~BallMgr();
    void reinit();
    void draw(SDL_Renderer *renderer, bool clean = false);
    void flipVertically();
    void flipHorizontally();
    CollisionType checkCollisionWithScreen();
    bool checkCollisionWithRect(RectMgr *rect);
};


#endif // BALLMGR_H_INCLUDED
