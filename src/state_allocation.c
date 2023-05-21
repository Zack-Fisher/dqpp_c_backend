#include "gamestate.h"

#include <stdlib.h>

GameState* mk_gamestate() {
    GameState* state = malloc(sizeof(GameState));

    state->current_state = OVERWORLD;

    state->player_state = malloc(sizeof(PlayerState));
    state->player_state->health = 100;
    state->player_state->stats.attack = 10;
    state->player_state->stats.defense = 10;
    state->player_state->stats.gold = 0;
    state->player_state->stats.experience = 0;
    state->player_state->stats.max_health = 100;

    state->battle_state = malloc(sizeof(BattleState));
    state->battle_state->enemy_state.attack = 10;
    state->battle_state->enemy_state.defense = 10;

    return state;
}
