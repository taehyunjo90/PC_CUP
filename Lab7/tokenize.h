#ifndef TOKENIZE_H
#define TOKENIZE_H

char** tokenize_malloc(const char* str, const char* delim);
int is_char_in_delim(const char c, const char* delim);

#endif /* TOKENIZE_H */

