#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include "map.h"

void print_dot(WINDOW *window)
{
    int x_min = 0, y_min = 0;
    int x_max = 0, y_max = 0;
    getmaxyx(window, y_max, x_max);

    char grid[x_max][y_max];
    int i = 0, j = 0, row = x_max, col = y_max;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            grid[i][j] = '.';
            wprintw(window, "%c", grid[i][j]);
        }
        printf("\n");
    }

    return;
}
