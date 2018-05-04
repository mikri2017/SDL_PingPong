#include "SDL_Game.h"
#include <SDL2/SDL_mixer.h>

SDL_Game::SDL_Game()
{
    SDL_error_msg = "";
    window = NULL;
	renderer = NULL;
}

SDL_Game::~SDL_Game()
{
    delete s_mgr;
    SDL_DestroyWindow( window ); // Уничтожаем окно
    TTF_Quit(); // Отключаем библиотеку SDL_ttf
    Mix_CloseAudio(); // Закрываем аудио
    SDL_Quit(); //Выход из SDL
    std::cout << "SDL_Game end\n";
}

bool SDL_Game::init(const char* title, int xpos, int ypos,
              int height, int width, int flags)
{
    // Инициализация SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_error_msg = "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError());
        return false;

    }
	else
	{
	    // Создаем окно
		window = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
		if( window == NULL )
        {
            SDL_error_msg = "Window could not be created! SDL_Error: " + std::string(SDL_GetError());
            return false;
        }
        else
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

        if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
        {
            SDL_error_msg = "Audio mixer not initialized " + std::string(SDL_GetError());
            return false;
        }
	}

	s_mgr = new SceneMgr();

	return true;
}

int SDL_Game::process_events()
{
    SDL_Event event;
    gameReaction gr = gameReaction::gr_ignore;
    int ret = 1;

    while ( SDL_PollEvent(&event) >= 1)
    {
        switch(event.type)
        {
        case SDL_KEYDOWN: // Нажали клавишу на клавиатуре
            gr = s_mgr->process_keyboard_keydown(event.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION: // Движение мышкой
            gr = s_mgr->process_mouse_motion(event.motion.x, event.motion.y);
            break;
        case SDL_MOUSEBUTTONDOWN: // Клик мышкой
            gr = s_mgr->process_mouse_button_event(event.button);
            break;
        case SDL_QUIT: // Закрыли окно
            gr = gameReaction::gr_exit;
            break;
        default:
            break;
        }

        // Выходим из игры
        if(gr == gameReaction::gr_exit)
            ret = 0;
    }
    return ret;
}

void SDL_Game::render()
{
    s_mgr->render(renderer);
}

std::string SDL_Game::getErrorMsg()
{
    return SDL_error_msg;
}
