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

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	//box(local_win, 0 , 0); /* 0, 0 gives default characters 
	//						* for the vertical and horizontal
	//						* lines	*/
	//wrefresh(local_win);   /* Show that box */

	return local_win;
}

void draw_borders(WINDOW *screen)
{
    box(screen, 0, 0);
    wrefresh(screen);
}
