#include "Ball.h"

Ball::Ball()
{
    p_centre.x = 0;
    p_centre.y = 0;
    radius = 0;
    CalculateAngles();
}

void Ball::CalculateAngles()
{
    for(int i=0; i<360; i++)
    {
        CosForAngles.push_back(cos(i*PI_by_180));
        SinForAngles.push_back(sin(i*PI_by_180));
    }
}

void Ball::setCentreXY(int x, int y)
{
    // x и y должны быть неотрицательны
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    p_centre.x = x;
    p_centre.y = y;
}

void Ball::setRadius(int r)
{
    // Радиус должен быть неотрицательным
    if(r < 0)
        r = 0;
    radius = r;
}

void Ball::draw(SDL_Renderer *renderer)
{
    //Рисуем шарик
    SDL_Point p_dest;

    for(int i=0;i<360;i++)
    {
        p_dest.x = p_centre.x + CosForAngles[i] * radius;
        p_dest.y = p_centre.y + SinForAngles[i] * radius;
        SDL_RenderDrawLine(renderer, p_centre.x, p_centre.y, p_dest.x, p_dest.y);
    }
}
