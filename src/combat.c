#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "combat.h"

int player_health(playerStruct *player)
{
    if (player == NULL)
        return 0;

    return player->vitality;
}

int player_attack(playerStruct *player)
{
    if (player == NULL)
        return 0;

    return roll(player->power);
}

int player_armor(playerStruct *player)
{
    if (player == NULL)
        return 0;

    return roll(player->vitality);
}

int enemy_health(enemyStruct *enemy)
{
    if (enemy == NULL)
        return 0;

    return enemy->vitality;
}

int enemy_attack(enemyStruct *enemy)
{
    if (enemy == NULL)
        return 0;

    return roll(enemy->power);
}

int enemy_armor(enemyStruct *enemy)
{
    if (enemy == NULL)
        return 0;

    return roll(enemy->vitality);
}

combatantStruct *init_combat(playerStruct *player, enemyStruct *enemy)
{
    if (player == NULL)
        return NULL;
    if (enemy == NULL)
        return NULL;

    combatantStruct *combatants = (combatantStruct *) malloc(sizeof(combatantStruct));
    combatants->player = player;
    combatants->enemy = enemy;

    return combatants;
}

void do_damage(combatantStruct *combatants)
{
    if (combatants == NULL)
        return;

    // rename these local vars
    int p_health = player_health(combatants->player);
    int p_attack = player_attack(combatants->player);
    int p_armor = player_armor(combatants->player);
    int e_health = enemy_health(combatants->enemy);
    int e_attack = enemy_attack(combatants->enemy);
    int e_armor = enemy_armor(combatants->enemy);

    int p_damage, e_damage;
    p_damage = e_attack;
    e_damage = p_attack;
    //p_damage = p_armor - e_attack;
    //if (p_damage > 0)
    //    p_damage = 0;
    //e_damage = e_armor - p_attack;
    //if (e_damage > 0)
    //    e_damage = 0;

    p_health -= p_damage;
    e_health -= e_damage;

    combatants->player->vitality = p_health;
    combatants->enemy->vitality = e_health;

    return;
}

void combat_loop(combatantStruct *combatants)
{
    if (combatants == NULL)
        return;
    
    while ((combatants->player->vitality > 0) && (combatants->enemy->vitality > 0)) {
        do_damage(combatants);
    }

    return;
}

int combat(combatantStruct *combatants)
{
    if (combatants == NULL)
        return 0;
    
    combat_loop(combatants);

    if (combatants->player->vitality > 0)
        return 1;
    else
        return 0;
}
