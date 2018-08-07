#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include "screen.h"

// Using ncurses to handle terminal IO

void draw_screen(WINDOW *screen)
{
    int x, y, i;
    getmaxyx(screen, y, x);

    initscr(); // initialize curses library
    keypad(stdscr, TRUE); // enable keyboard mapping
    raw();
    noecho(); // echo input

    return;
}
