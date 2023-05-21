#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hashmap.h"

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    // assume constant size of the hashing table
    return hash % HASHMAP_SIZE;
}

// dont judge macros are sick
#define DEFINE_HASHMAP_IMPL(Type) \
\
Node_##Type* hashmap_node_##Type() { \
    Node_##Type* node = (Node_##Type*)malloc(sizeof(Node_##Type)); \
    node->key = (char*)calloc(NODE_NAME_MAX_SIZE, sizeof(char)); \
    node->value = (Type)0; \
    node->next = NULL; \
    return node; \
} \
\
HashMap_##Type* hashmap_create_##Type() { \
    HashMap_##Type* hashmap = (HashMap_##Type*)malloc(sizeof(HashMap_##Type)); \
    hashmap->array = (Node_##Type**)calloc(HASHMAP_SIZE, sizeof(Node_##Type*)); \
    for (int i = 0; i < HASHMAP_SIZE; i++) { \
        hashmap->array[i] = hashmap_node_##Type(); \
    } \
    return hashmap; \
} \
\
void hashmap_insert_##Type(HashMap_##Type* hashmap, char* key, Type value) { \
    unsigned long index = hash(key); \
    Node_##Type* node = hashmap_node_##Type(); \
    sprintf(node->key, "%s", key); \
    node->value = value; \
    node->next = hashmap->array[index]; \
    hashmap->array[index] = node; \
} \
\
Type hashmap_get_##Type(HashMap_##Type* hashmap, char* key) { \
    unsigned long index = hash(key); \
    Node_##Type* node = hashmap->array[index]; \
    while(node != NULL) { \
        if(strcmp(node->key, key) == 0) \
            return node->value; \
        node = node->next; \
    } \
    if (#Type == "__ptr_t") \
        return NULL; \
    else \
    { \
        return (Type)0; \
    } \
} \
\
void hashmap_delete_##Type(HashMap_##Type* hashmap, char* key) { \
    unsigned long index = hash(key); \
    Node_##Type* node = hashmap->array[index]; \
    Node_##Type* prev = NULL; \
    while(node != NULL) { \
        if(strcmp(node->key, key) == 0) { \
            if(prev == NULL) \
                hashmap->array[index] = node->next; \
            else \
                prev->next = node->next; \
            free(node->key); \
            free(node); \
            return; \
        } \
        prev = node; \
        node = node->next; \
    } \
} \
\
void hashmap_destroy_##Type(HashMap_##Type* hashmap) { \
    for(unsigned long i = 0; i < HASHMAP_SIZE; i++) { \
        Node_##Type* node = hashmap->array[i]; \
        while(node != NULL) { \
            Node_##Type* next = node->next; \
            free(node->key); \
            free(node); \
            node = next; \
        } \
    } \
    free(hashmap); \
}

DEFINE_HASHMAP_IMPL(_Bool)
