#ifndef SDL_GAME_H_INCLUDED
#define SDL_GAME_H_INCLUDED

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_ttf.h>
#include "MainConstants.h"
#include "SceneMgr.h"

class SDL_Game
{
private:
    SDL_Window *window;
	SDL_Renderer *renderer;
	SceneMgr *s_mgr;
	std::string SDL_error_msg;
public:
    SDL_Game();
    ~SDL_Game();
    std::string getErrorMsg();
    bool init(const char* title, int xpos, int ypos,
              int height, int width, int flags);
    int process_events();
    void render();
};

#endif // SDL_GAME_H_INCLUDED
