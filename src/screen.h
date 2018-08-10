#ifndef SCREEN_H
#define SCREEN_H

void init_screen();

WINDOW *create_newwin(int height, int width, int starty, int startx);

void draw_borders(WINDOW *screen);

#endif
