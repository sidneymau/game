#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char name[16];
    int health;
    int mana;
} playerStruct;

playerStruct *create_player(char *name);

void playerStats(playerStruct *player);

#endif
