#ifndef USER_H
#define USER_H

#define MAX_LENGTH (50)

typedef struct user {
    size_t id;
    char username[MAX_LENGTH + 1];
    char email[MAX_LENGTH + 1];
    char password[MAX_LENGTH + 1];
} user_t;

#endif
