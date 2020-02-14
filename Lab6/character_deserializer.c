#include "character_deserializer.h"

int get_character(const char* filename, character_v3_t* out_character)
{
    char first_line[LINE_LENGTH];
    FILE* file_stream;
    int version = -1;
    
    file_stream = fopen(filename, "r");
    
    /* version check */
    if (read_one_line(first_line, file_stream)) {
        version = check_version(first_line);
    }
    
    /* deserialize */
    if (version == 1) {
        deserialize_version_1(file_stream, out_character);
    } else if (version == 2) {
        deserialize_version_2(file_stream, out_character);
    } else if (version == 3) {
        deserialize_version_3(file_stream, out_character);
    }
    
    fclose(file_stream);
    
    return version;
}

int read_one_line(char* where_to_put_line, FILE* file_stream) 
{
    if (fgets(where_to_put_line, LINE_LENGTH, file_stream) != NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}


int check_version(const char* first_line)
{
    int is_comma = FALSE;
    int is_colon = FALSE;
    int is_vertical_bar = FALSE;
    
    const char* first_line_ptr = first_line;
    
    while (*first_line_ptr != '\0') {
        if (*first_line_ptr == ',') {
            is_comma = TRUE;
        } else if (*first_line_ptr == ':') {
            is_colon = TRUE;
        } else if (*first_line_ptr == '|') {
            is_vertical_bar = TRUE;
        }
        first_line_ptr ++;
    }
    
    if (is_comma && is_colon && !is_vertical_bar) {
        return 1;
    } else if (is_comma && !is_colon && !is_vertical_bar) {
        return 2;
    } else if (!is_comma && !is_colon && is_vertical_bar) {
        return 3;
    }
    
    return -1;
}

int deserialize_version_1(FILE* file_stream, character_v3_t* out_character)
{   
    char line[LINE_LENGTH];
    char category[LINE_LENGTH];
    char value[LINE_LENGTH];
    
    char* line_ptr = line;
    char* category_ptr = category;
    char* value_ptr = value;
    
    int is_category = TRUE;
    
    rewind(file_stream);
    read_one_line(line, file_stream);
    
    while (*line_ptr != '\0') {
        
        if (is_category && *line_ptr != ':') {
            *category_ptr = *line_ptr;
            category_ptr ++;
        } else if (is_category && *line_ptr == ':') {
            is_category = FALSE;
            *category_ptr = '\0';
        } else if (!is_category && !(*line_ptr == ',')) {
            *value_ptr = *line_ptr;
            value_ptr ++;
        } else if ((!is_category && *line_ptr == ',')) {
            is_category = TRUE;
            *value_ptr = '\0';

            value_ptr = value;
            category_ptr = category;
            
            /* set out_character */
            _set_version_1_data_by_category_and_value(category, value, out_character);
        }
        line_ptr ++;
    }
    
    *value_ptr = '\0';
    value_ptr = value;
    category_ptr = category;
    /* set out_character */
    _set_version_1_data_by_category_and_value(category, value, out_character);
    
    out_character->evasion = out_character->dexterity / 2;
    out_character->elemental_resistance.fire = out_character->armour / 4 / 3;
    out_character->elemental_resistance.cold = out_character->armour / 4 / 3;
    out_character->elemental_resistance.lightning = out_character->armour / 4 / 3;
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
    

    return 0;
}

void _set_version_1_data_by_category_and_value(char* category, char* value, character_v3_t* out_character)
{
    unsigned int value_tmp;
    
    sscanf(value, "%d", &value_tmp);
    if (strcmp(category, "id") == 0) {
        char tmp_name[] = "player_";
        out_character->name[0] = '\0';
        strcat(out_character->name, tmp_name);
        strcat(out_character->name, value);
    } else if (strcmp(category, "lvl") == 0) {
        out_character->level = value_tmp;
    } else if (strcmp(category, "str") == 0) {
        out_character->strength = value_tmp;
    } else if (strcmp(category, "dex") == 0) {
        out_character->dexterity = value_tmp;
    } else if (strcmp(category, "intel") == 0) {
        out_character->intelligence = value_tmp;
    } else if (strcmp(category, "def") == 0) {
        out_character->armour = value_tmp;
    } else if (strcmp(category, "hp") == 0) {
        out_character->health = value_tmp;
    } else if (strcmp(category, "mp") == 0) {
        out_character->mana = value_tmp;
    }
}

int deserialize_version_2(FILE* file_stream, character_v3_t* out_character)
{
    char line_one[LINE_LENGTH];
    char line_two[LINE_LENGTH];
    
    char category[LINE_LENGTH];
    char value[LINE_LENGTH];
    
    char* line_one_ptr = line_one;
    char* line_two_ptr = line_two;
    
    char* category_ptr = category;
    char* value_ptr = value;
    
    unsigned int value_tmp;
    
    rewind(file_stream);
    read_one_line(line_one, file_stream);
    read_one_line(line_two, file_stream);
    /* printf("%s : %s\n", line_one_ptr, line_two_ptr); */
    
    
    while (TRUE) {
        
        while (*line_one_ptr != ',' && *line_one_ptr != '\n') {
            *category_ptr = *line_one_ptr;
            line_one_ptr ++;
            category_ptr ++;
        }
        *category_ptr = '\0';
        
        while (*line_two_ptr != ',' && *line_two_ptr != '\0') {
            *value_ptr = *line_two_ptr;
            line_two_ptr ++;
            value_ptr ++;
        }
        *value_ptr = '\0';
        
        /* deserialize */
        if (strcmp(category, "name") != 0) {
            sscanf(value, "%d", &value_tmp);
        }
        
        if (strcmp(category, "name") == 0) { 
            out_character->name[0] = '\0';
            strncat(out_character->name, value, 50);
        } else if (strcmp(category, "level") == 0) {
            out_character->level = value_tmp;
        } else if (strcmp(category, "strength") == 0) {
            out_character->strength = value_tmp;
        } else if (strcmp(category, "dexterity") == 0) {
            out_character->dexterity = value_tmp;
        } else if (strcmp(category, "intelligence") == 0) {
            out_character->intelligence = value_tmp;
        } else if (strcmp(category, "armour") == 0) {
            out_character->armour = value_tmp;
        } else if (strcmp(category, "evasion") == 0) {
            out_character->evasion = value_tmp;
        } else if (strcmp(category, "magic_resistance") == 0) {
            out_character->elemental_resistance.fire = value_tmp / 3;
            out_character->elemental_resistance.cold = value_tmp / 3;
            out_character->elemental_resistance.lightning = value_tmp / 3;
        } else if (strcmp(category, "health") == 0) {
            out_character->health = value_tmp;
        } else if (strcmp(category, "mana") == 0) {
            out_character->mana = value_tmp;
        } 
        
        /* 종료 조건 */
        if (*line_one_ptr == '\n' && *line_two_ptr == '\0') {
            break;
        }
        
        
        category_ptr = category;
        value_ptr = value;
        line_one_ptr ++;
        line_two_ptr ++;
        
    }
    
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
    
    return 0;
}

int deserialize_version_3(FILE* file_stream, character_v3_t* out_character)
{
    char line_one[LINE_LENGTH];
    char line_two[LINE_LENGTH];
    
    char category[LINE_LENGTH];
    char value[LINE_LENGTH];
    
    char* line_one_ptr = line_one;
    char* line_two_ptr = line_two;
    
    char* category_ptr = category;
    char* value_ptr = value;
    
    unsigned int value_tmp;
    
    rewind(file_stream);
    read_one_line(line_one, file_stream);
    read_one_line(line_two, file_stream);
    
    while (TRUE) {
        
        while (*line_one_ptr != '|' && *line_one_ptr != '\n') {
            if (*line_one_ptr != ' ') {
                *category_ptr = *line_one_ptr;
                category_ptr ++;
            }
            line_one_ptr ++;
        }
        *category_ptr = '\0';
        
        while (*line_two_ptr != '|' && *line_two_ptr != '\0' && *line_two_ptr != '\n') {
            if (*line_two_ptr != ' ') {
                *value_ptr = *line_two_ptr;
                value_ptr ++;
            }
            line_two_ptr ++;
        }
        *value_ptr = '\0';
        
        /* deserialize */
        if (strcmp(category, "name") != 0) {
            sscanf(value, "%d", &value_tmp);
        }
        
        if (strcmp(category, "name") == 0) { 
            out_character->name[0] = '\0';
            strncat(out_character->name, value, 50);
        } else if (strcmp(category, "level") == 0) {
            out_character->level = value_tmp;
        } else if (strcmp(category, "strength") == 0) {
            out_character->strength = value_tmp;
        } else if (strcmp(category, "dexterity") == 0) {
            out_character->dexterity = value_tmp;
        } else if (strcmp(category, "intelligence") == 0) {
            out_character->intelligence = value_tmp;
        } else if (strcmp(category, "armour") == 0) {
            out_character->armour = value_tmp;
        } else if (strcmp(category, "evasion") == 0) {
            out_character->evasion = value_tmp;
        } else if (strcmp(category, "fire_res") == 0) {
            out_character->elemental_resistance.fire = value_tmp;
        } else if (strcmp(category, "cold_res") == 0) {
            out_character->elemental_resistance.cold = value_tmp;
        } else if (strcmp(category, "lightning_res") == 0) {
            out_character->elemental_resistance.lightning = value_tmp;
        } else if (strcmp(category, "leadership") == 0) {
            out_character->leadership = value_tmp;
        } else if (strcmp(category, "mana") == 0) {
            out_character->mana = value_tmp;
        } else if (strcmp(category, "health") == 0) {
            out_character->health = value_tmp;
        } else if (strcmp(category, "minion_count") == 0) {
            out_character->minion_count = value_tmp;
        }
        
        /* 종료 조건 */
        if (*line_one_ptr == '\n') {
            break;
        }
        
        category_ptr = category;
        value_ptr = value;
        line_one_ptr ++;
        line_two_ptr ++;
        
    }
    
    
    if (out_character->minion_count != 0) {
        size_t i;
        read_one_line(line_one, file_stream);
        
        for (i = 0; i < out_character->minion_count; i ++ ) {
            read_one_line(line_two, file_stream);
            
            line_one_ptr = line_one;
            line_two_ptr = line_two;
            category_ptr = category;
            value_ptr = value;
            
            
            while (TRUE) {
            
                while (*line_one_ptr != '|' && *line_one_ptr != '\n') {
                    if (*line_one_ptr != ' ') {
                        *category_ptr = *line_one_ptr;
                        category_ptr ++;
                    }
                    line_one_ptr ++;
                }
                *category_ptr = '\0';
                
                while (*line_two_ptr != '|' && *line_two_ptr != '\0' && *line_two_ptr != '\n') {
                    if (*line_two_ptr != ' ') {
                        *value_ptr = *line_two_ptr;
                        value_ptr ++;
                    }
                    line_two_ptr ++;
                }
                *value_ptr = '\0';
                
                if (strcmp(category, "name") != 0) {
                    sscanf(value, "%d", &value_tmp);
                }
                
                if (strcmp(category, "name") == 0) { 
                    out_character->minions[i].name[0] = '\0';
                    strncat(out_character->minions[i].name, value, 50);
                } else if (strcmp(category, "health") == 0) {
                    out_character->minions[i].health = value_tmp;
                } else if (strcmp(category, "strength") == 0) {
                    out_character->minions[i].strength = value_tmp;
                } else if (strcmp(category, "defence") == 0) {
                    out_character->minions[i].defence = value_tmp;
                }
                /* 종료 조건 */
                if (*line_one_ptr == '\n') {
                    break;
                }
                
                category_ptr = category;
                value_ptr = value;
                line_one_ptr ++;
                line_two_ptr ++;
            
            }


        }
        
        
    }
    
    return 0;
}
