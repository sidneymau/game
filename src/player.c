#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

playerStruct *init_player(char *name, int vitality, int power, int mana)
{
    // should roll for stats
    if (name == NULL)
        return NULL;

    playerStruct *player = (playerStruct *) malloc(sizeof(playerStruct));
    strcpy(player->name, name);

    player->vitality = vitality;
    player->power = power;
    player->mana = mana;

    return player;
}

void player_stats(playerStruct *player)
{
    if (player == NULL)
        return;

    printf("name: %s", player->name);
    printf("vitality: %d\n", player->vitality);
    printf("power: %d\n", player->power);
    printf("mana: %d\n", player->mana);

    return;
}
