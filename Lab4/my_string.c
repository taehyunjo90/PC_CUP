#include "my_string.h"
#include <stdio.h>

#define TRUE  1
#define FALSE 0

static int s_is_once_started = FALSE;
static char* s_ptr;

void reverse(char* str)
{
    size_t len_str;
    len_str = my_strlen(str);
    reverse_n(str, len_str);
}

int index_of(const char* str, const char* word)
{
    size_t len_str = my_strlen(str);
    size_t len_word = my_strlen(word);
    
    size_t i;
    size_t j;
    
    const char* start_ptr;
    const char* str_detail_ptr;
    const char* word_detail_ptr;
    
    int is_match;
    
    for (i = 0; i < len_str - len_word + 1 ; i++) {
        start_ptr = str + i;
        is_match = TRUE;
        for (j = 0; j < len_word; j++) {
            str_detail_ptr = start_ptr + j;
            word_detail_ptr = word + j;
            if (*str_detail_ptr != *word_detail_ptr) {
                is_match = FALSE;
            }
            if (is_match == FALSE) {
                break;
            }
        }
        
        if (is_match == TRUE) {
            return i;
        }
    }
    return -1;
}

void reverse_by_words(char* str)
{
    size_t word_size;
    char* word_start_ptr;
    char* loop_ptr;
        
    loop_ptr = str;
    while (*loop_ptr != '\0') {
        word_start_ptr = loop_ptr;
        word_size = 0;
        while (*loop_ptr != ' ' && *loop_ptr != '\0') {
            word_size ++;
            loop_ptr ++;
        }
        reverse_n(word_start_ptr, word_size);
        loop_ptr ++;
    }
}

char* tokenize(char* str, const char* delims)
{
    int is_toknized = FALSE;
    int is_pre_toknized = FALSE;
    char* start_ptr;
    
    if (str == NULL && is_once_started == FALSE) {
        return NULL;
    } else if (str != NULL) {
        ptr = str;
    }
    
    start_ptr = ptr;
    
    while (*ptr != '\0') {
        is_toknized = if_char_is_in_delims_then_null_char(ptr, delims);
        if (is_pre_toknized == TRUE && is_toknized == FALSE) {
            break;
        }
        ptr ++;
        is_pre_toknized = is_toknized;
    }
    is_once_started = TRUE;
    
    return start_ptr;
}

int if_char_is_in_delims_then_null_char(char* char_ptr, const char* delims)
{   
    int is_delim;
    const char* delim_ptr = delims;
    while (*delim_ptr != '\0') {
        is_delim = if_char_is_delim_then_null_char(char_ptr, delim_ptr);
        if (is_delim) {
            return 1;
        }
        delim_ptr ++;
    }
    return 0;
}


int if_char_is_delim_then_null_char(char* char_ptr, const char* delim)
{
    if (*char_ptr == *delim) {
        *char_ptr = '\0';
        return 1;
    } else {
        return 0;
    }
}

char* reverse_tokenize(char* str, const char* delims)
{
    int is_toknized = FALSE;
    int is_pre_toknized = FALSE;
    char* start_ptr;
    int count = 0;
    
    if (str == NULL && is_once_started == FALSE) {
        return NULL;
    } else if (str != NULL) {
        ptr = str;
    }
    
    start_ptr = ptr;
    
    while (*ptr != '\0') {
        is_toknized = if_char_is_in_delims_then_null_char(ptr, delims);
        if (is_toknized == FALSE) {
            count ++;
        }
        
        if (is_pre_toknized == TRUE && is_toknized == FALSE) {
            break;
        }
        ptr ++;
        is_pre_toknized = is_toknized;
    }
    is_once_started = TRUE;
    
    if (*ptr == '\0') {
        reverse_n(start_ptr, count);
    } else {
        reverse_n(start_ptr, count - 1);
    }
    
    
    
    return start_ptr;
}

void reverse_n(char* str, size_t len_str)
{
    size_t i;
    
    char tmp;
    char* start_ptr;
    char* end_ptr;
    
    start_ptr = str;
    end_ptr = str + len_str - 1;
    
    for (i = 0; i < len_str / 2; i++) {
        tmp = *end_ptr;
        *end_ptr = *start_ptr;
        *start_ptr = tmp;
        start_ptr++;
        end_ptr--;
    }
}

size_t my_strlen(const char* str)
{
    size_t i = 0;
    const char* cur_ptr = str;
    while (*cur_ptr != '\0') {
        cur_ptr ++;
        i++;
    }
    return i;
}

void print_str(char* str, size_t len_str)
{
    size_t i;
    char* ptr = str;
    for (i = 0; i < len_str; i++) {
        printf("%c", *ptr);
        ptr ++;
    }
    printf("\n");
}
