#ifndef SCREEN_H
#define SCREEN_H

typedef struct {
    WINDOW *win;
    WINDOW *box;
    PANEL *pan;
} screenStruct;


void init_screen();

screenStruct *init_game_screen(int max_height, int max_width, int window_y, int window_x);

screenStruct *init_status_screen(int max_height, int max_width, int window_y, int window_x);

#endif
