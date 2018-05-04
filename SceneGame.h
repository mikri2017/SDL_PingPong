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
    void render(SDL_Renderer *renderer);
    void render_clean(SDL_Renderer *renderer);
    gameReaction process_mouse_motion(Sint32 x, Sint32 y);
    gameReaction process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    gameReaction process_keyboard_keydown(SDL_Keycode keycode);
};


#endif // GAMESCENE_H_INCLUDED
