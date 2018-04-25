#include "BallMgr.h"

BallMgr::BallMgr(SDL_Point p_begin, int radius)
{
    ball = new Ball();
    ball->setCentreXY(p_begin.x, p_begin.y);
    ball->setRadius(radius);
    srand(time(NULL));
    chg_dir_angle();
}

void BallMgr::chg_dir_angle()
{
    // Определяемся с направлением
    // 1. Шарик летит вниз или вверх
    int direction = rand()%50;
    // Для разнообразия выбора - вверх или вниз
    if(direction%2 == 0) // Летим вверх - от 30 до 150 градусов
        dir_angle = rand()%120 + 31;
    else // Летим вниз - от 210 до 330
        dir_angle = rand()%120 + 211;
}

void BallMgr::draw(SDL_Renderer *renderer)
{
    ball->draw(renderer);
}
