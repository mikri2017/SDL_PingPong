#ifndef SCENEMENU_H_INCLUDED
#define SCENEMENU_H_INCLUDED

#include "Scene.h"
#include "Button.h"
#include "CheckBox.h"

class SceneMenu : public Scene
{
private:
    bool first_render;
    int delay_time;
    SDL_Point menuPosition, btn_size;
    int chkbx_side_len, btn_w, btn_h;
    Button btn_new_game, btn_exit;
    CheckBox chkbx_mikri, chkbx_nzemekis;
public:
    SceneMenu();
    void render(SDL_Renderer *renderer);
    void process_mouse_motion(Sint32 x, Sint32 y);
    void process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    void process_keyboard_keydown(SDL_Keycode keycode);
};

#endif // SCENEMENU_H_INCLUDED
