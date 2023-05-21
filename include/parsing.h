#pragma once

#include "types.h"
#include <cjson/cJSON.h>

Request* parse_headers(char* request);
// most bodies in this API are json. we'll use cjson.
cJSON* parse_json(char* json);
void free_request(Request* request);
