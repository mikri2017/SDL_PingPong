#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>

class FontMgr;

class Button
{
private:
    std::string s_caption;
    SDL_Rect btn;
    FontMgr *font_caption;
    SDL_Color font_color;
    int font_margin_left_right;
    int font_margin_up_dowm;
public:
    Button();
    ~Button();
    void setCaption(std::string caption);
    void setPosition(int x, int y);
    void setSize(int w, int h);
    bool checkHover(int x, int y);
    void draw(SDL_Renderer *renderer);
};


#endif // BUTTON_H_INCLUDED
