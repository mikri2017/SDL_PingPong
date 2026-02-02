#define SDL_MAIN_USE_CALLBACKS 1  // Использовать обратные вызовы, вместо main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include "MainConstants.h"
#include "SDLGame.h"

static SDLGame* game {nullptr};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    std::string app_title { "SDL PingPong by MIKRI and nZemekis" };
    app_title += "(Press Esc for Exit)";

    SDL_SetAppMetadata(app_title.c_str(), "0.8", "com.mikri.GAMES");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!MIX_Init()) {
        SDL_Log("Couldn't initialize MIX: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState *as = new AppState();
    if (!SDL_CreateWindowAndRenderer(app_title.c_str(), as->win_w, as->win_h, 0, &(as->win), &(as->r))) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    *appstate = as;

    // Создаем объект игры
    game = new SDLGame();

    // Продолжим выполнение программы
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // завершение программы, сообщение ОС об успехе
    }

    return game->app_event(appstate, event);
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    return game->app_iter(appstate);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    // Закрываем аудио
    MIX_Quit();

    // Убираем объект игры
    delete game;

    // SDL освободит окно, рендер для нас
}
