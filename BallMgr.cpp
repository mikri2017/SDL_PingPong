#include "BallMgr.h"

BallMgr::BallMgr(int radius)
{
    srand(time(NULL));

    ball = new Ball();
    ball->setRadius(radius);

    reinit();
}

void BallMgr::reinit()
{
    p_ball_centre.x = SCREEN_WIDTH / 2;
    p_ball_centre.y = SCREEN_HEIGHT / 2;

    ball->setCentreXY(p_ball_centre.x, p_ball_centre.y);
    ball_cleaner = ball->getRectArea();

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

    // Вычисляем sin и cos этого угла
    dir_angle_cos = cos(dir_angle);
    dir_angle_sin = sin(dir_angle);

    // Сбрасываем длину направляющей
    dir_line_len = 0;
}

void BallMgr::draw(SDL_Renderer *renderer, bool clean)
{
    if(clean)
    {
        p_ball_centre.x = p_ball_centre.x + dir_angle_cos * dir_line_len;
        p_ball_centre.y = p_ball_centre.y + dir_angle_sin * dir_line_len;
        ball_cleaner = ball->getRectArea();

        // Убираем старое изображение шарика
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderFillRect(renderer, &ball_cleaner);
    }
    else
    {
        // Перемещаем шарик вдоль выбранной направляющей
        dir_line_len++;

        ball->setCentreXY(p_ball_centre.x, p_ball_centre.y);

        // Рисуем новое изображение шарика
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
        ball->draw(renderer);
    }
}
