#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <panel.h>
#include <menu.h>
#include "screen.h"
#include "menu.h"

screenStruct *init_menu_screen(int max_height, int max_width, int window_y, int window_x)
{
    // Draw menu window
    screenStruct *menu_screen = (screenStruct *) malloc(sizeof(screenStruct));

    WINDOW *menu_win = newwin(max_height - 6, max_width - 4, window_y + 1, window_x + 3);
    WINDOW *menu_border = newwin(max_height - 4, max_width, window_y, window_x + 1);
    box(menu_border, 0, 0);
    PANEL *menu_panel = new_panel(menu_win);

    menu_screen->win = menu_win;
    menu_screen->box = menu_border;
    menu_screen->pan = menu_panel;
    mvwprintw(menu_screen->box, 0, 0, "Menu");

    mvwprintw(menu_screen->win, 0, 0, "- You are ($).");
    mvwprintw(menu_screen->win, 1, 0, "- Press (s) for stats (not yet implemented).");
    mvwprintw(menu_screen->win, 2, 0, "- Press (g) to close menu.");
    mvwprintw(menu_screen->win, 3, 0, "- Press (q) to exit.");
    wnoutrefresh(menu_screen->box);
    update_panels();

    return menu_screen;
}
