#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include "Scene.h"
#include "IBallManager.h"

class SceneGame: public Scene
{
private:
    IBallMgr *ballmgr;
    RectMgr *rectUp, *rectDown;
    int rect_w, rect_h;
    bool first_render;
public:
    SceneGame();
    void render(SDL_Renderer *renderer);
    void render_clean(SDL_Renderer *renderer);
    void process_mouse_motion(Sint32 x, Sint32 y);
    void process_keyboard_keydown(SDL_Keycode keycode);
};


#endif // GAMESCENE_H_INCLUDED
