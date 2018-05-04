#include "FontMgr.h"

FontMgr::FontMgr()
{
    TTF_Init();

    scn_indent = 10;
    font_size = 10;
    font_name = "assets/fonts/XoloniumBold.ttf";
    font = TTF_OpenFont(font_name.c_str(), font_size);

    if(!font)
        std::cout << SDL_GetError() << std::endl;

    font_color = {0, 0, 255};
    letter_size_px = 20;
    x_start_left = 0;
    x_start_right = SCREEN_WIDTH;
}

FontMgr::~FontMgr()
{
    TTF_CloseFont(font);
    TTF_Quit();
    std::cout << "FontMgr end\n";
}

void FontMgr::setLetterSizeInPX(size_t l_size_px)
{
    letter_size_px = l_size_px;
}

void FontMgr::setFontName(std::string f_name)
{
    font_name = f_name;
    reloadFont();
}

void FontMgr::setFontColor(const SDL_Color &f_color)
{
    font_color = f_color;
    reloadFont();
}

void FontMgr::setTextXStartFrom(int x_left, int x_right)
{
    x_start_left = x_left;
    x_start_right = x_right;
}

void FontMgr::setFontSize(int f_size)
{
    font_size = f_size;
    reloadFont();
}

void FontMgr::paintText(SDL_Renderer *renderer, std::string text, int y, int h, fontAlign f_align)
{
    int x;
    int text_width_px = letter_size_px * static_cast<int>(text.length());

    // Настраиваем форматирование текста
    if(f_align == fontAlign::right) // по правому краю
        x = x_start_right - scn_indent - text_width_px;
    else if(f_align == fontAlign::centre) // по центру
        x = x_start_left + (x_start_right - x_start_left - text_width_px) / 2;
    else // по левому краю
        x = x_start_left;

    SDL_Rect dstrect = { x, y, text_width_px, h };

    // Русский язык в тексте не поддерживается :(
    // c_str() не проносит нормально русские буквы
    // Заполнение char* русскими буквами и его отдача дает русский язык на экране
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), font_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void FontMgr::reloadFont()
{
    TTF_CloseFont(font);
    font = TTF_OpenFont(font_name.c_str(), font_size);
}
