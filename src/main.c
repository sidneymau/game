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
    //printf("Welcome to game.\n");

    //printf("Name?\n");
    //printf("> ");
    //char name[16];
    //fgets(name, 16, stdin);

    //playerStruct *player = create_player(name);
    //player_stats(player);

    // initialize ncurses screen
    init_screen();
    draw_borders(stdscr);
    //mvprintw(0, 0, "screen");

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
    int game_x_min = 0, game_y_min = 0;
    int game_x_max, game_y_max;
    getmaxyx(game_win, game_y_max, game_x_max);

    // Draw status panel
    WINDOW *status_win = create_newwin(6, max_width, window_y + max_height - 4, window_x + 1);
    draw_borders(status_win);
    PANEL *status_panel = new_panel(status_win);

    // Update panels
    update_panels();

    // Push to screen
    doupdate();

    // Game messages
    //mvwprintw(game_win, 0, 0, "game");
    wnoutrefresh(game_win);

    // Status messages
    mvwprintw(status_win, 0, 0, "Status");
    mvwprintw(status_win, 1, 2, "You are ($).");
    mvwprintw(status_win, 2, 2, "Press (m) for the menu (not yet implemented).");
    mvwprintw(status_win, 3, 2, "Press (q) to exit.");
    wnoutrefresh(status_win);

    // Update
    doupdate();

    int x = 0, y = 0;
    int ch = 0;
    int t = 0;
    while(1) {
        wclear(game_win); // Clear the screen of all previously-printed characters
        mvwprintw(game_win, y, x, "$"); // Print player at (x, y)
        wnoutrefresh(game_win);
        update_panels();
        doupdate();

        ch = getch();
        if (ch == 'q')
            break;
        else if (ch == KEY_RIGHT) {
            if (x < game_x_max - 1)
                x++;
        }
        else if (ch == KEY_LEFT) {
            if (x > game_x_min)
                x--;
        }
        else if (ch == KEY_UP) {
            if (y > game_y_min)
                y--;
        }
        else if (ch == KEY_DOWN) {
            if (y < game_y_max - 1)
                y++;
        }

        t++;
    }

    del_panel(game_panel);
    delwin(game_win);
    del_panel(status_panel);
    delwin(status_win);
    clear();
    //mvprintw(0, 0, "Press any key to quit.\n");
    //getch();
    endwin(); // return to normal terminal

    printf("Exiting game.\n");

    return 1;
}
