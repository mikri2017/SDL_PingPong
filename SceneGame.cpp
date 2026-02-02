#include "MainConstants.h"
#include "SceneGame.h"
#include "BallMgr.h"
#include "BallMgrSimple.h"
#include <iostream>
#include "BallMgr.h"
#include "BallMgrSimple.h"

SceneGame::SceneGame(ball_move_logic bm_logic)
{
    // Выставляем счет игры
    score = 0;
    best = 0;

    // Расставляем элементы игры
    if(bm_logic == ball_move_logic::mikriVision)
    {
        delay_time = 5;
        ballmgr = new BallMgr(25);
    }
    else
    {
        delay_time = 25;
        ballmgr = new BallMgrSimple(25);
    }

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

    // Задаем параметры текста
    font_color = {0, 0, 255};

    font_game_info = new FontMgr();
    font_game_info->setFontName("assets/fonts/XoloniumBold.ttf");
    font_game_info->setFontSize(10);
    font_game_info->setFontColor(font_color);
    font_game_info->setLetterSizeInPX(20);

    // Добавляем звук
    sounds = new SoundMgr();
}

SceneGame::~SceneGame()
{
    delete ballmgr;
    delete rectUp;
    delete rectDown;
    delete sounds;
    delete font_game_info;
#ifdef DEBUG_MESSAGES_SHOW
    std::cout << "SceneGame end\n";
#endif // DEBUG_MESSAGES_SHOW
}

SDL_AppResult SceneGame::app_iter(AppState *as)
{
    if(!b_paused)
    {
        SDL_SetRenderDrawColor(as->r, 255, 255, 255, 255);
        SDL_RenderClear(as->r);
        SDL_SetRenderDrawColor(as->r, 255, 0, 0, 255);

        // Просчитываем столкновения
        if(ballmgr->checkCollisionWithRect(rectUp))
        {
            score++;
            sounds->playSound(SoundMgr::tcPing);
        }

        if(ballmgr->checkCollisionWithRect(rectDown))
        {
            score++;
            sounds->playSound(SoundMgr::tcPong);
        }

        // Очищаем экран от текущих объектов
        render_clean(as->r);

        // Рисуем новые
        rectUp->draw(as->r);
        rectDown->draw(as->r);

        ballmgr->draw(as->r);
        switch (ballmgr->checkCollisionWithScreen())
        {
            case leftRight:
                sounds->playSound(SoundMgr::tcKnock);
                break;
            case topBottom:
                sounds->playSound(SoundMgr::tcCrash);
                // Формируем статистику игры
                if(score > best)
                    best = score;
                score = 0;
                ballmgr->reinit();
                break;
            default:
                break;
        }

        // Выводим текст
        std::string s_game_info = "SCORE: " + std::to_string(score) + "  BEST: " + std::to_string(best);
        font_game_info->paintText(as->r, s_game_info, SCREEN_HEIGHT - 30, 30, fontAlign::right);

        SDL_RenderPresent(as->r);

        SDL_Delay(delay_time);
    }

    return SDL_APP_CONTINUE;
}

void SceneGame::render_clean(SDL_Renderer *r)
{
    // Стираем текущие объекты сцены
    rectUp->draw(r, true);
    rectDown->draw(r, true);
    ballmgr->draw(r, true);
}

gameReaction SceneGame::process_mouse_motion(float x, float y)
{
    if(!b_paused)
    {
        // Управляем движением ракеток
        // Чтобы ракетка не ушла за экран
        if( x + rect_w/2 > SCREEN_WIDTH)
            x = SCREEN_WIDTH - rect_w/2;

        rectUp->setBeginXY(x - rect_w/2, 0);
        rectDown->setBeginXY(x - rect_w/2, SCREEN_HEIGHT - rect_h);
    }

    return gameReaction::gr_ignore;
}

gameReaction SceneGame::process_mouse_button_event(SDL_MouseButtonEvent m_btn_event)
{
    return gameReaction::gr_ignore;
}

gameReaction SceneGame::process_keyboard_keydown(SDL_Scancode scancode)
{
    if(!b_paused)
    {
        if(scancode == SDL_SCANCODE_LEFT)
            ballmgr->flipVertically();
        if(scancode == SDL_SCANCODE_UP)
            ballmgr->flipHorizontally();
    }

    return gameReaction::gr_ignore;
}
