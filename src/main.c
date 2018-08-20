#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <panel.h>
//#include <menu.h>
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "combat.h"
#include "screen.h"
//#include "map.h"

int main()
{
    printf("Welcome to game.\n");

    printf("Name?\n");
    printf("> ");
    char name[16];
    fgets(name, 16, stdin);

    playerStruct *player = init_player(name, 100, 100, 100);
    player_stats(player);

    // initialize ncurses screen
    init_screen();
    box(stdscr, 0, 0);
    mvprintw(0, 0, "Screen");

    // set up initial windows
    //int x_min = 0, y_min = 0;
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);

    int max_width = x_max - 4;
    int max_height = y_max - 4;
    int window_width = max_width + 2;
	int window_height = max_height + 2;
	int window_x = x_max / 2 - window_width / 2;
    int window_y = y_max / 2 - window_height / 2;

    // Draw game window
    WINDOW *game_border = newwin(max_height - 4, max_width, window_y, window_x + 1);
    box(game_border, 0, 0);
    WINDOW *game_win = newwin(max_height - 6, max_width - 4, window_y + 1, window_x + 3);
    PANEL *game_panel = new_panel(game_win);
    int game_x_min = 0, game_y_min = 0;
    int game_x_max, game_y_max;
    getmaxyx(game_win, game_y_max, game_x_max);
    game_x_min+=0;
    game_y_min+=0;
    game_x_max-=1;
    game_y_max-=1;

    // Draw status window
    WINDOW *status_border = newwin(6, max_width, window_y + max_height - 4, window_x + 1);
    box(status_border, 0, 0);
    WINDOW *status_win = newwin(4, max_width - 3, window_y + max_height - 3, window_x + 3);
    PANEL *status_panel = new_panel(status_win);

    // Game messages
    mvwprintw(game_border, 0, 0, "Game");

    // Status messages
    mvwprintw(status_border, 0, 0, "Status");
    mvwprintw(status_win, 0, 0, "- You are ($).");
    mvwprintw(status_win, 1, 0, "- Press (m) for menu (not yet implemented).");
    mvwprintw(status_win, 2, 0, "- Press (q) to exit.");

    // Update
    wnoutrefresh(stdscr);
    wnoutrefresh(game_border);
    wnoutrefresh(status_border);
    update_panels();
    doupdate();

    int x = game_x_min, y = game_y_min;
    int ch = 0;
    int t = 0;
    int dice = 0;
    int alive = 1;
    while(1) {
        wclear(game_win);
        wclear(status_win);
        mvwprintw(game_win, y, x, "$");
        mvwprintw(status_win, 0, 0, "- You are ($).");
        //mvwprintw(status_win, 1, 0, "- Press (m) for menu (not yet implemented).");
        mvwprintw(status_win, 1, 0, "- Press (q) to exit.");
        mvwprintw(status_win, 2, 0, "You are at x=%d, y=%d, t=%d.", x, y, t);
        update_panels();
        doupdate();

        ch = getch();
        if (ch == 'q') {
            break;
        }
        else if ((ch == KEY_RIGHT) || (ch == 'd')) {
            if (x < game_x_max)
                x++;
        }
        else if ((ch == KEY_LEFT) || (ch == 'a')) {
            if (x > game_x_min)
                x--;
        }
        else if ((ch == KEY_UP) || (ch == 'w')) {
            if (y > game_y_min)
                y--;
        }
        else if ((ch == KEY_DOWN) || (ch == 's')) {
            if (y < game_y_max)
                y++;
        }

        wclear(status_win);
        dice = roll(20);
        mvwprintw(status_win, 1, 0, "You rolled %d.", dice);
        update_panels();
        doupdate();
        sleep(1);
        if (dice > 15) {
            enemyStruct *enemy = init_enemy("enemy", 10, 10, 10);
            combatantStruct *combatants = init_combat(player, enemy);
            mvwprintw(status_win, 2, 0, "You are in combat with %s.", enemy->name);
            update_panels();
            doupdate();
            sleep(1);
            alive = combat(combatants);
            if (alive == 1) {
                mvwprintw(status_win, 3, 0, "You won against the %s.", enemy->name);
                update_panels();
                doupdate();
                sleep(1);
            }
            else {
                mvwprintw(status_win, 3, 0, "You lost to the %s.", enemy->name);
                update_panels();
                doupdate();
                sleep(1);
                break;
            }
        }
        

        t++;
    }

    del_panel(game_panel);
    delwin(game_win);
    del_panel(status_panel);
    delwin(status_win);
    delwin(game_border);
    delwin(status_border);
    clear();
    //mvprintw(0, 0, "Press any key to quit.\n");
    //getch();
    endwin(); // end ncurses

    printf("Exiting game.\n");

    return 1;
}
