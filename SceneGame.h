#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include <string>
#include "Scene.h"
#include "IBallManager.h"
#include "RectMgr.h"
#include "FontMgr.h"
#include "SoundMgr.h"

typedef enum {
    mikriVision,
    nZemekisVision
} ball_move_logic;

class SceneGame: public Scene
{
private:
    IBallMgr *ballmgr;
    RectMgr *rectUp, *rectDown;
    int rect_w, rect_h;
    bool first_render;

    FontMgr font_game_info;
    SoundMgr sounds;
    SDL_Color font_color;

    int score, best;
    int delay_time;
public:
    SceneGame(ball_move_logic bm_logic = ball_move_logic::mikriVision);
    void render(SDL_Renderer *renderer);
    void render_clean(SDL_Renderer *renderer);
    void process_mouse_motion(Sint32 x, Sint32 y);
    void process_mouse_button_event(SDL_MouseButtonEvent m_btn_event);
    void process_keyboard_keydown(SDL_Keycode keycode);
};


#endif // GAMESCENE_H_INCLUDED
