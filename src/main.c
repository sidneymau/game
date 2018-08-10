#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <panel.h>
//#include <menu.h>
#include "player.h"
#include "screen.h"

int main()
{
    printf("Welcome to game.\n");

    printf("Name?\n");
    printf("> ");
    char name[16];
    fgets(name, 16, stdin);

    playerStruct *player = create_player(name);
    player_stats(player);
    sleep(1);

    // initialize ncurses screen
    init_screen();
    draw_borders(stdscr);
    mvprintw(0, 0, "screen");

    // set up initial windows
    int x_min = 0, y_min = 0;
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);

    int max_width = x_max - 4;
    int max_height = y_max - 4;
    int window_width = max_width + 2;
	int window_height = max_height + 2;
	int window_x = x_max / 2 - window_width / 2;
    int window_y = y_max / 2 - window_height / 2;

    // Draw game panel
    WINDOW *game_win = create_newwin(max_height - 4, max_width, window_y, window_x + 1);
    draw_borders(game_win);
    PANEL *game_panel = new_panel(game_win);

    // Draw status panel
    WINDOW *status_win = create_newwin(6, max_width, window_y + max_height - 4, window_x + 1);
    draw_borders(status_win);
    PANEL *status_panel = new_panel(status_win);

    // Update panels
    update_panels();

    // Push to screen
    doupdate();

    mvwprintw(game_win, 0, 0, "game");
    mvwprintw(status_win, 0, 0, "status");
    wrefresh(game_win);
    wrefresh(status_win);
    doupdate();

    int x = 0, y = 0;
    int ch = 0;
    int t = 0;
    while(1) {
        wclear(game_win); // Clear the screen of all previously-printed characters
        mvwprintw(game_win, y, x, "o"); // Print player at (x, y)
        //wrefresh(game_win);
        //update_panels();
        //doupdate();

        ch = getch();
        if (ch == 'q')
            break;
        else if (ch == KEY_RIGHT) {
            if (x < max_width)
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
            if (y < max_height)
                y++;
        }

        t++;
    }

    del_panel(game_panel);
    delwin(game_win);
    del_panel(status_panel);
    delwin(status_win);
    clear();
    mvprintw(window_y, window_x, "Press any key to end.\n");
    getch();
    endwin(); // return to normal terminal

    printf("Exiting game.\n");

    return 1;
}
