#pragma once

#include "types.h"

char* root_route(Client* client, char* url);

char* battle_attack_route(Client* client, Request* r);
char* battle_spell_route(Client* client, Request* r);
char* battle_run_route(Client* client, Request* r);
