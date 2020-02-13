#include "translate.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SET (1024)
#define BUFFER_MAP (1024)


int translate(int argc, const char** argv)
{
    char set_one[BUFFER_SET];
    char set_two[BUFFER_SET];

    char map_one[BUFFER_MAP];
    char map_two[BUFFER_MAP];
    
    int input_c;
    int output_c;
    
    error_code_t err_code = 0;
    int is_i_option = FALSE;
    
    
    if (argc != 3 && argc != 4) {
        err_code = ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
        goto end;
    }
    
    if (argc == 4) {
        if (!strcmp(argv[1], "-i")) {
            is_i_option = TRUE;
        
            strncpy(set_one, argv[2], BUFFER_SET);
            set_one[BUFFER_SET - 1] = '\0';
    
            strncpy(set_two, argv[3], BUFFER_SET);
            set_two[BUFFER_SET - 1] = '\0';
        } else {
            err_code = ERROR_CODE_INVALID_FLAG;
            goto end;
        }
    } else if (argc == 3) {
        err_code = argv_to_set(argv[1], set_one);
        if (err_code != 0) {
            goto end;
        }
        err_code = argv_to_set(argv[2], set_two);
        if (err_code != 0) {
            goto end;
        }
    }
    
    map_one[0] = '\0';
    map_two[0] = '\0';
    
    /* printf("SHOW SETS -> set1 : %s, set2 : %s\n", set_one, set_two); */
    
    set_maps(set_one, set_two, map_one, map_two);
    /* printf("SHOW MAPS -> map1 : %s, map2 : %s\n", map_one, map_two); */
    
    while (TRUE) {
        input_c = getchar();
        if ( input_c == EOF) {
            break;
        }
        output_c = unit_translate(input_c, map_one, map_two, is_i_option);
        putchar(output_c);
    }
    
    end:
    return err_code;
}

error_code_t argv_to_set(const char* argv_target, char* set_target)
{
    int idx = 0;
    const char* argv_ptr = argv_target + idx;
    char escape_end_char;
    
    int is_start_position = TRUE;
    int is_range = FALSE;
    char start_char;
    char end_char;
       
    while (*argv_ptr != '\0') {
        
        /* escape 문자 처리 과정 */
        if (*argv_ptr == '\\') { 
            argv_ptr ++;
            escape_end_char = *argv_ptr;
            if (escape_end_char == '\\') {
                set_target[idx] = '\\';
            } else if (escape_end_char == 'a') {
                set_target[idx] = '\a';
            } else if (escape_end_char == 'b') {
                set_target[idx] = '\b';
            } else if (escape_end_char == 'f') {
                set_target[idx] = '\f';
            } else if (escape_end_char == 'n') {
                set_target[idx] = '\n';
            } else if (escape_end_char == 'r') {
                set_target[idx] = '\r';
            } else if (escape_end_char == 't') {
                set_target[idx] = '\t';
            } else if (escape_end_char == 'v') {
                set_target[idx] = '\a';
            } else if (escape_end_char == 'a') {
                set_target[idx] = '\v';
            } else if (escape_end_char == '\'') {
                set_target[idx] = '\'';
            } else if (escape_end_char == '\"') {
                set_target[idx] = '\"';
            } else {
                return ERROR_CODE_INVALID_FORMAT;
            }
        } else {
            set_target[idx] = *argv_ptr;
        }
        
        /* 범위 지정 과정 */
        if (is_start_position) {
            is_start_position = FALSE;
        } else if (!is_start_position && !is_range) {
            if (set_target[idx] == '-') {
                is_range = TRUE;
            }
        } else if (!is_start_position && is_range) {
            if (set_target[idx] != '\0') {
                char tmp_for_range;
                char idx_for_range;
                
                start_char = set_target[idx - 2];
                end_char = set_target[idx];
                
                if (start_char > end_char) {
                    return ERROR_CODE_INVALID_RANGE;
                }
                
                tmp_for_range = (int) start_char;
                idx_for_range = idx - 2;
                while (tmp_for_range <= end_char) {
                    set_target[idx_for_range] = (char) tmp_for_range;
                    /* printf("%c\n", set_target[idx_for_range]); */
                    tmp_for_range ++;
                    idx_for_range ++;
                }
                
                idx = idx_for_range - 1;
                /* printf("start_char : %c -> end_char : %c\n", start_char, end_char); */
                is_start_position = TRUE;
                is_range = FALSE;
            }
        }        
        
        idx ++;
        argv_ptr ++;
        
        if (idx >= 512) {
            return ERROR_CODE_INVALID_FORMAT;
        }
    }
    set_target[idx] = '\0';
    /* printf("SET : %s\n", set_target); */
    return 0;
}


void set_maps(char* set_one, char* set_two, char* map_one, char* map_two)
{   
    char* set_one_ptr = set_one;
    char* set_two_ptr = set_two;
    
    int i = 0;
    int where_same_char_index;
    
    while (*set_one_ptr != '\0') {
        where_same_char_index = get_index_from_string(*set_one_ptr, map_one);
        if ( where_same_char_index == -1) {
            map_one[i] = *set_one_ptr;
            map_two[i] = *set_two_ptr;
            i ++;
        } else {
            map_one[where_same_char_index] = *set_one_ptr;
            map_two[where_same_char_index] = *set_two_ptr;
        }
        set_one_ptr ++;
        if ( *(set_two_ptr + 1) != '\0') {
            set_two_ptr ++;
        }
    }
    map_one[i] = '\0';
    map_two[i] = '\0';
}

char unit_translate(char target_char, char* src_string, char* des_string, int is_i_option)
{
    int index;
    index = get_index_from_string(target_char, src_string);
    if (index == -1) {
        if (is_i_option) {
            return unit_translate_i_option(target_char, src_string, des_string);
        }
        return target_char;
    } else {
        return *(des_string + index);
    }
}

char unit_translate_i_option(char target_char, char* src_string, char* des_string)
{   
    int index;
    char converted_char = '\0';
    if (target_char >= 'a' && target_char <= 'z') {
        converted_char = toupper(target_char);
    } else if (target_char >= 'A' && target_char <= 'Z') {
        converted_char = tolower(target_char);
    }
    index = get_index_from_string(converted_char, src_string);
    if (index == -1) {
        return target_char;
    } else {
        return *(des_string + index);
    }
}

int get_index_from_string(char target_char, char* string)
{
    int is_found = FALSE;
    char* string_ptr = string;
    int index = 0;
    
    while (*string_ptr != '\0') {
        if (*string_ptr == target_char) {
            is_found = TRUE;
            break;
        }
        index ++;
        string_ptr++;
    }
    
    if (is_found) {
        return index;
    } else {
        index = -1;
        return index;
    }
}
