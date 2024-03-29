#include "document_analyzer.h"

#define BUFFER_LENGTH (32)

char* g_loaded_document = NULL;
char**** g_document = NULL;
char*** g_paragraph = NULL;
char** g_sentence = NULL;

int load_document(const char* document)
{
    char buffer[BUFFER_LENGTH];
    int len_readed = 0;
    int malloc_memory_size = 0;

    char* word_start_ptr;
    char* pa_word = NULL;

    int cur_word_count = 0;
    int cur_sentence_count = 0;
    int cur_paragraph_count = 0;

    char* p;

    FILE* file_stream = fopen(document, "r");

    g_loaded_document = NULL;
    g_document = NULL;
    g_paragraph = NULL;
    g_sentence = NULL;

    /* Early exit*/
    if (file_stream == NULL) {
        return FALSE;
    }

    /* load document */
    while (fgets(buffer, BUFFER_LENGTH, file_stream) != NULL) {
        len_readed = strlen(buffer);
        if (g_loaded_document == NULL) {
            malloc_memory_size += len_readed + 1;
            g_loaded_document = (char*)malloc(malloc_memory_size);
            strcpy(g_loaded_document, buffer);
        } else {
            malloc_memory_size += len_readed;
            g_loaded_document = (char*)realloc(g_loaded_document, malloc_memory_size);
            strcpy(g_loaded_document + malloc_memory_size - len_readed - 1, buffer);
        }
    }
    fclose(file_stream);

    /* if loaded document is empty*/
    if (g_loaded_document == NULL) {
        goto end;
    }

    /* Analyze */
    p = g_loaded_document;
    word_start_ptr = p;
    while (*p != '\0') {
        if (is_delim_word(p)) {
            /* �ܾ� �ϼ� ��Ŵ*/
            set_word_malloc(word_start_ptr, p, &pa_word);
            word_start_ptr = get_next_word_start(p);
            p = word_start_ptr;

            g_sentence = (char**)realloc(g_sentence, sizeof(char*) * (cur_word_count + 2));
            g_sentence[cur_word_count++] = pa_word;
            g_sentence[cur_word_count] = NULL;

        } else if (is_delim_sentence(p)) {
            set_word_malloc(word_start_ptr, p, &pa_word);

            word_start_ptr = get_next_word_start(p);
            p = word_start_ptr;

            g_sentence = (char**)realloc(g_sentence, sizeof(char*) * (cur_word_count + 2));
            g_sentence[cur_word_count++] = pa_word;
            g_sentence[cur_word_count] = NULL;

            g_paragraph = (char***)realloc(g_paragraph, sizeof(char**) * (cur_sentence_count + 2));
            g_paragraph[cur_sentence_count++] = g_sentence;
            g_paragraph[cur_sentence_count] = NULL;

            g_sentence = (char**)malloc(sizeof(char*) * 2);
            g_sentence[1] = NULL;
            cur_word_count = 0;

        } else if (is_delim_paragraph(p)) {
            word_start_ptr = get_next_paragraph_start(p);
            p = word_start_ptr;

            g_paragraph[cur_sentence_count] = NULL;

            g_document = (char****)realloc(g_document, sizeof(char***) * (cur_paragraph_count + 2));
            g_document[cur_paragraph_count++] = g_paragraph;
            g_document[cur_paragraph_count] = NULL;

            cur_sentence_count = 0;
            g_paragraph = (char***)malloc(sizeof(char**) * 2);
            g_paragraph[1] = NULL;
            
        }

        if (*p == '\0') {
            break;
        }

        p++;
    }

    g_document = (char****)realloc(g_document, sizeof(char***) * (cur_paragraph_count + 2));
    g_document[cur_paragraph_count++] = g_paragraph;
    g_document[cur_paragraph_count] = NULL;

    free(g_loaded_document);
    free(g_sentence);
end:
    return TRUE;
}

size_t get_total_word_count(void)
{
    size_t total_word_count = 0;

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    if (g_document == NULL) {
        return (size_t)0;
    }

    while (g_document[i] != NULL) {
        while (g_document[i][j] != NULL) {
            while (g_document[i][j][k] != NULL) {
                total_word_count++;
                k++;
            }
            j++;
            k = 0;
        }
        i++;
        j = 0;
        k = 0;
    }
    return total_word_count;

}

size_t get_total_sentence_count(void)
{
    size_t total_sentence_count = 0;

    size_t i = 0;
    size_t j = 0;

    if (g_document == NULL) {
        return (size_t)0;
    }

    while (g_document[i] != NULL) {
        while (g_document[i][j] != NULL) {
            total_sentence_count++;
            j++;
        }
        i++;
        j = 0;
    }
    return total_sentence_count;
}

size_t get_total_paragraph_count(void)
{
    size_t total_paragraph_count = 0;

    size_t i = 0;

    if (g_document == NULL) {
        return (size_t)0;
    }

    while (g_document[i] != NULL) {
        total_paragraph_count++;
        i++;
    }
    return total_paragraph_count;
}

const char*** get_paragraph(const size_t paragraph_index)
{
    size_t total_paragraph_count = get_total_paragraph_count();

    if (paragraph_index < total_paragraph_count) {
        return (const char***)g_document[paragraph_index];
    } else {
        return NULL;
    }
}

size_t get_paragraph_word_count(const char*** paragraph)
{
    size_t word_count = 0;

    size_t i = 0;
    size_t j = 0;

    while (paragraph[i] != NULL) {
        while (paragraph[i][j] != NULL) {
            word_count++;
            j++;
        }
        i++;
        j = 0;
    }

    return word_count;
}

size_t get_paragraph_sentence_count(const char*** paragraph)
{
    size_t sentence_count = 0;

    size_t i = 0;

    while (paragraph[i] != NULL) {
        sentence_count++;
        i++;
    }

    return sentence_count;
}

const char** get_sentence(const size_t paragraph_index, const size_t sentence_index)
{
    size_t total_paragraph_count = get_total_paragraph_count();
    size_t selected_sentence_count;
    const char*** paragraph;

    if (paragraph_index < total_paragraph_count) {
        paragraph = (const char***)g_document[paragraph_index];
    } else {
        return NULL;
    }

    selected_sentence_count = get_paragraph_sentence_count(paragraph);
    if (sentence_index < selected_sentence_count) {
        return (const char**)paragraph[sentence_index];
    } else {
        return NULL;
    }
}

size_t get_sentence_word_count(const char** sentence)
{

    size_t setence_count = 0;

    size_t i = 0;

    while (sentence[i] != NULL) {
        setence_count++;
        i++;
    }

    return setence_count;
}

int print_as_tree(const char* filename)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    FILE* file_stream;

    if (g_document == NULL) {
        return FALSE;
    }

    file_stream = fopen(filename, "w");
    if (file_stream == NULL) {
        return FALSE;
    }

    while (g_document[i] != NULL) {
        fprintf(file_stream, "Paragraph %d:\n", i);
        while (g_document[i][j] != NULL) {
            fprintf(file_stream, "    ");
            fprintf(file_stream, "Sentence %d:\n", j);
            while (g_document[i][j][k] != NULL) {
                fprintf(file_stream, "    ");
                fprintf(file_stream, "    ");
                fprintf(file_stream, "%s", g_document[i][j][k]);
                if (g_document[i + 1] != NULL || g_document[i][j + 1] != NULL || g_document[i][j][k + 1] != NULL) {
                    fprintf(file_stream, "\n");
                }
                k++;
            }
            j++;
            k = 0;
        }

        if (g_document[i + 1] != NULL) {
            fprintf(file_stream, "\n");
        }

        i++;
        j = 0;
        k = 0;
    }

    fclose(file_stream);
    return TRUE;
}


void set_word_malloc(char* start_word_ptr, char* delim_word_ptr, char** pa_word)
{
    int word_len = delim_word_ptr - start_word_ptr;

    if (word_len > 0) {
        *pa_word = (char*)malloc(word_len * sizeof(char) + 1);
        strncpy(*pa_word, start_word_ptr, word_len);
        *(*pa_word + word_len) = '\0';
    } else {
        *pa_word = NULL;
    }
}

char* get_next_word_start(char* p)
{
    char* tmp = p;

    while (is_delim_word(tmp) || is_delim_sentence(tmp)) {
        if (*tmp == '\0') {
            return tmp - 1;
        }
        tmp++;
    }
    return tmp;
}

char* get_next_paragraph_start(char* p)
{
    char* tmp = p;

    while (is_delim_word(tmp) || is_delim_sentence(tmp) || is_delim_paragraph(tmp)) {
        if (*tmp == '\0') {
            return tmp - 1;
        }
        tmp++;
    }
    return tmp;
}

void dispose(void)
{
    int i = 0;
    int j = 0;
    int k = 0;

    if (g_document != NULL) {
        while (g_document[i] != NULL) {
            while (g_document[i][j] != NULL) {
                while (g_document[i][j][k] != NULL) {
                    free(g_document[i][j][k]);
                    k++;
                }
                free(g_document[i][j][k]);
                j++;
                k = 0;
            }
            i++;
            j = 0;
            k = 0;
        }


        i = 0;
        j = 0;
        k = 0;

        while (g_document[i] != NULL) {
            while (g_document[i][j] != NULL) {
                free(g_document[i][j]);
                j++;
            }
            free(g_document[i][j]);
            i++;
            j = 0;
        }

        i = 0;
        j = 0;
        k = 0;

        while (g_document[i] != NULL) {
            free(g_document[i]);
            i++;
        }
        free(g_document[i]);

        free(g_document);
    }
    g_loaded_document = NULL;
    g_document = NULL;
    g_paragraph = NULL;
    g_sentence = NULL;

}

int is_delim_word(char* p)
{
    if (*p == ' ' || *p == ',') {
        return TRUE;
    }
    return FALSE;
}

int is_delim_sentence(char* p)
{
    if (*p == '.' || *p == '!' || *p == '?') {
        return TRUE;
    }
    return FALSE;
}


int is_delim_paragraph(char* p)
{

    if (*p == '\n') {
        return TRUE;
    }
    return FALSE;
}
