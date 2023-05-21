// help with generating responses and etc
#include "route_helpers.h"

char* http_response(const char* http_status, const char* content_type, const char* body) {
    char* response = malloc(strlen(http_status) + strlen(content_type) + strlen("Content-Length: ") + strlen(body) + 5);
    sprintf(response, "%s%sContent-Length: %lu\n\n%s", http_status, content_type, strlen(body), body);
    return response;
}

char* load_html_from_file(char* filename)
{
    char buffer[256];

    sprintf(buffer, "%s%s", HTML_PATH, filename);

    FILE* file = fopen(buffer, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", buffer);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* html = malloc(fsize + 1);
    fread(html, 1, fsize, file);
    fclose(file);

    return html;
}

char* html_response(char* filename)
{
    char* response;
    response = http_response(HTTP_OK, CONTENT_TYPE_HTML, load_html_from_file(filename));
    return response;
}

char* text_response(char* text)
{
    char* response;
    response = http_response(HTTP_OK, CONTENT_TYPE_PLAIN, text);
    return response;
}
