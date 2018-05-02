#ifndef SCENEMGR_H_INCLUDED
#define SCENEMGR_H_INCLUDED

#include <vector>
#include <SDL2/SDL.h>
#include "Scene.h"

class SceneMgr
{
private:
    Scene *active;
    std::vector<Scene*> v_scenes;
    void add_scene(Scene *scene, bool set_active = true);
public:
    SceneMgr();
    void render(SDL_Renderer *renderer);
    void process_mouse_motion(Sint32 x, Sint32 y);
    void process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    void process_keyboard_keydown(SDL_Keycode keycode);
};

#endif // SCENEMGR_H_INCLUDED
