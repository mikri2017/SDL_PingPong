#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "MainConstants.h"
#include <SDL2/SDL.h>

class Scene
{
protected:
    bool b_paused = true;
    bool b_first_render = true;
public:
    virtual ~Scene() {};
    void setPaused(bool paused);
    bool getPauseState();
    void setFirstRenderState(bool first);
    virtual void render(SDL_Renderer *renderer) = 0;
    virtual gameReaction process_mouse_motion(Sint32 x, Sint32 y) = 0;
    virtual gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event) = 0;
    virtual gameReaction process_keyboard_keydown(SDL_Keycode keycode) = 0;
};

#endif // SCENE_H_INCLUDED
