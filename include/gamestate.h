#pragma once

#include "hashmap.h"

// things that change with a level-up
typedef struct {
    int defense;
    int attack;
    int gold;
    int experience;
    int max_health;
} PlayerStats;

// things that are constantly fluctuating, vitals.
// also the container for the stats.
typedef struct {
    PlayerStats stats;
    int health;
} PlayerState;

typedef struct {
    int attack;
    int defense;
} EnemyState;

typedef struct {
    EnemyState enemy_state;
} BattleState;

typedef enum {
    OVERWORLD = 1,
    BATTLE = 2,
} StateMachine;

typedef struct {
    // contains the state of either the last or current battle, depending on the state machine position.
    BattleState* battle_state;
    // contains the gameplay mode we're in.
    StateMachine current_state;
    // contains the state of the player.
    PlayerState* player_state;
} GameState;

GameState* mk_gamestate();
