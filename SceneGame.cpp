#include "SceneGame.h"
#include "RectMgr.h"
//#include "BallMgr.h"
#include "BallMgr2.h"

SceneGame::SceneGame()
{
    first_render = true;

	ballmgr = new BallMgr2(25);

	rect_w = 200;
	rect_h = 50;

    rectUp = new RectMgr();
    rectUp->setBeginXY(0, 0);
    rectUp->setHeight(rect_h);
    rectUp->setWidth(rect_w);

    rectDown = new RectMgr();
    rectDown->setBeginXY(0, SCREEN_HEIGHT - rect_h);
    rectDown->setHeight(rect_h);
    rectDown->setWidth(rect_w);
}

void SceneGame::render(SDL_Renderer *renderer)
{
    if(first_render)
    {
        first_render = false;

        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    }


    // ������������ ������������
    ballmgr->checkCollisionWithRect(rectUp);
    ballmgr->checkCollisionWithRect(rectDown);

    // ������� ����� �� ������� ��������
    render_clean(renderer);

    // ������ �����
    rectUp->draw(renderer);
    rectDown->draw(renderer);
    ballmgr->draw(renderer);


    SDL_RenderPresent(renderer);

    SDL_Delay(50);
}

void SceneGame::render_clean(SDL_Renderer *renderer)
{
    // ������� ������� ������� �����
    rectUp->draw(renderer, true);
    rectDown->draw(renderer, true);
    ballmgr->draw(renderer, true);
}

void SceneGame::process_mouse_motion(Sint32 x, Sint32 y)
{
    // ��������� ��������� �������
    // ����� ������� �� ���� �� �����
    if( x + rect_w/2 > SCREEN_WIDTH)
        x = SCREEN_WIDTH - rect_w/2;

    rectUp->setBeginXY(x - rect_w/2, 0);
    rectDown->setBeginXY(x - rect_w/2, SCREEN_HEIGHT - rect_h);
}

void SceneGame::process_keyboard_keydown(SDL_Keycode keycode)
{
    if(keycode == SDLK_LEFT)
        ballmgr->flipVertically();
    if(keycode == SDLK_UP)
        ballmgr->flipHorizontally();
}
