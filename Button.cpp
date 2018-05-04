#include "Button.h"
#include "FontMgr.h"

Button::Button()
{
    btn.x = 0;
    btn.y = 0;
    btn.w = 0;
    btn.h = 0;
    s_caption = "";

    // Задаем параметры текста
    font_color = {255, 0, 0};
    font_margin_left_right = 10;
    font_margin_up_dowm = 5;

    font_caption = new FontMgr();
    font_caption->setFontName("assets/fonts/XoloniumBold.ttf");
    font_caption->setFontSize(10);
    font_caption->setFontColor(font_color);
    font_caption->setLetterSizeInPX(20);
}

Button::~Button()
{
    delete font_caption;
#ifdef DEBUG_MESSAGES_SHOW
    std::cout << "Button end\n";
#endif // DEBUG_MESSAGES_SHOW
}

void Button::setCaption(std::string caption)
{
    s_caption = caption;
}

void Button::setPosition(int x, int y)
{
    btn.x = x;
    btn.y = y;
}

void Button::setSize(int w, int h)
{
    btn.w = w;
    btn.h = h;
    font_caption->setTextXStartFrom(btn.x + font_margin_left_right, btn.x + btn.w - font_margin_left_right);
}

bool Button::checkHover(int x, int y)
{
    if(x >= btn.x && x <= btn.x + btn.w)
    {
        if(y >= btn.y && y <= btn.y + btn.h)
            return true;
    }

    return false;
}

void Button::draw(SDL_Renderer *renderer)
{
    SDL_RenderDrawRect(renderer, &btn);
    font_caption->paintText(renderer, s_caption, btn.y, btn.h - font_margin_up_dowm, fontAlign::centre);
}
