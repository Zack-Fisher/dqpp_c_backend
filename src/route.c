#include <string.h>
#include <unistd.h>

#include "routes/routes.h"
#include "route_helpers.h"

char* handle_routing(Client* client, Request* request) {
    // things are already exposed by default from the request.
    char* method = request->method;
    char* url = request->url;

    char *response;
    switch (method[0]) {
        // GET
        case 'G':
            if (strcmp(url, "/") == 0) {
                response = root_route(client, url);
            } else if (strcmp(url, "/infopage") == 0) {
                response = html_response("infopage.html");
            } else {
                response = html_response("not_found.html");
            }
            break;
        // POST
        case 'P':
            if (strcmp(url, "/battle/attack") == 0) {
                response = battle_attack_route(client, request);
            } else if (strcmp(url, "/battle/run") == 0) {
                response = battle_run_route(client, request);
            } else if (strcmp(url, "/battle/spell") == 0) {
                response = battle_spell_route(client, request);
            } else if (strcmp(url, "/debug/kill") == 0) {
                // kill the server
                #ifdef DEBUG
                    response = http_response(HTTP_OK, CONTENT_TYPE_PLAIN, "Killing server");
                    exit(0);
                #else
                    response = http_response(HTTP_OK, CONTENT_TYPE_PLAIN, "Nice try");
                #endif
            } else {
                response = http_response(HTTP_NOT_FOUND, CONTENT_TYPE_PLAIN, "Not found");
            }
            break;
        default:
            response = http_response(HTTP_NOT_FOUND, CONTENT_TYPE_PLAIN, "Not found, bad method.");
    }
    return response;
}
