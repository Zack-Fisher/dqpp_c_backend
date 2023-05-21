#include "parsing.h"

#include "string.h"
#include <stdlib.h>
#include <stdio.h>

#include "helpers.h"

// the first line of the request is the request line, it's special.
// by the HTTP spec, it always has the method, route and protocol version.

// Check if the line is empty, indicating the end of headers
// there's a gap between the request line and the headers, to make it easier to parse
// the MIME type, then the MIME type specified data after the \n gap.

/* example:
    GET / HTTP/1.1
    Host: localhost:8080
    User-Agent: curl/7.64.1
    Content-Type: application/json

    {"name": "John", "age": 30} 
*/

char* newline = "\n\0";

// just processes a single line of the header, and modifies the request struct accordingly.
void process_header(Request* request, char* header) {
    int first_colon_index = index_of(header, ':');

    char* key = (char*)calloc(strlen(header) + 1, 1);
    char* value = (char*)calloc(strlen(header) + 1, 1);

    if (first_colon_index == -1) {
        printf("Invalid header, no colon: %s\n", header);
        return;
    }

    memcpy(key, header, first_colon_index);
    strcpy(value, header + first_colon_index + 2);

    printf("Header: %s\n", header);
    printf("Key: %s\n", key);
    printf("Value: %s\n", value);

    if (strcmp(key, "Content-Type") == 0) {
        request->mime_type = value;
    } else {
        free(value);
    }

    free(key);
}

Request* parse_headers(char* raw_request) {
    printf("Parsing request: %s\n", raw_request);

    Request* request = malloc(sizeof(Request));

    // Split the request on '\n' to extract headers
    char *line;
    char *saveptr;
    
    int header_len;
    char** request_lines = split_string(raw_request, '\n', &header_len);
// just to be safe.
    // zero init it so that we can strlen the body properly.
    request->body = calloc(strlen(raw_request) + 1, 1);
    int body_offset = 0;

    bool processing_headers = true;
    for (int i = 0; i < header_len; i++) {

        line = request_lines[i];
        if (line == NULL) {
            break;
        }

        if (i == 0)
        {
            printf("Request Line: %s\n", line);

            int line_length = strlen(line);
            request->request_line = (char*)malloc((line_length + 1) * sizeof(char));
            strcpy(request->request_line, line);

            // Extract the method and url from the request line
            char* method = strtok_r(line, " ", &saveptr);
            char* url = strtok_r(NULL, " ", &saveptr);

            // Copy the method and url to the request struct
            int method_length = strlen(method);
            request->method = (char*)malloc((method_length + 1) * sizeof(char));
            strcpy(request->method, method);

            int url_length = strlen(url);
            request->url = (char*)malloc((url_length + 1) * sizeof(char));
            strcpy(request->url, url);

            continue;
        }

        if (processing_headers) {
            // it's just a single carriage return, indicating the end of the headers.
            if (strncmp(line, "\r", 1) == 0) {
                printf("End of Headers\n");
                processing_headers = false;
                continue;
            }
            
            process_header(request, line);
            continue;
        }

        // process the body lines
        if (strncmp(line, "\r", 1) != 0) {
            // Process the body, add it to the request struct body field
            printf("Body: %s\n", line);
            strcpy(request->body + body_offset, line);
            body_offset = strlen(request->body);
            strcat(request->body, newline);
        }
    }
    
    return request;
}

cJSON* parse_json(char* json) {
    if (json == NULL) {
        return NULL;
    }

    cJSON* parsed = cJSON_Parse(json);
    if (parsed == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
    }
    return parsed;
}

void free_request(Request* request) {
    free(request->request_line);
    free(request->method);
    free(request->url);
    free(request->body);
    free(request);
}
