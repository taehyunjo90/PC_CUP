#include <assert.h>
#include <string.h>
#include "document_analyzer.h"
#include <stdio.h>

void test_empty(void)
{
    printf("1");
    assert(load_document("input_empty.txt") == TRUE);
    printf("2");
    assert(print_as_tree("output_empty.txt") == FALSE);
    printf("3");
    assert(get_total_word_count() == 0U);
    printf("4");
    assert(get_total_sentence_count() == 0U);
    printf("5");
    assert(get_total_paragraph_count() == 0U);
    printf("6");


    dispose();

    puts("test_empty");
}

void test_document(void)
{
    const char** sentence = NULL;
    const char*** paragraph = NULL;
    assert(get_paragraph(0) == NULL);
    assert(get_sentence(0, 0) == NULL);
    assert(get_total_word_count() == 0U);
    assert(get_total_sentence_count() == 0U);
    assert(get_total_paragraph_count() == 0U);
    assert(print_as_tree("output_document.txt") == FALSE);

    assert(load_document("document.txt") == TRUE);

    assert(get_total_word_count() == 62U);
    assert(get_total_sentence_count() == 6U);
    assert(get_total_paragraph_count() == 3U);

    paragraph = get_paragraph(0);
    assert(paragraph != NULL);
    assert(get_paragraph_word_count(paragraph) == 19);
    assert(get_paragraph_sentence_count(paragraph) == 1);
    sentence = get_sentence(0, 0);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 19);
    assert(get_sentence(0, 1) == NULL);

    paragraph = get_paragraph(1);
    assert(paragraph != NULL);
    assert(get_paragraph_word_count(paragraph) == 28);
    assert(get_paragraph_sentence_count(paragraph) == 3);
    sentence = get_sentence(1, 0);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 10);
    sentence = get_sentence(1, 1);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 9);
    sentence = get_sentence(1, 2);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 9);
    assert(get_sentence(1, 3) == NULL);

    paragraph = get_paragraph(2);
    assert(paragraph != NULL);
    assert(get_paragraph_word_count(paragraph) == 15);
    assert(get_paragraph_sentence_count(paragraph) == 2);
    sentence = get_sentence(2, 0);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 8);
    sentence = get_sentence(2, 1);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 7);
    assert(get_sentence(2, 2) == NULL);

    assert(get_paragraph(3) == NULL);

    assert(print_as_tree("output_document.txt") == TRUE);

    dispose();

    puts("test_document");
}


int main(void)
{
    test_empty();
    test_document();
    printf("DONE");

    return 0;
}


