#ifndef PARENTHESES_H
#define PARENTHESES_H

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE (1)
#define FALSE (0)

typedef struct {
    size_t opening_index;
    size_t closing_index;
} parenthesis_t;

size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str);

int is_end_paren(char end_paren);
int is_start_paren(char end_paren, char start_paren);
int is_exist_already_by_opening_idx(parenthesis_t* parentheses, int len_parentheses, int opening_idx);
void add_parentheses(parenthesis_t* parentheses, size_t* p_len_parentheses, size_t max_size, int opening_idx, int closing_idx);
int compare_paren(const parenthesis_t* first, const parenthesis_t* second);

#endif /* PARENTHESES_H */
