#ifndef SCENEMGR_H_INCLUDED
#define SCENEMGR_H_INCLUDED

#include <vector>
#include <SDL2/SDL.h>
#include "Scene.h"
#include "SceneGame.h"

class SceneMgr
{
private:
    Scene *active;
    SceneGame *s_game;
    std::vector<Scene*> v_scenes;
    void add_scene(Scene *scene, bool set_active = true);
public:
    SceneMgr();
    void render(SDL_Renderer *renderer);
    void process_mouse_motion(Sint32 x, Sint32 y);
    void process_keyboard_keydown(SDL_Keysym keysym);
};

#endif // SCENEMGR_H_INCLUDED
