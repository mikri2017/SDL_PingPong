#ifndef MAINCONSTANTS_H_INCLUDED
#define MAINCONSTANTS_H_INCLUDED

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
constexpr double PI_by_180 = 3.14159265 / 180;
const int RectStepByKeyboard = 50;

enum gameReaction {
    gr_ignore,
    gr_start_new_mikri,
    gr_start_new_zemekis,
    gr_continue,
    gr_pause,
    gr_main_menu,
    gr_exit
};

#endif // MAINCONSTANTS_H_INCLUDED
