#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
//#include <menu.h>
#include "player.h"
//#include "screen.h"

int main()
{
    printf("Welcome to game.\n");

    printf("Name?\n");
    printf("> ");
    char name[16];
    fgets(name, 16, stdin);

    playerStruct *player = create_player(name);
    player_stats(player);

    // draw screen
    initscr(); // initialize curses library
    keypad(stdscr, TRUE); // enable keyboard
    raw(); // instead of cbreak
    noecho(); // don't echo input
    curs_set(FALSE);

    // set up initial windows
    int x_min = 0, y_min = 0;
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);

    int x = 0, y = 0;
    int ch = 0;
    int t = 0;
    while(t < 100) {
        clear(); // Clear the screen of all previously-printed characters
        mvprintw(y, x, "o"); // Print our "ball" at the current xy position
        refresh();

        ch = getch();
        if (ch == KEY_RIGHT) {
            if (x < x_max)
                x++;
        }
        else if (ch == KEY_LEFT) {
            if (x > x_min)
                x--;
        }
        else if (ch == KEY_UP) {
            if (y > y_min)
                y--;
        }
        else if (ch == KEY_DOWN) {
            if (y < y_max)
                y++;
        }

        t++;
        
    }

    endwin(); // return to normal terminal

    printf("Exiting game.\n");

    return 1;
}
