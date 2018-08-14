#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char name[16];
    int vitality;
    int power;
    int mana;
} playerStruct;

playerStruct *init_player(char *name, int vitality, int power, int mana);

void player_stats(playerStruct *player);

#endif
