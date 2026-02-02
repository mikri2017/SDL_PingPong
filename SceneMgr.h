#ifndef SCENEMGR_H_INCLUDED
#define SCENEMGR_H_INCLUDED

#include "DebugParams.h"
#include <vector>
#include <SDL3/SDL.h>
#include "MainConstants.h"
#include "Scene.h"
#include "SceneGame.h"

class SceneMgr
{
private:
    Scene *active;
    std::vector<Scene*> v_scenes;
    void add_scene(Scene *scene, bool set_active = true);
    void delete_all_scenes();
    void reinit();
    void start_new_game(ball_move_logic bmv = ball_move_logic::mikriVision);
public:
    SceneMgr();
    ~SceneMgr();
    SDL_AppResult app_iter(AppState *as);
    gameReaction process_mouse_motion(float x, float y);
    gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    gameReaction process_keyboard_keydown(SDL_Scancode scancode);
};

#endif // SCENEMGR_H_INCLUDED
