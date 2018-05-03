#include "BallMgr.h"
#include <ctime>
//#include <iostream>

BallMgr::BallMgr(int radius)
{
    srand(time(NULL));

    ball = new Ball();
    ball->setRadius(radius);

    reinit();
}

void BallMgr::reinit()
{
    SDL_Point p_ball_first;
    p_ball_first.x = SCREEN_WIDTH / 2;
    p_ball_first.y = SCREEN_HEIGHT / 2;

    ball->setCentreXY(p_ball_first.x, p_ball_first.y);
    ball_cleaner = ball->getRectArea();

    // Определяемся с направлением
    // 1. Шарик летит вниз или вверх
    int direction = rand()%50;
    // Для разнообразия выбора - вверх или вниз
    if(direction%2 == 0) // Летим вверх - от 30 до 150 градусов
        dir_angle = rand()%120 + 31;
    else // Летим вниз - от 210 до 330
        dir_angle = rand()%120 + 211;

    // Убираем "скучные" углы
    if((dir_angle >= 75 && dir_angle <= 105) || (dir_angle >= 255 && dir_angle <= 285))
        dir_angle += 30;

    // Вычисляем sin и cos этого угла
    dir_angle_cos = cos(dir_angle * PI_by_180);
    dir_angle_sin = sin(dir_angle * PI_by_180);

    SDL_Point p_ball_second;
    p_ball_second.x = p_ball_first.x + dir_angle_cos * 10;
    p_ball_second.y = p_ball_first.y + dir_angle_sin * 10;

    updateLinePath(p_ball_first, p_ball_second);
}

void BallMgr::updateLinePath(SDL_Point p_first, SDL_Point p_second)
{
    // Обновляем направляющую шарик линию
    if(p_first.y != p_second.y) // Избегаем деление на ноль
    {
        SDL_Point p_end_line;
        if(p_second.y > p_first.y)
            p_end_line.y = SCREEN_HEIGHT; // Идем вниз
        else p_end_line.y = 0; // Идем вверх

        // Проверяем на "плохие" углы отражения, близкие прямой линии
        // Слева/справа
        //std::cout << abs(p_second.y - p_first.y) << " <= " << ball->getRadius() << std::endl;
        if(abs(p_second.y - p_first.y) <= ball->getRadius())
        {
            float k_chg_angle;
            if(p_second.x < SCREEN_WIDTH / 2)
                k_chg_angle = 0.2;
            else k_chg_angle = -0.2;

            p_second.x += ball->getRadius() * k_chg_angle;
        }

        // Сверху/снизу
        /*if(abs(p_second.x - p_first.x) <= ball->getRadius())
        {
            float k_chg_angle;
            if(p_second.y < SCREEN_HEIGHT / 2)
                k_chg_angle = 0.0401;
            else k_chg_angle = -0.0401;

            p_second.y += ball->getRadius() * k_chg_angle;
        }*/

        p_end_line.x = ( (p_second.x * p_first.y - p_first.x * p_second.y) - p_end_line.y * (p_second.x - p_first.x) )
                        / (p_first.y - p_second.y);

        //std::cout << "f_x: " << p_first.x << " f_y: " << p_first.y << " s_x: " << p_second.x << " s_y: " << p_second.y << " e_x: " << p_end_line.x << " e_y: " << p_end_line.y << std::endl;
        //std::cout << "e_x: (" << (p_second.x * p_first.y - p_first.x * p_second.y) << " - " << p_end_line.y * (p_second.x - p_first.x) << ") / " << (p_first.y - p_second.y) << std::endl;
        // Генерируем путь движения
        genLinePath(p_first.x, p_first.y, p_end_line.x, p_end_line.y);

        // Сбрасываем счетчик
        linePath_iter = 0;
    }
    else
    {
        // Зашли в тупик, сбрасываем игру
        reinit();
    }
}

void BallMgr::genLinePath(int x1, int y1, int x2, int y2)
{
    // Рисуем линию алгоритмом Брезенхэма
    linePath.clear();

    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    SDL_Point p;
    p.x = x2;
    p.y = y2;
    //linePath.push_back(p);
    //SDL_RenderDrawPoint(renderer, x2, y2);
    //setPixel(x2, y2);
    while(x1 != x2 || y1 != y2)
    {
        p.x = x1;
        p.y = y1;
        linePath.push_back(p);
        //SDL_RenderDrawPoint(renderer, x1, y1);
        //setPixel(x1, y1);
        const int error2 = error * 2;
        //
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void BallMgr::draw(SDL_Renderer *renderer, bool clean)
{
    //for(int i = 0; i < linePath.size(); i++)
    //    SDL_RenderDrawPoint(renderer, linePath[i].x, linePath[i].y);

    if(clean)
    {
        // Убираем старое изображение шарика
        ball_cleaner = ball->getRectArea();
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderFillRect(renderer, &ball_cleaner);
    }
    else
    {
        // Перемещаем шарик дальше вдоль пути
        if(linePath_iter < linePath.size())
            ball->setCentreXY(linePath[linePath_iter].x, linePath[linePath_iter].y);

        // Рисуем новое изображение шарика
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
        ball->draw(renderer);

        linePath_iter++;
    }
}

void BallMgr::flipVertically()
{
    // Отражаем шарик от вертикальной поверхности
    SDL_Point p_second;
    p_second.x = linePath[0].x;
    p_second.y = linePath[0].y + 2 * (linePath[linePath_iter].y - linePath[0].y);
    updateLinePath(linePath[linePath_iter], p_second);
    // Тест плохих углов
    SDL_Point t_f, t_s;
    // Слева
    //t_f.x = 25; t_f.y = 373; t_s.x = 25; t_s.y = 372;
    //t_f.x = 25; t_f.y = 106; t_s.x = 25; t_s.y = 107;
    // Справа
    //t_f.x = SCREEN_WIDTH - 25; t_f.y = 373; t_s.x = SCREEN_WIDTH - 25; t_s.y = 372;
    //t_f.x = SCREEN_WIDTH - 25; t_f.y = 106; t_s.x = SCREEN_WIDTH - 25; t_s.y = 107;
    //updateLinePath(t_f, t_s);
}

void BallMgr::flipHorizontally()
{
    // Отражаем шарик от горизонтальной поверхности
    SDL_Point p_second;
    p_second.x = linePath[0].x + 2 * (linePath[linePath_iter].x - linePath[0].x);
    p_second.y = linePath[0].y;
    updateLinePath(linePath[linePath_iter], p_second);
}

CollisionType BallMgr::checkCollisionWithScreen()
{
    // Проверка столкновения с экраном
    if(linePath_iter < linePath.size())
    {
        // Опредедяем столкновение с боковыми сторонами экрана
        if((linePath[linePath_iter].x + ball->getRadius() >= SCREEN_WIDTH)
            || (linePath[linePath_iter].x - ball->getRadius() <= 0))
        {
            flipVertically();
            return leftRight;
        }

        // Определяем столкновение с нижней и верхней сторонами экрана
        if((linePath[linePath_iter].y + ball->getRadius() >= SCREEN_HEIGHT)
            || (linePath[linePath_iter].y - ball->getRadius() <= 0))
        {
            return topBottom;
        }

    }
    return none;
}

bool BallMgr::checkCollisionWithRect(RectMgr *rect)
{
    // Проверка столкновения с ракеткой
    if(linePath_iter < linePath.size())
    {
        // Получаем данные ракетки
        SDL_Rect p_rect = rect->getRect();

        // Проверяем, что мы в зоне ракеток
        if((linePath[linePath_iter].x >= p_rect.x)
           && (linePath[linePath_iter].x <= p_rect.x + p_rect.w))
        {
            // Определяем направление шарика
            if(linePath[linePath.size() - 1].y > linePath[0].y)
            {
                // Летим вниз
                if(p_rect.y > p_rect.h)
                {
                    // Нижняя ракетка
                    if(linePath[linePath_iter].y + ball->getRadius() >= p_rect.y)
                    {
                        flipHorizontally();
                        return true;
                    }

                }
            }
            else
            {
                // Летим вверх
                if(p_rect.y < p_rect.h)
                {
                    // Верхняя ракетка
                    if(linePath[linePath_iter].y - ball->getRadius() <= p_rect.y + p_rect.h)
                    {
                        flipHorizontally();
                        return true;
                    }

                }
            }
        }
    }

    return false;
}
