#include "BallMgr.h"

BallMgr::BallMgr()
{
    ball = new Ball();
}

void BallMgr::setCentreXY(int x, int y)
{
    ball->setCentreXY(x, y);

}

void BallMgr::setRadius(int r)
{
    ball->setRadius(r);
}

void BallMgr::draw(SDL_Renderer *renderer)
{
    ball->draw(renderer);
}
