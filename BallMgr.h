#ifndef BALLMGR_H_INCLUDED
#define BALLMGR_H_INCLUDED

#include "Ball.h"

class BallMgr
{
private:
    Ball *ball;
    SDL_Rect ball_cleaner;
public:
    BallMgr();
    void setCentreXY(int x, int y);
    void setRadius(int r);
    void draw(SDL_Renderer *renderer);
};


#endif // BALLMGR_H_INCLUDED
