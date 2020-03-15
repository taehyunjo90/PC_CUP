#include <assert.h>
#include "parentheses.h"

#define PARENTHESES_MAX_SIZE (50)

void test_is_paren(void)
{
    char t = ']';
    char t_s_1 = 'a';
    char t_s_2 = '[';

    char a = '[';

    assert(is_end_paren(t) == 1);
    assert(is_end_paren(a) == 0);
    assert(is_start_paren(t, t_s_1) == 0);
    assert(is_start_paren(t, t_s_2) == 1);

    printf("Test is paren passed...\n");
}

void test_is_exist_already_by_opening_idx(void)
{
    parenthesis_t a;
    parenthesis_t b;
    parenthesis_t c;
    parenthesis_t arr_parens[3];

    
    a.opening_index = 1;
    a.closing_index = 2;

    b.opening_index = 3;
    b.closing_index = 4;

    c.opening_index = 0;
    c.closing_index = 5;

    arr_parens[0] = a;
    arr_parens[1] = b;
    arr_parens[2] = c;

    assert(is_exist_already_by_opening_idx(arr_parens, 3, 1) == 1);
    assert(is_exist_already_by_opening_idx(arr_parens, 3, 3) == 1);
    assert(is_exist_already_by_opening_idx(arr_parens, 3, 0) == 1);

    assert(is_exist_already_by_opening_idx(arr_parens, 3, 8) == 0);
    assert(is_exist_already_by_opening_idx(arr_parens, 3, 9) == 0);

    printf("Test is opening idx checking passed...\n");

}

void test_find_start_paren(void)
{
    char* str = "[[]]";
    char* forward_p = str + 2;
    int forward_idx = 2;

    parenthesis_t a;
    parenthesis_t b;
    parenthesis_t c;
    parenthesis_t arr_parens[3];

    a.opening_index = 0;
    a.closing_index = 2;

    b.opening_index = 3;
    b.closing_index = 4;

    c.opening_index = 7;
    c.closing_index = 6;

    arr_parens[0] = a;
    arr_parens[1] = b;
    arr_parens[2] = c;
       
    printf("%d\n", find_start_paren_backward(forward_p, forward_idx, arr_parens, 3));
}

int main(void)
{
    test_is_paren();
    test_is_exist_already_by_opening_idx();
    test_find_start_paren();

    
    parenthesis_t parentheses[PARENTHESES_MAX_SIZE];

    size_t len = get_matching_parentheses(parentheses, PARENTHESES_MAX_SIZE, "}{)(][><");
    
    assert(len == 0);

    len = get_matching_parentheses(parentheses, PARENTHESES_MAX_SIZE, "{{{}}}");

    assert(len == 3);


    assert(parentheses[0].opening_index == 0);
    assert(parentheses[0].closing_index == 5);

    assert(parentheses[1].opening_index == 1);
    assert(parentheses[1].closing_index == 4);

    assert(parentheses[2].opening_index == 2);
    assert(parentheses[2].closing_index == 3);

    len = get_matching_parentheses(parentheses, PARENTHESES_MAX_SIZE, " {]}[[i]{)))} ]");

    assert(len == 4);

    assert(parentheses[0].opening_index == 1);
    assert(parentheses[0].closing_index == 3);

    assert(parentheses[1].opening_index == 4);
    assert(parentheses[1].closing_index == 14);

    assert(parentheses[2].opening_index == 5);
    assert(parentheses[2].closing_index == 7);

    assert(parentheses[3].opening_index == 8);
    assert(parentheses[3].closing_index == 12);

    len = get_matching_parentheses(parentheses, PARENTHESES_MAX_SIZE, "{this}(bracket;[](){[(><>)");

    assert(len == 5);

    assert(parentheses[0].opening_index == 0);
    assert(parentheses[0].closing_index == 5);

    assert(parentheses[1].opening_index == 15);
    assert(parentheses[1].closing_index == 16);

    assert(parentheses[2].opening_index == 17);
    assert(parentheses[2].closing_index == 18);

    assert(parentheses[3].opening_index == 21);
    assert(parentheses[3].closing_index == 25);

    assert(parentheses[4].opening_index == 23);
    assert(parentheses[4].closing_index == 24);

    printf("DONE\n");

    return 0;
}
