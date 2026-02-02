#pragma once

#include "DebugParams.h"
#include <string>
#include <SDL3/SDL.h>
#include "SceneMgr.h"

class SDLGame
{
private:
	// Менеджер сцен
	SceneMgr* s_mgr {nullptr};

    // Текст с последней ошибкой
    std::string error_msg;
public:
	SDLGame();

	~SDLGame();

	std::string get_error_msg();

	SDL_AppResult app_event(void* appstate, SDL_Event* event);

	SDL_AppResult app_iter(void* appstate);

	void app_quite(void* appstate, SDL_AppResult result);
};
