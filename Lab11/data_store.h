#ifndef DATA_STORE_H
#define DATA_STORE_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "user.h"

#define BUFFER (256)

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id);

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username);

bool update_email(user_t** users_or_null, size_t id, const char* email);

bool update_password(user_t** users_or_null, size_t id, const char* password);

#endif 
