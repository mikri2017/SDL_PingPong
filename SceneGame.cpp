#include "SceneGame.h"
#include <iostream>

SceneGame::SceneGame()
{
    p_ball_start.x = 100;
    p_ball_start.y = 100;
	ballmgr = new BallMgr(p_ball_start, 25);

    rectUp = new Rect();
    rectUp->setBeginXY(0, 0);
    rectUp->setHeight(50);
    rectUp->setWidth(200);

    rectDown = new Rect();
    rectDown->setBeginXY(0, SCREEN_HEIGHT - 50);
    rectDown->setHeight(50);
    rectDown->setWidth(200);
}

void SceneGame::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    ballmgr->draw(renderer);
    rectUp->draw(renderer);
    rectDown->draw(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(50);
}

void SceneGame::process_mouse_motion(Sint32 x, Sint32 y)
{
    std::cout << "x= " << x << " y=" << y << std::endl;
}
