#include "BallMgr.h"
#include <iostream>

BallMgr::BallMgr(int radius)
{
    srand(time(NULL));

    CalculateAngles();

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

    ball_moving = true;
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

    // Градусы идут по часовой стрелке
    dir_angle = dir_angle * (-1);

    // Вычисляем sin и cos этого угла
    dir_angle_cos = cos(dir_angle * PI_by_180);
    dir_angle_sin = sin(dir_angle * PI_by_180);

    // Сбрасываем длину направляющей
    dir_line_len = 0;

    std::cout << "dir_angle = " << dir_angle << std::endl;

    // Определяем соседние углы для проверки столкновения
    if(dir_angle >= 0 && dir_angle < 90)
    {
        checkCollisionAngles[0] = 0;
        checkCollisionAngles[1] = dir_angle;
        checkCollisionAngles[2] = 90;
    }
    else if(dir_angle >= 90 && dir_angle < 180)
    {
        checkCollisionAngles[0] = 90;
        checkCollisionAngles[1] = dir_angle;
        checkCollisionAngles[2] = 180;
    }
    else if(dir_angle >= 180 && dir_angle < 270)
    {
        checkCollisionAngles[0] = 180;
        checkCollisionAngles[1] = dir_angle;
        checkCollisionAngles[2] = 270;
    }
    else if(dir_angle >= 270 && dir_angle < 360)
    {
        checkCollisionAngles[0] = 270;
        checkCollisionAngles[1] = dir_angle;
        checkCollisionAngles[2] = 360;
    }

}

void BallMgr::CalculateAngles()
{
    for(int i=0; i<360; i++)
    {
        CosForAngles.push_back(cos(i*PI_by_180));
        SinForAngles.push_back(sin(i*PI_by_180));
    }
}

void BallMgr::draw(SDL_Renderer *renderer, bool clean)
{
    if(clean)
    {
        ball_cleaner = ball->getRectArea();

        // Перемещаем шарик вдоль выбранной направляющей
        dir_line_len++;
        p_ball_centre.x = p_ball_centre.x + dir_angle_cos * dir_line_len;
        p_ball_centre.y = p_ball_centre.y + dir_angle_sin * dir_line_len;

        ball->setCentreXY(p_ball_centre.x, p_ball_centre.y);

        // Убираем старое изображение шарика
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderFillRect(renderer, &ball_cleaner);
    }
    else
    {
        // Рисуем новое изображение шарика
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
        ball->draw(renderer);

        if(checkCollisionWithScreen())
            reinit();
    }
}

bool BallMgr::checkCollisionWithScreen()
{
    for(int i = 0; i < 3; i++)
    {
        int p_dest_x = p_ball_centre.x + CosForAngles[checkCollisionAngles[i]] * ball->getRadius();
        int p_dest_y = p_ball_centre.y + SinForAngles[checkCollisionAngles[i]] * ball->getRadius();

        if(p_dest_x >= SCREEN_WIDTH || p_dest_x <= 0)
        {
            dir_angle = 180 - dir_angle;

            dir_angle_cos = cos(dir_angle * PI_by_180);
            dir_angle_sin = sin(dir_angle * PI_by_180);

            dir_line_len = 0;

            if(p_dest_x >= SCREEN_WIDTH)
                p_ball_centre.x = SCREEN_WIDTH - ball->getRadius();
            else p_ball_centre.x = 0 + ball->getRadius();

            p_ball_centre.y = p_ball_centre.y + dir_angle_sin * dir_line_len;

            ball->setCentreXY(p_ball_centre.x, p_ball_centre.y);


            if(p_dest_x >= SCREEN_WIDTH)
                std::cout << "SCREEN_WIDTH" << std::endl;
            else std::cout << "0" << std::endl;

            return false;// Столкнулись с левой/правой стенкой
        }

        if(p_dest_y >= SCREEN_HEIGHT || p_dest_y <= 0)
        {
            p_ball_centre.y = SCREEN_HEIGHT - ball->getRadius();
            return true;// Столкнулись с нижней стенкой
        }
    }

    return false;
}

bool BallMgr::checkCollisionWithRect(RectMgr *rect)
{
    SDL_Rect p_rect = rect->getRect();
}
