#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

playerStruct *create_player(char *name)
{
    if (name == NULL)
        return NULL;

    playerStruct *player = (playerStruct *) malloc(sizeof(playerStruct));
    strcpy(player->name, name);

    player->health = 100;
    player->mana = 0;

    return player;
}

void player_stats(playerStruct *player)
{
    if (player == NULL)
        return;

    printf("name: %s", player->name);
    printf("health: %d\n", player->health);
    printf("mana: %d\n", player->mana);

    return;
}
