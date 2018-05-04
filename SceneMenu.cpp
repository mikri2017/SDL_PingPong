#include "SceneMenu.h"

SceneMenu::SceneMenu()
{
    std::cout << "SceneMenu created\n";
    delay_time = 50;

    menuPosition.x = 120;
    menuPosition.y = 70;
    chkbx_side_len = 50;
    btn_w = 400;
    btn_h = 70;

    // Задаем параметры кнопок
    btn_new_game = new Button();
    btn_new_game->setCaption("NEW GAME");
    btn_new_game->setPosition(menuPosition.x, menuPosition.y);
    btn_new_game->setSize(btn_w, btn_h);

    chkbx_mikri = new CheckBox();
    chkbx_mikri->setCaption("MIKRI version");
    chkbx_mikri->setPosition(menuPosition.x, menuPosition.y + btn_h + 30);
    chkbx_mikri->setSize(chkbx_side_len);
    chkbx_mikri->setCheckState(true);

    chkbx_nzemekis = new CheckBox();
    chkbx_nzemekis->setCaption("nZemekis version");
    chkbx_nzemekis->setPosition(menuPosition.x, menuPosition.y + 2 * btn_h + 40);
    chkbx_nzemekis->setSize(chkbx_side_len);

    btn_exit = new Button();
    btn_exit->setCaption("EXIT");
    btn_exit->setPosition(menuPosition.x, menuPosition.y + 3 * btn_h + 50);
    btn_exit->setSize(btn_w, btn_h);
}

SceneMenu::~SceneMenu()
{
    delete btn_new_game;
    delete chkbx_mikri;
    delete chkbx_nzemekis;
    delete btn_exit;
    std::cout << "SceneMenu end\n";
}

void SceneMenu::render(SDL_Renderer *renderer)
{
    if(b_first_render)
    {
        setFirstRenderState(false);

        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    }

    btn_new_game->draw(renderer);
    chkbx_mikri->draw(renderer);
    chkbx_nzemekis->draw(renderer);
    btn_exit->draw(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(delay_time);
}

gameReaction SceneMenu::process_mouse_motion(Sint32 x, Sint32 y)
{
    return gameReaction::gr_ignore;
}

gameReaction SceneMenu::process_mouse_button_event(SDL_MouseButtonEvent m_btn_event)
{
    // Клик левой кнопкой мышки
    if(m_btn_event.button == SDL_BUTTON_LEFT)
    {
        // Один клик
        if(m_btn_event.clicks == 1)
        {
            if(chkbx_mikri->checkHover(m_btn_event.x, m_btn_event.y))
            {
                chkbx_mikri->setCheckState(true);
                chkbx_nzemekis->setCheckState(false);
            }

            if(chkbx_nzemekis->checkHover(m_btn_event.x, m_btn_event.y))
            {
                chkbx_nzemekis->setCheckState(true);
                chkbx_mikri->setCheckState(false);
            }

            if(btn_exit->checkHover(m_btn_event.x, m_btn_event.y))
            {
                // Выходим из игры
                return gameReaction::gr_exit;
            }

            if(btn_new_game->checkHover(m_btn_event.x, m_btn_event.y))
            {
                // Начинаем новую игру
                if(chkbx_mikri->getCheckState())
                    return gameReaction::gr_start_new_mikri;
                else return gameReaction::gr_start_new_zemekis;
            }
        }
    }

    return gameReaction::gr_ignore;
}

gameReaction SceneMenu::process_keyboard_keydown(SDL_Keycode keycode)
{
    return gameReaction::gr_ignore;
}
