#ifndef SCENEMENUPAUSE_H_INCLUDED
#define SCENEMENUPAUSE_H_INCLUDED

#include "Scene.h"
#include "Button.h"

class SceneMenuPause : public Scene
{
private:
    int delay_time;
    SDL_Point menuPosition, btn_size;
    SDL_Rect rect_backgrnd;
    int btn_w, btn_h;
    Button *btn_continue, *btn_main_menu, *btn_exit;
public:
    SceneMenuPause();
    ~SceneMenuPause();
    void render(SDL_Renderer *renderer);
    gameReaction process_mouse_motion(Sint32 x, Sint32 y);
    gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    gameReaction process_keyboard_keydown(SDL_Keycode keycode);
};

#endif // SCENEMENUPAUSE_H_INCLUDED
