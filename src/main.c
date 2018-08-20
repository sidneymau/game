#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <panel.h>
#include <menu.h>
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "combat.h"
#include "screen.h"
#include "menu.h"
//#include "map.h"

int main()
{
    printf("Welcome to game.\n");

    printf("Name?\n");
    printf("> ");
    char name[16];
    fgets(name, 16, stdin);

    playerStruct *player = init_player(name, 100, 100, 100);

    // initialize ncurses screen
    init_screen();

    int x_max = 0;
    int y_max = 0;
    getmaxyx(stdscr, y_max, x_max);
    
    int max_width = x_max - 4;
    int max_height = y_max - 4;
    int window_width = max_width + 2;
    int window_height = max_height + 2;
    int window_x = x_max / 2 - window_width / 2;
    int window_y = y_max / 2 - window_height / 2;


    // Draw menu window
    screenStruct *menu_screen = init_menu_screen(max_height / 2, max_width / 2, window_y, window_x);

    // Draw game window
    screenStruct *game_screen = init_game_screen(max_height, max_width, window_y, window_x);

    // Draw status window
    screenStruct *status_screen = init_status_screen(max_height, max_width, window_y, window_x);

    // Update
    wnoutrefresh(stdscr);
    wnoutrefresh(game_screen->box);
    wnoutrefresh(status_screen->box);
    update_panels();
    doupdate();

    int game_x_min = 0, game_y_min = 0;
    int game_x_max, game_y_max;
    getmaxyx(game_screen->win, game_y_max, game_x_max);
    game_x_min+=0;
    game_y_min+=0;
    game_x_max-=1;
    game_y_max-=1;

    int x = game_x_min, y = game_y_min;
    int ch = 0;
    int t = 0;
    int dice = 0;
    int alive = 1;
    while(1) {
        wclear(game_screen->win);
        wclear(status_screen->win);
        mvwprintw(game_screen->win, y, x, "$");
        mvwprintw(status_screen->win, 0, 0, "You ($) are at x=%d, y=%d, t=%d.", x, y, t);
        mvwprintw(status_screen->win, 1, 0, "- Press (m) for menu (not implemented).");
        mvwprintw(status_screen->win, 2, 0, "- Press (q) to exit.");
        mvwprintw(status_screen->win, 0, game_x_max / 2, "name: %s", player->name);
        mvwprintw(status_screen->win, 1, game_x_max / 2, "vitality: %d", player->vitality);
        mvwprintw(status_screen->win, 2, game_x_max / 2, "power: %d", player->power);
        mvwprintw(status_screen->win, 3, game_x_max / 2, "mana: %d", player->mana);
        update_panels();
        doupdate();

        ch = getch();
        if (ch == 'q') {
            break;
        }
        /*
        if (ch == 'm') {
            top_panel(menu_screen->pan);
            doupdate();
            getch();
            top_panel(game_screen->pan);
            doupdate();
        }
        */

        if ((ch == KEY_RIGHT) || (ch == 'd')) {
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

        dice = roll(20);
        if (dice > 15) {
            enemyStruct *enemy = init_enemy("enemy", 10, 10, 10);
            combatantStruct *combatants = init_combat(player, enemy);
            wclear(status_screen->win);
            mvwprintw(status_screen->win, 0, 0, "You ecountered %s!", enemy->name);
            update_panels();
            doupdate();
            sleep(1);
            mvwprintw(status_screen->win, 1, 0, "You are in combat with %s.", enemy->name);
            update_panels();
            doupdate();
            sleep(1);
            alive = combat(combatants);
            if (alive == 1) {
                mvwprintw(status_screen->win, 2, 0, "You won against %s.", enemy->name);
                update_panels();
                doupdate();
                sleep(1);
            }
            else {
                mvwprintw(status_screen->win, 2, 0, "You lost to %s.", enemy->name);
                update_panels();
                doupdate();
                sleep(1);
                break;
            }
            free(enemy);
        }

        t++;
    }

    del_panel(game_screen->pan);
    delwin(game_screen->win);
    del_panel(status_screen->pan);
    delwin(status_screen->win);
    delwin(game_screen->box);
    delwin(status_screen->box);
    clear();
    endwin(); // end ncurses
    free(game_screen);
    free(status_screen);
    free(player);

    printf("Exiting game.\n");

    return 1;
}
