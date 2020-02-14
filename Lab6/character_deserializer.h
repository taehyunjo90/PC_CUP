#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

#include <stdio.h>
#include <string.h>

#define TRUE (1)
#define FALSE (0)

#define LINE_LENGTH (1024)

#define MAX_NAME_LEN (55)
#define MAX_MINION_COUNT (3)


typedef struct {
    char name[MAX_NAME_LEN];
    unsigned int health;
    unsigned int strength;
    unsigned int defence;
} minion_t;

typedef struct {
    unsigned int fire;
    unsigned int cold;
    unsigned int lightning;
    
} elemental_resistance_t;

typedef struct {
    char name[MAX_NAME_LEN];
    unsigned int level;
    unsigned int health;
    unsigned int mana;
    unsigned int strength;
    unsigned int dexterity;
    unsigned int intelligence;
    unsigned int armour;
    unsigned int evasion;
    unsigned int leadership;
    size_t minion_count;
    elemental_resistance_t elemental_resistance;
    minion_t minions[MAX_MINION_COUNT];
} character_v3_t;

int get_character(const char* filename, character_v3_t* out_character);

/* my module */
int read_one_line(char* where_to_put_line, FILE* file_stream);
int check_version(const char* filename);
int deserialize_version_1(FILE* file_stream, character_v3_t* out_character);
void _set_version_1_data_by_category_and_value(char* category, char* value, character_v3_t* out_character);
int deserialize_version_2(FILE* file_stream, character_v3_t* out_character);
int deserialize_version_3(FILE* file_stream, character_v3_t* out_character);

#endif /* CHARACTER_DESERIALIZER_H */
