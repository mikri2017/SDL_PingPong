#ifndef SCENEMENUPAUSE_H_INCLUDED
#define SCENEMENUPAUSE_H_INCLUDED

#include "DebugParams.h"
#include "Scene.h"
#include "Button.h"

class SceneMenuPause : public Scene
{
private:
    int delay_time;
    SDL_Point menuPosition, btn_size;
    SDL_FRect frect_backgrnd;
    int btn_w, btn_h;
    Button *btn_continue, *btn_main_menu, *btn_exit;
public:
    SceneMenuPause();
    ~SceneMenuPause();
    SDL_AppResult app_iter(AppState *as);
    gameReaction process_mouse_motion(float x, float y);
    gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    gameReaction process_keyboard_keydown(SDL_Scancode scancode);
};

#endif // SCENEMENUPAUSE_H_INCLUDED
