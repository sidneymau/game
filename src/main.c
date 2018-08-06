#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

int main() {
    printf("Welcome to game.\n");

    printf("Name?\n");
    printf("> ");
    char name[16];
    fgets(name, 16, stdin);
    printf("\n");

    playerStruct *player = create_player(name);
    playerStats(player);

    printf("Exiting game.\n");

    return 1;
}
