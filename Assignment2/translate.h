#ifndef TRANSLATE_H
#define TRANSLATE_H

#define TRUE (1)
#define FALSE (0)

typedef enum error_code {
    ERROR_CODE_WRONG_ARGUMENTS_NUMBER = 1, /* used */
    ERROR_CODE_INVALID_FLAG, /* used */
    ERROR_CODE_INVALID_FORMAT, /* used */
    ERROR_CODE_ARGUMENT_TOO_LONG, /* used */
    ERROR_CODE_INVALID_RANGE /* used */
} error_code_t;

int translate(int argc, const char** argv);

int argv_to_set(const char* argv_target, char* set_target);
void set_maps(char* s_set_one, char* s_set_two, char* s_map_one, char* s_map_two);
int get_index_from_string(char target_char, char* string);
char translate_unit(char target_char, char* src_string, char* des_string, int s_is_i_option);
char translate_unit_i_option(char target_char, char* src_string, char* des_string);

#endif /* TRANSLATE_H */
