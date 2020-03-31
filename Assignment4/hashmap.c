#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, int (*p_hash_func)(const char* key))
{
    hashmap_t* hashmap = malloc(sizeof(hashmap_t));
    size_t i;

    hashmap->hash_func = p_hash_func;
    hashmap->length = length;

    hashmap->plist = malloc(sizeof(node_t*) * length);
    
    for (i = 0; i < length; i++) {
        *(hashmap->plist + i) = NULL;
    }

    return hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    int hashed_key;
    int idx;
    node_t* p;
    
    hashed_key = (hashmap->hash_func)(key);
    idx = hashed_key % hashmap->length;

    p = *(hashmap->plist + idx);
    if (p == NULL) {
        *(hashmap->plist + idx) = make_node(key, value);
        return TRUE;
    } else {
        do {
            if (!strcmp(p->key, key)) {
                return FALSE;
            } else {
                if (p->next == NULL) {
                    p->next = make_node(key, value);
                    return TRUE;
                }
                p = p->next;
            }
        } while (TRUE);
    }
}

node_t* make_node(const char* key, const int value)
{
    int key_len = strlen(key);
    node_t* p;

    p = malloc(sizeof(node_t));

    p->key = malloc(sizeof(char) * (key_len + 1));
    strcpy(p->key, key);
    (p->key)[key_len] = '\0';

    p->value = value;

    p->next = NULL;

    return p;
}

int get_value(hashmap_t* hashmap, const char* key)
{
    int hashed_key;
    int idx;
    node_t* p;

    hashed_key = (hashmap->hash_func)(key);
    idx = hashed_key % hashmap->length;

    p = *(hashmap->plist + idx);

    while (TRUE) {
        if (p == NULL) {
            return -1;
        } else {
            if (!strcmp(p->key, key)) {
                return p->value;
            }
            p = p->next;
        }
    }
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    int hashed_key;
    int idx;
    node_t* p;

    hashed_key = (hashmap->hash_func)(key);
    idx = hashed_key % hashmap->length;

    p = *(hashmap->plist + idx);

    while (TRUE) {
        if (p == NULL) {
            return FALSE;
        } else {
            if (!strcmp(p->key, key)) {
                p->value = value;
                return TRUE;
            }
            p = p->next;
        }
    }
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    int hashed_key;
    int idx;
    node_t* p;
    node_t* pre_p = NULL;

    hashed_key = (hashmap->hash_func)(key);
    idx = hashed_key % hashmap->length;

    p = *(hashmap->plist + idx);

    while (TRUE) {
        if (p == NULL) {
            return FALSE;
        } else {
            if (!strcmp(p->key, key)) {
                if (pre_p == NULL) {
                    *(hashmap->plist + idx) = p->next;
                    free(p->key);
                    free(p);
                } else {
                    pre_p->next = p->next;
                    free(p->key);
                    free(p);
                }
                return TRUE;
            }
            pre_p = p;
            p = p->next;
            
        }
    }
}

void destroy(hashmap_t* hashmap)
{
    node_t* p;
    node_t* tmp_p;
    size_t i;

    for (i = 0; i < hashmap->length; i++) {
        p = *(hashmap->plist + i);
        while (p != NULL) {
            tmp_p = p;
            p = p->next;
            free(tmp_p->key);
            free(tmp_p);
        }
    }

    free(hashmap->plist);
    free(hashmap);
}
