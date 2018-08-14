#ifndef COMBAT_H
#define COMBAT_H

typedef struct {
    playerStruct *player;
    enemyStruct *enemy;
} combatantStruct;

int player_health(playerStruct *player);

int player_attack(playerStruct *player);

int player_armor(playerStruct *player);

int enemy_health(enemyStruct *enemy);

int enemy_attack(enemyStruct *enemy);

int enemy_armor(enemyStruct *enemy);

combatantStruct *init_combat(playerStruct *player, enemyStruct *enemy);

void do_damage(combatantStruct *combatants);

void combat_loop(combatantStruct *combatants);

int combat(combatantStruct *combatants);

#endif
