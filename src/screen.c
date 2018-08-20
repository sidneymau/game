#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
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
