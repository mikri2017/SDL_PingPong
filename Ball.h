#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <vector>
#include <SDL2/SDL.h>
#include <math.h>
#include "MainConstants.h"

class Ball
{
private:
    SDL_Point p_centre;
    int radius;
    std::vector<double> CosForAngles, SinForAngles;
    void SetDirectionAngle(double new_angle);
    void CalculateAngles();
    void drawCircle(SDL_Renderer* renderer);
    void fillCircle (SDL_Renderer* renderer);
public:
    struct BallBound {
        int l,r,t,b;
    };

    Ball();
    ~Ball();
    void setCentreXY(int x, int y);
    void setRadius(int r);
    int getRadius();
    void draw(SDL_Renderer *renderer);
    SDL_Rect getRectArea();
    BallBound getBallBound() const;
};

#endif // BALL_H_INCLUDED
