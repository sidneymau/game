#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <panel.h>
#include "screen.h"

// Using ncurses to handle terminal IO

void init_screen()
{
    initscr(); // initialize curses
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);
}

screenStruct *init_game_screen(int max_height, int max_width, int window_y, int window_x)
{
    // Draw game window
    screenStruct *game_screen = (screenStruct *) malloc(sizeof(screenStruct));

    WINDOW *game_win = newwin(max_height - 6, max_width - 4, window_y + 1, window_x + 3);
    WINDOW *game_border = newwin(max_height - 4, max_width, window_y, window_x + 1);
    box(game_border, 0, 0);
    PANEL *game_panel = new_panel(game_win);

    game_screen->win = game_win;
    game_screen->box = game_border;
    game_screen->pan = game_panel;

    return game_screen;

}

screenStruct *init_status_screen(int max_height, int max_width, int window_y, int window_x)
{
    // Draw status window
    screenStruct *status_screen = (screenStruct *) malloc(sizeof(screenStruct));

    WINDOW *status_win = newwin(4, max_width - 3, window_y + max_height - 3, window_x + 3);
    WINDOW *status_border = newwin(6, max_width, window_y + max_height - 4, window_x + 1);
    box(status_border, 0, 0);
    PANEL *status_panel = new_panel(status_win);

    status_screen->win = status_win;
    status_screen->box = status_border;
    status_screen->pan = status_panel;

    return status_screen;
}
