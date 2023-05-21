#ifndef HASHMAP_H
#define HASHMAP_H
// simple definition of a hashmap between char* and bool
// mainly for input mapping

#define HASHMAP_SIZE 50
#define NODE_NAME_MAX_SIZE 64

#include <stdbool.h>
#include <stddef.h>

// so we can have arb types of hashmaps, we need to use the preprocessor macro here.
#define DEFINE_HASHMAP_TYPE(Type) \
\
typedef struct Node_##Type { \
    char* key; \
    Type value; \
    struct Node_##Type* next; \
} Node_##Type; \
\
typedef struct HashMap_##Type { \
    Node_##Type** array; \
} HashMap_##Type; \
\
HashMap_##Type* hashmap_create_##Type(); \
void hashmap_insert_##Type(HashMap_##Type* hashmap, char* key, Type value); \
Type hashmap_get_##Type(HashMap_##Type* hashmap, char* key); \
void hashmap_delete_##Type(HashMap_##Type* hashmap, char* key); \
void hashmap_destroy_##Type(HashMap_##Type* hashmap); \

// hashmap from char* to bool
// doesn't work well with typedef'd types.
// we use the ACTUAL _Bool, not bool, because bool is a macro.
DEFINE_HASHMAP_TYPE(_Bool)

#endif // HASHMAP_H
