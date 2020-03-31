#include "data_store.h"

static void log_when_update_email(size_t id, const char* old_email, const char* new_email);

static void log_when_update_password(size_t id, const char* old_password, const char* new_password);

static char* make_secure_email(char* secure_email, const char* email);

static char* make_secure_password(char* secure_password, const char* password);

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    user_t** p = users_or_null;

    if (p == NULL) {
        return NULL;
    }
    
    while (*p != NULL) {
        if ((*p)->id == id) {
            return *p;
        }
        p++;
    }

    return NULL;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    user_t** p = users_or_null;

    if (p == NULL) {
        return NULL;
    }

    while (*p != NULL) {
        if (!strcmp(username, (*p)->username)) {
            return *p;
        }
        p++;
    }

    return NULL;
}

bool update_email(user_t** users_or_null, size_t id, const char* email)
{
    user_t* p = get_user_by_id_or_null(users_or_null, id);

    if (p == NULL) {
        return false;
    }
    log_when_update_email(id, p->email, email);
    strcpy(p->email, email);
    return true;
}

static void log_when_update_email(size_t id, const char* old_email, const char* new_email)
{
    char log_message[BUFFER];
    FILE* fp = fopen("log.txt", "a");
#if defined(RELEASE)
    char secure_old_email[MAX_LENGTH];
    char secure_new_email[MAX_LENGTH];
    make_secure_email(secure_old_email, old_email);
    make_secure_email(secure_new_email, new_email);
    sprintf(log_message, "TRACE: User %d updated email from \"%s\" to \"%s\"\n", id, secure_old_email, secure_new_email);
#else
    sprintf(log_message, "TRACE: User %d updated email from \"%s\" to \"%s\"\n", id, old_email, new_email);
#endif
    fputs(log_message, fp);
    fclose(fp);
}

static char* make_secure_email(char* secure_email, const char* email) 
{
    const char* p = email;
    int len_email = 0;

    while (*p != '@') {
        len_email++;
        p++;
    }

    strcpy(secure_email, email);

    if (len_email == 1) {
        secure_email[0] = '*';
    } else if (len_email == 2) {
        secure_email[1] = '*';
    } else {
        for (int i = 1; i < len_email - 1; i++) {
            secure_email[i] = '*';
        }
    }

    return secure_email;
}


bool update_password(user_t** users_or_null, size_t id, const char* password)
{
    user_t* p = get_user_by_id_or_null(users_or_null, id);
    if (p == NULL) {
        return false;
    }
    log_when_update_password(id, p->password, password);
    strcpy(p->password, password);
    return true;
}

static void log_when_update_password(size_t id, const char* old_password, const char* new_password)
{
    char log_message[BUFFER];
    FILE* fp = fopen("log.txt", "a");

#if defined(RELEASE)
    char secure_old_password[MAX_LENGTH];
    char secure_new_password[MAX_LENGTH];
    make_secure_password(secure_old_password, old_password);
    make_secure_password(secure_new_password, new_password);
    sprintf(log_message, "TRACE: User %d updated password from \"%s\" to \"%s\"\n", id, secure_old_password, secure_new_password);
#else
    sprintf(log_message, "TRACE: User %d updated password from \"%s\" to \"%s\"\n", id, old_password, new_password);
#endif
    fputs(log_message, fp);
    fclose(fp);
}

static char* make_secure_password(char* secure_password, const char* password)
{
    const char* p = password;
    int len_pass = 0;

    while (*p != '\0') {
        len_pass++;
        p++;
    }

    strcpy(secure_password, password);

    if (len_pass == 1) {
        secure_password[0] = '*';
    } else if (len_pass == 2) {
        secure_password[1] = '*';
    } else {
        for (int i = 1; i < len_pass - 1; i++) {
            secure_password[i] = '*';
        }
    }
    return secure_password;
}
