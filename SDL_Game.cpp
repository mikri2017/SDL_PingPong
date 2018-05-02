#include "SDL_Game.h"
#include <SDL2/SDL_mixer.h>

SDL_Game::SDL_Game()
{
    SDL_error_msg = "";
    window = NULL;
	renderer = NULL;
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
    int ret = 1;

    while ( SDL_PollEvent(&event) >= 1)
    {
        switch(event.type)
        {
        case SDL_KEYDOWN: // Нажали клавишу на клавиатуре
            /*if (event.key.keysym.sym == SDLK_LEFT)
                ScrObjMngr.ChgXBegin(-RectStepByKeyboard);

            if (event.key.keysym.sym == SDLK_RIGHT)
                ScrObjMngr.ChgXBegin(RectStepByKeyboard);
            */
            if (event.key.keysym.sym == SDLK_ESCAPE)
                ret = 0;
            else s_mgr->process_keyboard_keydown(event.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION: // Движение мышкой
            s_mgr->process_mouse_motion(event.motion.x, event.motion.y);
            break;
        case SDL_QUIT: // Закрыли окно
            ret = 0;
            break;
        default:
            break;
        }
    }
    return ret;
}

void SDL_Game::render()
{
    s_mgr->render(renderer);
}

void SDL_Game::clean_and_exit()
{
    SDL_DestroyWindow( window ); // Уничтожаем окно
    TTF_Quit(); // Отключаем библиотеку SDL_ttf
	SDL_Quit(); //Выход из SDL
}

std::string SDL_Game::getErrorMsg()
{
    return SDL_error_msg;
}
