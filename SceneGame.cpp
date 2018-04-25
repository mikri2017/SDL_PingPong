#include "SceneGame.h"

SceneGame::SceneGame()
{
    p_ball_start.x = 100;
    p_ball_start.y = 100;
	ballmgr = new BallMgr(p_ball_start, 25);

	rect_w = 200;
	rect_h = 50;

    rectUp = new Rect();
    rectUp->setBeginXY(0, 0);
    rectUp->setHeight(rect_h);
    rectUp->setWidth(rect_w);

    rectDown = new Rect();
    rectDown->setBeginXY(0, SCREEN_HEIGHT - rect_h);
    rectDown->setHeight(rect_h);
    rectDown->setWidth(rect_w);
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
    // Управляем движением ракеток
    // Чтобы ракетка не ушла за экран
    if( x + rect_w/2 > SCREEN_WIDTH)
        x = SCREEN_WIDTH - rect_w/2;

    rectUp->setBeginXY(x - rect_w/2, 0);
    rectDown->setBeginXY(x - rect_w/2, SCREEN_HEIGHT - rect_h);
}
