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
    Ball::BallBound ballBound = ball->getBallBound();

    if (ballBound.l < 0)
    {
        ball_point.x = radius;
        flipHorizontally();
        return false;
    }

    if (ballBound.r > SCREEN_WIDTH)
    {
        ball_point.x = SCREEN_WIDTH - radius;
        flipHorizontally();
        return false;
    }

    if (ballBound.t < 0)
    {
        ball_point.y = radius;
        flipVertically();
        return true;
    }

    if (ballBound.b > SCREEN_HEIGHT)
    {
        ball_point.y = SCREEN_HEIGHT - radius;
        flipVertically();
        return true;
    }
    return false;
}


bool BallMgrSimple::checkCollisionWithRect (RectMgr *rect)
{
    SDL_Rect p_rect = rect->getRect();
    int radius = ball->getRadius();
    Ball::BallBound ballBound = ball->getBallBound();

    // Если не в зоне ракеток проверять не надо
    if (ball_point.x >= p_rect.x && ball_point.x <= p_rect.x + p_rect.w)
    {
        // Проверяем верхнюю ракетку
        if (p_rect.y == 0)
        {
            if (ballBound.t < p_rect.y + p_rect.h)
            {
                ball_point.y = p_rect.y + p_rect.h + radius;
                flipVertically();
                xspeed *= bounce;
                yspeed *= bounce;
                return true;
            }
        }
        else
        {
            if (ballBound.b > p_rect.y)
            {
                ball_point.y = p_rect.y - radius;
                flipVertically();
                xspeed *= bounce;
                yspeed *= bounce;
                return true;
            }
        }
    }
    return false;
}