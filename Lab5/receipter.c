#include "receipter.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_MENU 10
#define PRINT_MAX_COL_LENGTH (50)
#define PRINT_MAX_ROW_LENGTH (50)
#define TOTAL_PRINT_LENGTH (4096)

static int s_receipt_count = 0;

static const char* s_food_names[MAX_MENU];
static double s_food_prices[MAX_MENU];

static char s_food_names_[MAX_MENU][PRINT_MAX_COL_LENGTH];
 
static int s_food_count = 0;

static const char* s_thanks_message = NULL;

static double s_sum_of_food_prices = 0.0;
static double s_tip = 0.0;
static double s_tax = 0.0;

static char s_total_print[TOTAL_PRINT_LENGTH];
static int s_len_total_print = 0;

int add_item(const char* name, double price)
{   
    if (s_food_count >= 10) {
        return FALSE;
    }
    s_food_names[s_food_count] = name;
    s_food_prices[s_food_count] = price;
    
    /* !!! */
    strncpy(s_food_names_[s_food_count], name, 25);
    s_food_names_[s_food_count][25] = '\0';
    
    s_food_count ++;
    return TRUE;
}

void add_tip(double tip)
{
    s_tip = tip;
}

void add_message(const char* message)
{
    s_thanks_message = message;
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* file_stream;
        
    if (s_food_count == 0 || filename == NULL) {
        s_food_count = 0;
        s_sum_of_food_prices = 0.0;
        s_tip = 0.0;
        s_tax = 0.0;
        s_len_total_print = 0;
        s_thanks_message = NULL;        
        return FALSE;
    }
    
    s_total_print[0] = '\0';
    
    append_company_name();
    append_divider();
    append_time(timestamp);
    append_blank(26);
    append_receipt_count();
    append_divider();
    append_ordered_menu();
    append_new_line();
/*     append_sub_total();
    append_tip();
    append_tax();
    append_total();
    append_new_line();
    append_thanks_message();
    append_double_divider();
    append_tax_info(); */
    
    file_stream = fopen(filename, "wb");
    print_total_to_file_stream(file_stream, s_len_total_print);
    fclose(file_stream);
    
    s_receipt_count ++;
    
    s_food_count = 0;
    s_sum_of_food_prices = 0.0;
    s_tip = 0.0;
    s_tax = 0.0;
    s_len_total_print = 0;
    s_thanks_message = NULL;
    
    
    return TRUE;
}

/* my sub module */
void append_company_name(void)
{   
    char company_name[] = "Charles' Seafood\n";
    _append_str_to_total_print(company_name);
}

void append_divider(void)
{
    char divider[] = "--------------------------------------------------\n";
    _append_str_to_total_print(divider);
}

void append_time(time_t timestamp)
{
    char time_string[PRINT_MAX_COL_LENGTH + 10];
    struct tm *ptm = gmtime(&timestamp);
    sprintf(time_string, "%04d-%02d-%02d %02d:%02d:%02d", ptm->tm_year + 1900, ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    _append_str_to_total_print(time_string);
}

void append_blank(int blank_count)
{
    int i;
    for (i = 0 ; i < blank_count ; i ++) {
        _append_str_to_total_print(" ");
    }
}

void append_receipt_count(void)
{
    char receipt_count_string[PRINT_MAX_COL_LENGTH];
    sprintf(receipt_count_string, "%05d\n", s_receipt_count);
    _append_str_to_total_print(receipt_count_string);
}

void append_ordered_menu(void)
{
    int i;
    for (i = 0 ; i < s_food_count; i++) {
        _append_food(i);
        _append_price(i);
    }
}

void _append_food(int order_num)
{
    /* char food_name[PRINT_MAX_COL_LENGTH + 10];
    char string_food_name[PRINT_MAX_COL_LENGTH + 10];
    strncpy(food_name, s_food_names[order_num], 25);
    food_name[25] = '\0';
    sprintf(string_food_name, "%33s", food_name);
    _append_str_to_total_print(string_food_name); */
    
    /* !!! */
    char food_name[PRINT_MAX_COL_LENGTH + 10];
    char string_food_name[PRINT_MAX_COL_LENGTH + 10];
    strncpy(food_name, s_food_names_[order_num], 25);
    food_name[25] = '\0';
    sprintf(string_food_name, "%33s", food_name);
    _append_str_to_total_print(string_food_name);
}

void _append_price(int order_num)
{
    char string_price[PRINT_MAX_COL_LENGTH + 10];
    sprintf(string_price, "%17.2f\n", s_food_prices[order_num]);
    _append_str_to_total_print(string_price);
    
}

void append_new_line(void)
{
    char new_line[] = "\n";
    _append_str_to_total_print(new_line);
}

void append_sub_total(void)
{
    char subtotal_category[] = "Subtotal";
    int i;
    
    for (i = 0 ; i < s_food_count; i ++) {
        s_sum_of_food_prices += s_food_prices[i];
    }
    
    _append_str_to_total_print_with_category_and_price(subtotal_category, s_sum_of_food_prices);
    
}

void append_tip(void)
{
    char tip_catetory[] = "Tip";
    
    if (s_tip != 0.0) {
        _append_str_to_total_print_with_category_and_price(tip_catetory, s_tip);
    }
}

void append_tax(void)
{
    char tax_category[] = "Tax";
    
    s_tax = s_sum_of_food_prices * 0.05;
    _append_str_to_total_print_with_category_and_price(tax_category, s_tax);
}

void append_total(void)
{
    char total_category[] = "Total";
    double total = 0;
    
    total += s_sum_of_food_prices;
    total += s_tip;
    total += s_tax;
    
    _append_str_to_total_print_with_category_and_price(total_category, total);
}

void _append_str_to_total_print_with_category_and_price(char* category, double price)
{
    char subtotal_line[PRINT_MAX_COL_LENGTH + 1];
    sprintf(subtotal_line, "%33s%17.2f\n", category, price);
    _append_str_to_total_print(subtotal_line);
}

void append_thanks_message(void)
{
    int len_thanks_msg;
    char thanks_msg_buffer[PRINT_MAX_COL_LENGTH + 10];
    const char* next_line_ptr;
    
    if (s_thanks_message == NULL) {
        return;
    }
    
    len_thanks_msg = strlen(s_thanks_message);
    
    strncpy(thanks_msg_buffer, s_thanks_message, 50);
    thanks_msg_buffer[50] = '\0';
    _append_str_to_total_print(thanks_msg_buffer);
    append_new_line();
    
    if (len_thanks_msg > 50) {
        next_line_ptr = s_thanks_message + 50;
        strncpy(thanks_msg_buffer, next_line_ptr, 25);
        thanks_msg_buffer[25] = '\0';
        _append_str_to_total_print(thanks_msg_buffer);
        append_new_line();
    }
}

void append_double_divider(void)
{
    char divider[] = "==================================================\n";
    _append_str_to_total_print(divider);
    
}

void append_tax_info(void)
{
    char tax_info_line[PRINT_MAX_COL_LENGTH + 10];
    char tax_info[] = "Tax#-51234";
    
    sprintf(tax_info_line, "%50s", tax_info);
    _append_str_to_total_print(tax_info_line);
}

void _append_str_to_total_print(char* target_str)
{
    char* write_point = s_total_print;
    write_point += s_len_total_print;
    strcpy(write_point, target_str);
    s_len_total_print += strlen(target_str);
}


int print_total_to_file_stream(FILE* file_stream, int total_print_length)
{
    fwrite(s_total_print, 1, total_print_length, file_stream);
    return 1;
}

/* my test code */

void print_foods(void)
{
    int i;
    
    for (i = 0; i < s_food_count ; i++) {
        printf("food_name : %s, food_price : %f\n", s_food_names[i], s_food_prices[i]);
    }
}

void print_tip(void)
{
    printf("tip is : %f\n", s_tip);
}


void print_message(void)
{
    printf("thanks_message : %s\n", s_thanks_message);
}
