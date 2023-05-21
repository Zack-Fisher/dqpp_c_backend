#include "panic.h"

#include <stdio.h>
#include <stdlib.h>

void panic(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}
