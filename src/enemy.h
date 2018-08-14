#ifndef ENEMY_H
#define ENEMY_H

typedef struct {
    char name[16];
    int vitality;
    int power;
    int mana;
} enemyStruct;

enemyStruct *init_enemy(char *name, int vitality, int power, int mana);

void enemy_stats(enemyStruct *enemy);

#endif
