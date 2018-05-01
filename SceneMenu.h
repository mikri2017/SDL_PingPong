#ifndef SCENEMENU_H_INCLUDED
#define SCENEMENU_H_INCLUDED

#include "Scene.h"

class SceneMenu : public Scene
{
private:
    bool first_render;
public:
    void render(SDL_Renderer *renderer);
    void process_mouse_motion(Sint32 x, Sint32 y);
    void process_keyboard_keydown(SDL_Keycode keycode);
};

#endif // SCENEMENU_H_INCLUDED
