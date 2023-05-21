#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// example:
// split_string("GET / HTTP/1.1\nHost: localhost:5000\n\n", '\n', &num_lines);
// the &num_lines returns the length of the array
char** split_string(const char* str, char delimiter, int* num_tokens) {
    // Count the number of occurrences of the delimiter in the string
    int delimiter_count = 0;
    const char* p = str;
    while (*p != '\0') {
        if (*p == delimiter)
            delimiter_count++;
        p++;
    }
    
    // Allocate memory for the result array
    char** tokens = (char**)malloc((delimiter_count + 1) * sizeof(char*));
    
    // Copy the string and split it into tokens
    char* copy = strdup(str);  // Make a copy of the original string
    char* token = strtok(copy, &delimiter);
    int i = 0;
    while (token != NULL) {
        tokens[i] = strdup(token);
        token = strtok(NULL, &delimiter);
        i++;
    }
    tokens[i] = NULL;  // Set the last element to NULL for easy iteration
    
    *num_tokens = delimiter_count + 1;  // Set the number of tokens
    
    free(copy);  // Free the copy of the string
    
    return tokens;
}

void print_ascii_string(const char* string) {
    // Iterate over each character in the string
    for (int i = 0; string[i] != '\0'; i++) {
        // Get the ASCII code for the character
        int ascii_code = (int) string[i];
        // Print the character and its ASCII code
        printf("Character: %c\tASCII Code: %d\n", string[i], ascii_code);
    }
}

int index_of(char* string, char character) {
    int index = -1;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == character) {
            index = i;
            break;
        }
    }
    return index;
}
