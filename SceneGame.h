#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include "DebugParams.h"
#include <string>
#include "Scene.h"
#include "IBallManager.h"
#include "RectMgr.h"
#include "FontMgr.h"
#include "SoundMgr.h"

enum ball_move_logic {
    mikriVision,
    nZemekisVision
};

class SceneGame: public Scene
{
private:
    IBallMgr *ballmgr;
    RectMgr *rectUp, *rectDown;
    int rect_w, rect_h;

    FontMgr *font_game_info;
    SoundMgr *sounds;
    SDL_Color font_color;

    int score, best;
    int delay_time;
public:
    SceneGame(ball_move_logic bm_logic = ball_move_logic::mikriVision);
    ~SceneGame();
    SDL_AppResult app_iter(AppState *as);
    void render_clean(SDL_Renderer *r);
    gameReaction process_mouse_motion(float x, float y);
    gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    gameReaction process_keyboard_keydown(SDL_Scancode scancode);
};

#endif // GAMESCENE_H_INCLUDED
