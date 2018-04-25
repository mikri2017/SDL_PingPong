#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
    s_game = new SceneGame();
    add_scene(s_game);
}

void SceneMgr::add_scene(Scene *scene, bool set_active)
{
    v_scenes.push_back(scene);
    if(set_active)
        active = scene;
}

void SceneMgr::render(SDL_Renderer *renderer)
{
    active->render(renderer);
}

void SceneMgr::process_mouse_motion(Sint32 x, Sint32 y)
{
    active->process_mouse_motion(x, y);
}

void SceneMgr::process_keyboard_keydown(SDL_Keysym keysym)
{

}
