#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

char** tokenize_malloc(const char* str, const char* delim)
{
    char** tokens = NULL;
    char** pa_tokens = NULL;
    char* token = NULL;
    char* pa_token = NULL;

    const char* p = str;

    const char* org_token_start = NULL;
    const char* org_token_end = NULL;
    size_t token_size = 0;
    size_t tokens_size = 0;

    int is_meet_delim = 0;

    while (*p != '\0') {
        is_meet_delim = is_char_in_delim(*p, delim);
        if (org_token_start == NULL && is_meet_delim == 0) {
            org_token_start = p;
        } else if (org_token_start != NULL && is_meet_delim) {
            org_token_end = p - 1;
            token_size = (org_token_end - org_token_start + 1);

            tokens_size++;
            if (tokens == NULL) {
                pa_tokens = malloc(tokens_size * sizeof(char*));
            } else {
                pa_tokens = realloc(tokens, tokens_size * sizeof(char*));
            }

            if (pa_tokens != NULL) {
                tokens = pa_tokens;
            }

            pa_token = malloc((token_size + 1) * sizeof(char));
            token = pa_token;
            memcpy(token, org_token_start, (token_size + 1) * sizeof(char));
            *(pa_token + token_size) = '\0';
            *(tokens + tokens_size - 1) = pa_token;

            org_token_start = NULL;
            org_token_end = NULL;
        }
        p++;
    }

    if (org_token_start != NULL) {
        org_token_end = p - 1;
        token_size = (org_token_end - org_token_start + 1);

        tokens_size++;
        if (tokens == NULL) {
            pa_tokens = malloc(tokens_size * sizeof(char*));
        } else {
            pa_tokens = realloc(tokens, tokens_size * sizeof(char*));
        }
        

        if (pa_tokens != NULL) {
            tokens = pa_tokens;
        }

        pa_token = malloc((token_size + 1) * sizeof(char));
        token = pa_token;
        memcpy(token, org_token_start, (token_size + 1) * sizeof(char));
        *(pa_token + token_size) = '\0';
        *(tokens + tokens_size - 1) = pa_token;

        org_token_start = NULL;
        org_token_end = NULL;
    }

    tokens_size++;
    if (tokens == NULL) {
        pa_tokens = malloc(tokens_size * sizeof(char*));
    } else {
        pa_tokens = realloc(tokens, tokens_size * sizeof(char*));
    }
    

    if (pa_tokens != NULL) {
        tokens = pa_tokens;
    }

    *(tokens + tokens_size - 1) = NULL;

    return tokens;

    
}


int is_char_in_delim(const char c, const char* delim)
{
    const char* p = delim;
    int is_char = 0;
    while (*p != '\0') {
        if (c == *p) {
            is_char = 1;
            break;
        }
        p++;
    }
    return is_char;
}
