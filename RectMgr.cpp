#include "RectMgr.h"

RectMgr::RectMgr()
{
    rect = new Rect();
    rect_cleaner = new Rect();
}

void RectMgr::setBeginXY(int x, int y)
{
    rect->setBeginXY(x, y);
    rect_cleaner->setBeginXY(0, y);
}

void RectMgr::setWidth(int w)
{
    rect->setWidth(w);
    rect_cleaner->setWidth(SCREEN_WIDTH);
}

void RectMgr::setHeight(int h)
{
    rect->setHeight(h);
    rect_cleaner->setHeight(h);
}

void RectMgr::draw(SDL_Renderer *renderer, bool clean)
{
    if(clean)
    {
        // Убираем старое изображение платформы
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        rect_cleaner->draw(renderer);
    }
    else
    {
        // Рисуем новое изображение платформы
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
        rect->draw(renderer);
    }
}
