#ifndef CHECKBOX_H_INCLUDED
#define CHECKBOX_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>
#include "FontMgr.h"

class CheckBox
{
private:
    bool b_checked;
    std::string s_caption;
    SDL_Rect chkbx;
    FontMgr *font_caption;
    SDL_Color font_color;
    int font_margin_left;
public:
    CheckBox();
    ~CheckBox();
    bool getCheckState();
    void setCheckState(bool checked);
    void setCaption(std::string caption);
    void setPosition(int x, int y);
    void setSize(int side_len);
    bool checkHover(int x, int y);
    void draw(SDL_Renderer *renderer);
};

#endif // CHECKBOX_H_INCLUDED
