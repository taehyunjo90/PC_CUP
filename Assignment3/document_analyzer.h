#ifndef DOCUMENT_ANALYZER_H
#define DOCUMENT_ANALYZER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TRUE (1)
#define FALSE (0)

int load_document(const char* document);

void dispose(void);

size_t get_total_word_count(void);

size_t get_total_sentence_count(void);

size_t get_total_paragraph_count(void);

const char*** get_paragraph(const size_t paragraph_index);

size_t get_paragraph_word_count(const char*** paragraph);

size_t get_paragraph_sentence_count(const char*** paragraph);

const char** get_sentence(const size_t paragraph_index, const size_t sentence_index);

size_t get_sentence_word_count(const char** sentence);

int print_as_tree(const char* filename);

void set_word_malloc(char* start_word_ptr, char* delim_word_ptr, char** pa_word);

char* get_next_word_start(char* p);

char* get_next_paragraph_start(char* p);

int is_delim_word(char* p);

int is_delim_sentence(char* p);

int is_delim_paragraph(char* p);

#endif /* DOCUMENT_ANALYZER_H */
