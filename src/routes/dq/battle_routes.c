#include "route_helpers.h"

char* battle_attack_route(Client* client, Request* r)
{
}

char* battle_spell_route(Client* client, Request* r)
{
    printf("SPELL REQUEST BODY: %s", r->body);

    cJSON* j = parse_json(r->body);
    if (j == NULL) {
        return BAD_REQUEST("json parse error");
    }

    cJSON* spell = cJSON_GetObjectItem(j, "spell");
    if (spell == NULL) {
        return BAD_REQUEST("spell not found");
    }

    printf("Spell: %s\n", spell->valuestring);
}

char* battle_run_route(Client* client, Request* r)
{
}
