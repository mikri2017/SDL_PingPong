#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <SDL2/SDL.h>

class Scene
{
public:
    virtual void render(SDL_Renderer *renderer);
    virtual void process_mouse_motion(Sint32 x, Sint32 y);
    virtual void process_keyboard_keydown(SDL_Keycode keycode);
};

#endif // SCENE_H_INCLUDED
