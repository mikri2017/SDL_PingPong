#include "RectMgr.h"

RectMgr::RectMgr()
{
    rect = new Rect();
    rect_cleaner = new Rect();
}

RectMgr::~RectMgr()
{
    delete rect;
    delete rect_cleaner;
    std::cout << "RectMgr end\n";
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

SDL_Rect RectMgr::getRect()
{
    SDL_Point tmp_point;
    tmp_point = rect->getBeginXY();
    SDL_Rect tmp_rect;
    tmp_rect.x = tmp_point.x;
    tmp_rect.y = tmp_point.y;
    tmp_rect.w = rect->getWidth();
    tmp_rect.h = rect->getHeight();
    return tmp_rect;
}
