#include "todo_list.h"


todo_list_t* init_todo_list_malloc(size_t max_size)
{
    todo_list_t* p;
    todo_list_t* tmp_p;

    p = malloc(sizeof(todo_list_t) * (max_size + 1));

    // init first element
    p->is_meta = true;
    p->total_count = 0;
    p->max_count = (int32_t)max_size;
    p->is_empty = false;

    tmp_p = p;
    // init other elemnts
    for (size_t i = 0; i < max_size; i++) {
        tmp_p++;
        tmp_p->is_meta = false;

        tmp_p->is_empty = true;
        tmp_p->todo_task = NULL;
        tmp_p->todo_priority = 0;
    }

    return p;
}

void dispose(todo_list_t* todo_list)
{
    todo_list_t* p = todo_list;
    int32_t total_count;
    int32_t max_count;
    
    if (NULL != todo_list) {
        total_count = p->total_count;
        max_count = p->max_count;

        for (int32_t i = 0; i < max_count; i++) {
            p++;
            if (!p->is_empty) {
                free(p->todo_task);
            }
        }
        free(todo_list);
    }
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    todo_list_t* p = todo_list;
    int32_t total_count;
    int32_t max_count;
    size_t len_task;
    
    if (todo_list == NULL) {
        return false;
    }

    total_count = p->total_count;
    max_count = p->max_count;

    // early exit when is full
    if (total_count == max_count) {
        return false;
    }

    for (int32_t i = 0; i < max_count; i++) {
        p++;
        if (p->is_empty) {
            break;
        }
    }

    len_task = strlen(task);
    p->is_empty = false;
    p->todo_priority = priority;
    p->todo_task = malloc(sizeof(char) * (len_task + 1));
    strcpy(p->todo_task, task);
    *(p->todo_task + len_task) = '\0';

    todo_list->total_count++;

    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    todo_list_t* p = todo_list;
    
    todo_list_t* max_priority_todo = NULL;
    int32_t max_priority;

    int32_t total_count;
    int32_t max_count;
    
    if (todo_list == NULL) {
        return false;
    }

    total_count = p->total_count;
    max_count = p->max_count;

    for (int32_t i = 0; i < max_count; i++) {
        p++;
        if (!p->is_empty && max_priority_todo == NULL) {
            max_priority_todo = p;
            max_priority = p->todo_priority;
        } else if (!p->is_empty && max_priority < p->todo_priority) {
            max_priority_todo = p;
            max_priority = p->todo_priority;
        }
    }

    if (max_priority_todo == NULL) {
        return false;
    } else {
        free(max_priority_todo->todo_task);
        max_priority_todo->is_meta = false;
        max_priority_todo->is_empty = true;
        max_priority_todo->todo_task = NULL;
        max_priority_todo->todo_priority = 0;

        todo_list->total_count--;
        return true;
    }
}

const char* peek_or_null(todo_list_t* todo_list)
{
    todo_list_t* p = todo_list;

    todo_list_t* max_priority_todo = NULL;
    int32_t max_priority;

    int32_t total_count;
    int32_t max_count;
    
    if (todo_list == NULL) {
        return NULL;
    }

    total_count = p->total_count;
    max_count = p->max_count;

    for (int32_t i = 0; i < max_count; i++) {
        p++;
        if (!p->is_empty && max_priority_todo == NULL) {
            max_priority_todo = p;
            max_priority = p->todo_priority;
        } else if (!p->is_empty && max_priority < p->todo_priority) {
            max_priority_todo = p;
            max_priority = p->todo_priority;
        }
    }

    if (max_priority_todo == NULL) {
        return NULL;
    } else {
        return max_priority_todo->todo_task;
    }
    
}

size_t get_count(todo_list_t* todo_list)
{
    todo_list_t* p = todo_list;
    
    if (todo_list == NULL) {
        return 0;
    }
    
    return p->total_count;
}

bool is_empty(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return false;
    }
    
    if (0 == todo_list->total_count) {
        return true;
    }
    
    return false;
}

