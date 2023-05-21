#include "route_helpers.h"

char* root_route(Client* client, char* url)
{
    char *response;
    response = http_response(HTTP_OK, CONTENT_TYPE_PLAIN, "Hello, world!");
    return response;
}
