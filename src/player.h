#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char name[16];
    int health;
    int mana;
} playerStruct;

playerStruct *init_player(char *name);

void player_stats(playerStruct *player);

#endif
