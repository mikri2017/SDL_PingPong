#include "BallMgrSimple.h"

#include "Ball.h"
#include "RectMgr.h"

BallMgrSimple::BallMgrSimple (size_t radius)
    : yspeed(3.), xspeed(2.), bounce(1.01)
{
    ball = new Ball();
    ball->setRadius(radius);
    reinit();
}

// implementation for IBallMgr

void BallMgrSimple::reinit()
{
    ball_point.x = SCREEN_WIDTH / 2;
    ball_point.y = SCREEN_HEIGHT / 2;
    ball->setCentreXY(ball_point.x, ball_point.y);
    ball_cleaner = ball->getRectArea();
    xspeed = 3.;
    yspeed = 2.;
}

void BallMgrSimple::draw (SDL_Renderer *renderer, bool clean)
{
    if (clean)
    {
        ball_cleaner = ball->getRectArea();
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderFillRect(renderer, &ball_cleaner);
    }
    else
    {
        ball_point.x += xspeed;
        ball_point.y += yspeed;
        ball->setCentreXY(ball_point.x, ball_point.y);
        // Рисуем новое изображение шарика
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
        ball->draw(renderer);

        if(checkCollisionWithScreen())
            reinit();
    }
}

void BallMgrSimple::flipHorizontally ()
{
    xspeed = -xspeed;
}

void BallMgrSimple::flipVertically ()
{
    yspeed = -yspeed;
}

bool BallMgrSimple::checkCollisionWithScreen ()
{
    int radius = ball->getRadius();

    if (ball_point.x - radius < 0 || ball_point.x + radius > SCREEN_WIDTH)
    {
        flipHorizontally();
        return false;
    }

    if (ball_point.y + radius > SCREEN_HEIGHT || ball_point.y - radius < 0)
    {
        flipVertically();
        return true;
    }
    return false;
}

void BallMgrSimple::checkCollisionWithRect (RectMgr *rect)
{
    SDL_Rect p_rect = rect->getRect();
    int radius = ball->getRadius();

    if (ball_point.x >= p_rect.x && ball_point.x <= p_rect.x + p_rect.w)
    {
        // Проверяем верхнюю ракетку
        if (p_rect.y == 0)
        {
            if (ball_point.y - radius <= p_rect.y + p_rect.h)
            {
                flipVertically();
                xspeed *= bounce;
                yspeed *= bounce;
            }
        }
        else
        {
            if (ball_point.y + radius >= p_rect.y)
            {
                flipVertically();
                xspeed *= bounce;
                yspeed *= bounce;
            }
        }
    }



}