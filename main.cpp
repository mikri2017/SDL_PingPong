/*
    Рыжков Михаил, Пинг-Понг на SDL
 */

#include <iostream>
#include "SDL_Game.h"

int main( int argc, char* args[] )
{
    SDL_Game *game = new SDL_Game();
    if(!game->init("SDL PingPong by MIKRI and nZemekis (Press Esc for Exit)", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN))
    {
        std::cout << game->getErrorMsg() << std::endl;
        return 1;
    }

    std::cout << "Press Esc button to Exit!\n";

    while(game->process_events())
    {
        game->render();
    }

	delete game;

	return 0;
}
