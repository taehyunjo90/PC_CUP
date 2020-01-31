#ifndef MY_STRING_H
#define MY_STRING_H

void reverse(char* str);

int index_of(const char* str, const char* word);

void reverse_by_words(char* str);

char* tokenize(char* str, const char* delims);

char* reverse_tokenize(char* str, const char* delims);

/* my func */
void reverse_n(char* str, size_t len_str);
size_t my_strlen(const char* str);
void print_str(char* str, size_t len_str);
int if_char_is_in_delims_then_null_char(char* char_ptr, const char* delims);
int if_char_is_delim_then_null_char(char* char_ptr, const char* delim);


#endif /* MY_STRING_H */
