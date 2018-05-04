#include "BallMgrSimple.h"
#include "RectMgr.h"
#include <ctime>

//возвращает true, если сгенерировано четное число
static inline bool evenUnevenGenerate ()
{
    int number = rand() % 100;
    return (number % 2 == 0);
}

// задает направлении, на основании случайного числа
static float initDirection (float direction)
{
    if (evenUnevenGenerate())
        direction *= -1.;
    return direction;
}


BallMgrSimple::BallMgrSimple (size_t radius)
    : yspeed(3.), xspeed(2.), bounce(1.05)
{
    ball.reset(new Ball());
    ball->setRadius(radius);
    reinit();
}

BallMgrSimple::~BallMgrSimple()
{
#ifdef DEBUG_MESSAGES_SHOW
    std::cout << "BallMgrSimple end\n";
#endif // DEBUG_MESSAGES_SHOW
}

// implementation for IBallMgr

void BallMgrSimple::reinit()
{
    srand(time(NULL));

    ball_point.x = SCREEN_WIDTH / 2;
    ball_point.y = SCREEN_HEIGHT / 2;
    ball->setCentreXY(ball_point.x, ball_point.y);
    ball_cleaner = ball->getRectArea();

    xspeed = initDirection(3.);
    yspeed = initDirection(2.);

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

CollisionType BallMgrSimple::checkCollisionWithScreen ()
{
    int radius = ball->getRadius();
    Ball::BallBound ballBound = ball->getBallBound();

    if (ballBound.l < 0)
    {
        ball_point.x = radius;
        flipHorizontally();
        return leftRight;
    }

    if (ballBound.r > SCREEN_WIDTH)
    {
        ball_point.x = SCREEN_WIDTH - radius;
        flipHorizontally();
        return leftRight;
    }

    if (ballBound.t < 0)
    {
        ball_point.y = radius;
        flipVertically();
        return topBottom;
    }

    if (ballBound.b > SCREEN_HEIGHT)
    {
        ball_point.y = SCREEN_HEIGHT - radius;
        flipVertically();
        return topBottom;
    }
    return none;
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
