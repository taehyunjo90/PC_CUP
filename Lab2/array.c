#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i;
    
    for (i = 0; i < element_count; ++i) {
        if (numbers[i] == num) {
            return i;
        }
    }
    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i;
    int last_index_of = -1;
    
    for (i = 0; i < element_count; ++i) {
        if (numbers[i] == num) {
            last_index_of = i;
        }
    }
    return last_index_of;

}

int get_max_index(const int numbers[], const size_t element_count)
{
    size_t i;
    int max_value;
    int max_index = -1;

    if (element_count != 0) {
        max_value = numbers[0];
        max_index = 0;
        for (i = 1; i < element_count; ++i) {
            if (numbers[i] > max_value) {
                max_value = numbers[i];
                max_index = i;
            }
        }
    }
    return max_index;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    size_t i;
    int min_value;
    int min_index = -1;
    
    if (element_count != 0) {
        min_value = numbers[0];
        min_index = 0;
        for (i = 1; i < element_count; ++i) {
            if (numbers[i] < min_value){
                min_value = numbers[i];
                min_index = i;
            }
        }
    }
    return min_index;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    size_t i;
    
    if (element_count == 0) {
        return 0;
    }
    
    for (i = 0; i < element_count; ++i) {
        if (numbers[i] < 0){
            return 0;
        }
    }
    return 1;
}

int has_even(const int numbers[], const size_t element_count)
{
    size_t i;
    
    for (i = 0; i < element_count; ++i) {
        if (numbers[i] % 2 == 0) {
            return 1;
        }
    }
    return 0;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    size_t i;
    size_t reverse_index;
    
    if (pos > element_count) {
        return 0;
    }
    
    for (i = 0; i < element_count + 1; ++i) {
        reverse_index = element_count - i;
        if (reverse_index > pos) {
            numbers[reverse_index] = numbers[reverse_index - 1];
        } else if (reverse_index == pos) {
            numbers[reverse_index] = num;
        }
    }
    return 1;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    size_t i;
    
    if (element_count == 0 || index > element_count) {
        return 0;
    }
    
    for (i = 0; i < element_count; ++i) {
        if (i >= index) {
            numbers[i] = numbers[i+1];
        }
    }
    return 1;
}

