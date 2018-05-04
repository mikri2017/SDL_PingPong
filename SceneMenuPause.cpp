#include "SceneMenuPause.h"
#include <iostream>

SceneMenuPause::SceneMenuPause()
{
    delay_time = 50;

    menuPosition.x = 120;
    menuPosition.y = 100;
    btn_w = 400;
    btn_h = 70;

    // Фон меню паузы
    rect_backgrnd.x = 0;
    rect_backgrnd.y = 0;
    rect_backgrnd.w = SCREEN_WIDTH;
    rect_backgrnd.h = SCREEN_HEIGHT;

    // Задаем параметры кнопок
    btn_continue = new Button();
    btn_continue->setCaption("CONTINUE GAME");
    btn_continue->setPosition(menuPosition.x, menuPosition.y);
    btn_continue->setSize(btn_w, btn_h);

    btn_main_menu = new Button();
    btn_main_menu->setCaption("MAIN MENU");
    btn_main_menu->setPosition(menuPosition.x, menuPosition.y + btn_h + 30);
    btn_main_menu->setSize(btn_w, btn_h);

    btn_exit = new Button();
    btn_exit->setCaption("EXIT");
    btn_exit->setPosition(menuPosition.x, menuPosition.y + 2 * btn_h + 60);
    btn_exit->setSize(btn_w, btn_h);
}

SceneMenuPause::~SceneMenuPause()
{
    delete btn_continue;
    delete btn_main_menu;
    delete btn_exit;
#ifdef DEBUG_MESSAGES_SHOW
    std::cout << "SceneMenuPause end\n";
#endif // DEBUG_MESSAGES_SHOW
}

void SceneMenuPause::render(SDL_Renderer *renderer)
{
    if(b_first_render)
    {
        setFirstRenderState(false);

        // Включаем поддержку прозрачности
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        // Выставляем цвет с прозрачностью
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 190 );
        // Заливаем весь экран
        SDL_RenderFillRect(renderer, &rect_backgrnd);
        // Возвращаем основной цвет рисовки
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    }

    btn_continue->draw(renderer);
    btn_main_menu->draw(renderer);
    btn_exit->draw(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(delay_time);
}

gameReaction SceneMenuPause::process_mouse_motion(Sint32 x, Sint32 y)
{
    return gameReaction::gr_ignore;
}

gameReaction SceneMenuPause::process_mouse_button_event(SDL_MouseButtonEvent m_btn_event)
{
    // Клик левой кнопкой мышки
    if(m_btn_event.button == SDL_BUTTON_LEFT)
    {
        // Один клик
        if(m_btn_event.clicks == 1)
        {
            if(btn_exit->checkHover(m_btn_event.x, m_btn_event.y))
            {
                // Выходим из игры
                return gameReaction::gr_exit;
            }

            if(btn_main_menu->checkHover(m_btn_event.x, m_btn_event.y))
            {
                // Выходим в главное меню
                return gameReaction::gr_main_menu;
            }

            if(btn_continue->checkHover(m_btn_event.x, m_btn_event.y))
            {
                // Возвращаемся в игру
                return gameReaction::gr_continue;
            }
        }
    }

    return gameReaction::gr_ignore;
}

gameReaction SceneMenuPause::process_keyboard_keydown(SDL_Keycode keycode)
{
    return gameReaction::gr_ignore;
}
