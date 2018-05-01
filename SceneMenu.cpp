#include "SceneMenu.h"

void SceneMenu::render(SDL_Renderer *renderer)
{
    if(first_render)
    {
        first_render = false;

        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    }
}

void SceneMenu::process_mouse_motion(Sint32 x, Sint32 y)
{

}

void SceneMenu::process_keyboard_keydown(SDL_Keycode keycode)
{

}
