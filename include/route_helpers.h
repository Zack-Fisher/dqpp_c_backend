#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "parsing.h"

#include "main.h"

// gives us return codes
#include "http_defines.h"

#define BAD_REQUEST(reason) http_response(HTTP_BAD_REQUEST, CONTENT_TYPE_PLAIN, "Bad request:\n " #reason "\n")

char* http_response(const char* http_status, const char* content_type, const char* body);
char* load_html_from_file(char* filename);
char* html_response(char* filename);
char* text_response(char* text);
