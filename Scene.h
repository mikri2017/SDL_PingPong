#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "DebugParams.h"
#include "MainConstants.h"
#include <SDL3/SDL.h>

class Scene
{
protected:
    bool b_paused = true;
public:
    virtual ~Scene() {};
    void setPaused(bool paused);
    bool getPauseState();
    virtual SDL_AppResult app_iter(AppState *as) = 0;
    virtual gameReaction process_mouse_motion(float x, float y) = 0;
    virtual gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event) = 0;
    virtual gameReaction process_keyboard_keydown(SDL_Scancode scancode) = 0;
};

#endif // SCENE_H_INCLUDED
