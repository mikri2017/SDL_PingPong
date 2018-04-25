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
    int checkCollisionAngles[3];
    float dir_angle_cos, dir_angle_sin;
    int dir_line_len;
    std::vector<double> CosForAngles, SinForAngles;
    bool ball_moving;

    void chg_dir_angle();
    void CalculateAngles();
public:
    BallMgr(int radius);
    void reinit();
    void draw(SDL_Renderer *renderer, bool clean = false);
    bool checkCollisionWithScreen();
};


#endif // BALLMGR_H_INCLUDED
