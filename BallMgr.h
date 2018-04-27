#ifndef BALLMGR_H_INCLUDED
#define BALLMGR_H_INCLUDED

#include <ctime>
#include <math.h>
#include "Ball.h"
#include "RectMgr.h"

class BallMgr
{
private:
    Ball *ball;
    SDL_Rect ball_cleaner;
    SDL_Point p_ball_centre;
    int dir_angle;
    int checkCollisionAngles[3];
    float dir_angle_cos, dir_angle_sin;
    float dir_line_len;
    std::vector<double> CosForAngles, SinForAngles;
    bool ball_moving;

    void chg_dir_angle();
    void CalculateAngles();
    void updateCollisionAngles();
public:
    BallMgr(int radius);
    void reinit();
    void draw(SDL_Renderer *renderer, bool clean = false);
    void flipVertically();
    void flipHorizontally();
    bool checkCollisionWithScreen();
    void checkCollisionWithRect(RectMgr *rect);
};


#endif // BALLMGR_H_INCLUDED
