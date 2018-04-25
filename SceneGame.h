#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include "Scene.h"
#include "BallMgr.h"
#include "Rect.h"

class SceneGame: public Scene
{
private:
    SDL_Point p_ball_start;
    BallMgr *ballmgr;
    Rect *rectUp, *rectDown;
public:
    SceneGame();
    void render(SDL_Renderer *renderer);
    void process_mouse_motion(Sint32 x, Sint32 y);
};


#endif // GAMESCENE_H_INCLUDED
