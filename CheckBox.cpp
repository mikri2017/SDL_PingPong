#include "CheckBox.h"

CheckBox::CheckBox()
{
    b_checked = false;
    s_caption = "";
    chkbx.x = 0;
    chkbx.y = 0;
    chkbx.w = 0;
    chkbx.h = 0;

    // Задаем параметры текста
    font_color = {255, 0, 0};
    font_margin_left = 10;

    font_caption = new FontMgr();
    font_caption->setFontName("assets/fonts/XoloniumBold.ttf");
    font_caption->setFontSize(10);
    font_caption->setFontColor(font_color);
    font_caption->setLetterSizeInPX(20);
    font_caption->setTextXStartFrom(0, 0);
}

CheckBox::~CheckBox()
{
    delete font_caption;
    std::cout << "CheckBox end\n";
}

bool CheckBox::getCheckState()
{
    return b_checked;
}

void CheckBox::setCheckState(bool checked)
{
    b_checked = checked;
}

void CheckBox::setCaption(std::string caption)
{
    s_caption = caption;
}

void CheckBox::setPosition(int x, int y)
{
    chkbx.x = x;
    chkbx.y = y;
}

void CheckBox::setSize(int side_len)
{
    chkbx.w = side_len;
    chkbx.h = side_len;
    font_caption->setTextXStartFrom(chkbx.x + chkbx.w + font_margin_left);
}

bool CheckBox::checkHover(int x, int y)
{
    if(x >= chkbx.x && x <= chkbx.x + chkbx.w)
    {
        if(y >= chkbx.y && y <= chkbx.y + chkbx.h)
            return true;
    }

    return false;
}

void CheckBox::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &chkbx);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &chkbx);
    font_caption->paintText(renderer, s_caption, chkbx.y, chkbx.h, fontAlign::left);
    if(b_checked)
    {
        SDL_RenderDrawLine(renderer, chkbx.x, chkbx.y, chkbx.x + chkbx.w, chkbx.y + chkbx.h);
        SDL_RenderDrawLine(renderer, chkbx.x + chkbx.w, chkbx.y, chkbx.x, chkbx.y + chkbx.h);
    }
}
