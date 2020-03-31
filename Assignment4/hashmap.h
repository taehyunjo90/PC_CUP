#ifndef HASHMAP_H
#define HASHMAP_H

#include "node.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define TRUE (1)
#define FALSE (0)

typedef struct hashmap {
    int (*hash_func)(const char* key);
    node_t** plist;
    size_t length;
} hashmap_t;

hashmap_t* init_hashmap_malloc(size_t length, int (*p_hash_func)(const char* key));

int add_key(hashmap_t* hashmap, const char* key, const int value);

int get_value(hashmap_t* hashmap, const char* key);

int update_value(hashmap_t* hashmap, const char* key, int value);

int remove_key(hashmap_t* hashmap, const char* key);

void destroy(hashmap_t* hashmap);

node_t* make_node(const char* key, const int value);

#endif /* HASHMAP_H */
