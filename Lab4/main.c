#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "my_string.h"

int main(void)
{
    char str[] = "X  my name is mui";
    char single[] = "a";
    char empty[] = "";

    char* token;

    /* REVERSE */
    reverse(str);
    assert(strcmp(str, "ium si eman ym  X") == 0);
    reverse(str);

    reverse_by_words(str);
    assert(strcmp(str, "X  ym eman si ium") == 0);
    reverse_by_words(str);
    assert(strcmp(str, "X  my name is mui") == 0 );

    reverse(single);
    assert(strcmp(single, "a") == 0);

    reverse_by_words(single);
    assert(strcmp(single, "a") == 0);

    reverse(empty);
    assert(strcmp(empty, "") == 0);

    reverse_by_words(empty);
    assert(strcmp(empty, "") == 0);

    /* INDEX OF */
    assert(index_of(str, "my") == 3);
    assert(index_of(str, "X") == 0);
    assert(index_of(str, "") == 0);
    
    assert(index_of(NULL, "X") == -1);
    assert(index_of(str, "X    ") == -1);
    assert(index_of(str, "mui") == 14);
    assert(index_of(single, "a") == 0);
    
    assert(index_of(empty, "") == 0);
    assert(index_of("", "a") == -1);
    assert(index_of("    ", "a") == -1);

    /* TOKENIZER */
    printf("tokenizer!\n");
    assert(tokenize(NULL, " !") == NULL);

    token = tokenize(str, " ");
    assert(token == str);
    assert(strcmp(token, "X") == 0);

    token = tokenize(NULL, " ");
    assert(token == str + 3);
    assert(strcmp(token, "my") == 0);

    token = reverse_tokenize(NULL, " ");
    assert(token == str + 6);
    assert(strcmp(token, "eman") == 0);

    token = tokenize(NULL, " ");
    assert(token == str + 11);
    assert(strcmp(token, "is") == 0);

    token = reverse_tokenize(NULL, " ");
    assert(token == str + 14);
    assert(strcmp(token, "ium") == 0);

    token = reverse_tokenize(NULL, " ");
    assert(token == NULL);
    token = tokenize(NULL, " ");
    assert(token == NULL);
    printf("clear!");

    return 0;
}
