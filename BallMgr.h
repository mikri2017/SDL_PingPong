#ifndef BALLMGR_H_INCLUDED
#define BALLMGR_H_INCLUDED

#include <ctime>
#include "Ball.h"

class BallMgr
{
private:
    Ball *ball;
    SDL_Rect ball_cleaner;
    int dir_angle;
    void chg_dir_angle();
public:
    BallMgr(SDL_Point p_begin, int radius);
    void draw(SDL_Renderer *renderer);
};


#endif // BALLMGR_H_INCLUDED
