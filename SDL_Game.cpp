#include "SDL_Game.h"

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
	}

	ball = new Ball();
	ball->setCentreXY(100, 100);
    ball->setRadius(50);

    rect = new Rect();
    rect->setBeginXY(200, 200);
    rect->setHeight(50);
    rect->setWidth(100);

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
        case SDL_KEYDOWN:
            /*if (event.key.keysym.sym == SDLK_LEFT)
                ScrObjMngr.ChgXBegin(-RectStepByKeyboard);

            if (event.key.keysym.sym == SDLK_RIGHT)
                ScrObjMngr.ChgXBegin(RectStepByKeyboard);
            */
            if (event.key.keysym.sym == SDLK_ESCAPE)
                ret = 0;
            break;
        case SDL_MOUSEMOTION:
            //ScrObjMngr.ChgXBeginByMouse(event.motion.x);
            break;
        default:
            break;
        }
    }
    return ret;
}

void SDL_Game::render()
{
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    ball->draw(renderer);
    rect->draw(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(50);
}

void SDL_Game::clean_and_exit()
{
    SDL_DestroyWindow( window ); // Уничтожаем окно
	SDL_Quit(); //Выход из SDL
}

std::string SDL_Game::getErrorMsg()
{
    return SDL_error_msg;
}
