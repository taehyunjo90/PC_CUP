#include "parentheses.h"

size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str)
{
    const char* forward_p;
    int forward_p_idx = 0;
    int backward_p_idx = 0;

    size_t len_parenthesis = 0;

    forward_p = str;
    while (*forward_p != '\0') {
        if (is_end_paren(*forward_p)) {
            backward_p_idx = find_start_paren_backward(forward_p, forward_p_idx, parentheses, len_parenthesis);
            if (backward_p_idx != -1) {
                add_parentheses(parentheses, &len_parenthesis, max_size, backward_p_idx, forward_p_idx);
            }
        }
        forward_p_idx++;
        forward_p++;
    }

    qsort(parentheses, len_parenthesis, sizeof(parenthesis_t), compare_paren);
    
    return len_parenthesis;
}

int is_end_paren(char end_paren)
{
    
    char* parens = "})]>";
    char* tmp = parens;

    while (*tmp != '\0') {
        if (end_paren == *tmp) {
            return TRUE;
        }
        tmp++;
    }
    return FALSE;
}

int is_start_paren(char end_paren, char start_paren)
{
    char check_paren;

    if (end_paren == ']') {
        check_paren = '[';
    } else if (end_paren == '>') {
        check_paren = '<';
    } else if (end_paren == ')') {
        check_paren = '(';
    } else if (end_paren == '}') {
        check_paren = '{';
    } else {
        return FALSE;
    }

    if (check_paren == start_paren) {
        return TRUE;
    }

    return FALSE;
}

int is_exist_already_by_opening_idx(parenthesis_t* parentheses, int len_parentheses, int opening_idx)
{
    int i = 0;
    parenthesis_t cur_parenthesis;
    for (i = 0; i < len_parentheses; i++) {
        cur_parenthesis = *(parentheses + i);
        if ((int)cur_parenthesis.opening_index == opening_idx) {
            return TRUE;
        }
    }
    return FALSE;
}

int find_start_paren_backward(const char* forward_p, int forward_idx, parenthesis_t* parentheses, int len_parentheses)
{
    int i;
    char cur_char;
    char end_paren = *forward_p;
    int cur_idx = forward_idx;

    for (i = 0; i < forward_idx; i++) {
        cur_char = *(--forward_p);
        cur_idx--;
        if (is_start_paren(end_paren, cur_char) && !is_exist_already_by_opening_idx(parentheses, len_parentheses, cur_idx)) {
            return cur_idx;
        }
    }
    return -1;
}

void add_parentheses(parenthesis_t* parentheses, size_t* p_len_parentheses, size_t max_size, int opening_idx, int closing_idx)
{
    size_t o_i = (size_t)opening_idx;
    size_t c_i = (size_t)closing_idx;

    if (max_size != *p_len_parentheses) {
        (parentheses + *p_len_parentheses)->opening_index = o_i;
        (parentheses + *p_len_parentheses)->closing_index = c_i;

        (*p_len_parentheses)++;
    }    
}

int compare_paren(const void* first, const void* second)
{
    parenthesis_t* first_ = (parenthesis_t*)first;
    parenthesis_t* second_ = (parenthesis_t*)second;
    return first_->opening_index - second_->opening_index;
}

