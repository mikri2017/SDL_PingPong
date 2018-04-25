#ifndef BALLMGR_H_INCLUDED
#define BALLMGR_H_INCLUDED

#include <ctime>
#include <math.h>
#include "Ball.h"

class BallMgr
{
private:
    Ball *ball;
    SDL_Rect ball_cleaner;
    SDL_Point p_ball_centre;
    int dir_angle;
    float dir_angle_cos, dir_angle_sin;
    int dir_line_len;

    void chg_dir_angle();
public:
    BallMgr(int radius);
    void reinit();
    void draw(SDL_Renderer *renderer, bool clean = false);
};


#endif // BALLMGR_H_INCLUDED
