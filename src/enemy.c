#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "enemy.h"

enemyStruct *init_enemy(char *name, int vitality, int power, int mana)
{
    // should roll for stats
    if (name == NULL)
        return NULL;

    enemyStruct *enemy = (enemyStruct *) malloc(sizeof(enemyStruct));
    strcpy(enemy->name, name);

    enemy->vitality = vitality;
    enemy->power = power;
    enemy->mana = mana;

    return enemy;
}

void enemy_stats(enemyStruct *enemy)
{
    if (enemy == NULL)
        return;

    printf("name: %s", enemy->name);
    printf("vitality: %d\n", enemy->vitality);
    printf("power: %d\n", enemy->power);
    printf("mana: %d\n", enemy->mana);

    return;
}

enumyStruct *dragon = init_enemy("dragon", 100, 100, 100);

enemyStruct *slime = init_enemy("slime", 50, 50, 0);

enemyStruct *knight = init_enemy("knight", 75, 75, 0);

