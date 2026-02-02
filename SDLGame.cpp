#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "MainConstants.h"
#include "SDLGame.h"

SDLGame::SDLGame()
{
    error_msg = "";

	// Создадим менеджер сцен
	s_mgr = new SceneMgr();
}

SDLGame::~SDLGame()
{
    delete s_mgr;
    TTF_Quit(); // Отключаем библиотеку SDL_ttf
}

std::string SDLGame::get_error_msg()
{
    return error_msg;
}

SDL_AppResult SDLGame::app_event(void* appstate, SDL_Event* event)
{
    gameReaction gr = gameReaction::gr_ignore;

    if (event->type == SDL_EventType::SDL_EVENT_KEY_DOWN)
    {
        // Нажатие клавиши
        gr = s_mgr->process_keyboard_keydown(event->key.scancode);
    }
    else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_MOTION)
    {
        // Движение мышкой
        gr = s_mgr->process_mouse_motion(event->motion.x, event->motion.y);
    }
    else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        // Клик мышкой
        gr = s_mgr->process_mouse_button_event(event->button);
    }
    else if(event->type == SDL_EventType::SDL_EVENT_QUIT)
    {
        // Выход из приложения
        return SDL_APP_SUCCESS;
    }

    if(gr == gameReaction::gr_exit)
        return SDL_APP_SUCCESS;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDLGame::app_iter(void* appstate)
{
    AppState *as = (AppState *) appstate;

    s_mgr->app_iter(as);

    SDL_GetWindowSize(as->win, &(as->win_w), &(as->win_h));

	return SDL_APP_CONTINUE;
}

void SDLGame::app_quite(void* appstate, SDL_AppResult result) {}
