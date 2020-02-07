#ifndef RECEIPTER_H
#define RECEIPTER_H

#define TRUE (1)
#define FALSE (0)

#include <time.h>
#include <stdio.h>

int add_item(const char* name, double price);

void add_tip(double tip);

void add_message(const char* message);

int print_receipt(const char* filename, time_t timestamp);

/* my sub module */
void append_company_name(void);
void append_divider(void);
void append_time(time_t timestamp);
void append_blank(int blank_count);
void append_receipt_count(void);
void append_ordered_menu(void);
void _append_food(int order_num);
void _append_price(int order_num);
void append_new_line(void);
void append_sub_total(void);
void append_tip(void);
void append_tax(void);
void append_total(void);
void append_thanks_message(void);
void append_double_divider(void);
void append_tax_info(void);
void _append_str_to_total_print_with_category_and_price(char* category, double price);

void _append_str_to_total_print(char* target_str);
int print_total_to_file_stream(FILE* file_stream, int total_print_length);

/* my test code */
void print_foods(void);
void print_tip(void);
void print_message(void);

#endif /* RECEIPTER_H */
