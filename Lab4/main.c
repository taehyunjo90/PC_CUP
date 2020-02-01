#include <assert.h>
#include <string.h>
#include "my_string.h"

#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

 
void print_address(void* addr1, void* addr2) {
    printf("	Return value: %p", addr1);
    if (addr1 == addr2) {
        printf(" == ");
    } else {
        printf(" != ");
    }
    printf("%p(Expected value)\n\n", addr2);
}
 
int main(void)
{
    char str[] = "Oh happy day! My lovely day!";
    char* token;
    int is_passed = 1;
 
    /* &str[0]을 반환. 토큰은 "hO" */
    token = reverse_tokenize(str, " !");
    printf("\"%s\" == \"%s\"?", token, "hO");
    if (strcmp(token, "hO") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[0]);
    if (token != &str[0]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[3]을 반환. 토큰은 "yppah" */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "yppah");
    if (strcmp(token, "yppah") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[3]);
    if (token != &str[3]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[9]을 반환. 토큰은 "yad" */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "yad");
    if (strcmp(token, "yad") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[9]);
    if (token != &str[9]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[14]을 반환. 토큰은 "yM" */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "yM");
    if (strcmp(token, "yM") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[14]);
    if (token != &str[14]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[17]을 반환. 토큰은 "lovely" */
    token = tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "lovely");
    if (strcmp(token, "lovely") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[17]);
    if (token != &str[17]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[24]을 반환. 토큰은 "yad" */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "yad");
    if (strcmp(token, "yad") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[24]);
    if (token != &str[24]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[28]을 반환. 토큰은 ""('\0') */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "");
    if (strcmp(token, "") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[28]);
    if (token != &str[28]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /*
    	토큰화가 모두 끝난 빈 문자열("". 즉, '\0')을 넣어도,
    	시작위치 제대로 반환
	*/
    /* &str[28]을 반환. 토큰은 ""('\0') */
    token = reverse_tokenize(token, " !");
    printf("\"%s\" == \"%s\"?", token, "");
    if (strcmp(token, "") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[28]);
    if (token != &str[28]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /*
    	이미 토큰화가 다 된(delims를 만나지 않고, '\0'으로 끝나는 연속된 문자들) 단위라도,
    	시작위치 제대로 반환
	*/
    /* &str[0]을 반환. 토큰은 "hO" */
    token = tokenize(str, " !");
    printf("\"%s\" == \"%s\"?", token, "hO");
    if (strcmp(token, "hO") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[0]);
    if (token != &str[0]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /*
    	이미 토큰화가 다 된(delims를 만나지 않고, '\0'으로 끝나는 연속된 문자들) 단위라도,
    	단위를 정상적으로 뒤집고, 시작위치 제대로 반환
	*/
    /* &str[0]을 반환. 토큰은 "Oh" */
    token = reverse_tokenize(str, " !");
    printf("\"%s\" == \"%s\"?", token, "Oh");
    if (strcmp(token, "Oh") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[0]);
    if (token != &str[0]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
end:
    if (is_passed == 1) {
        /* 위 테스트를 모두 성공하면 이 메시지를 출력 */
        printf("~~~ If you see this message, you passed all tokenize test. ~~~\n");
        return 0;
    } else {
        /* 위 테스트 중 하나라도 실패하면, 바로 goto로 여기로 오면서 이 실패 메시지를 출력 */
        printf("!!! You may correct your function. !!!\n");
        return 1;
    }
}
 




/* int main(void)
{
    const char* str = "We all live in a yellow submarine";
    char str_cpy[34];
    const char* token;
    
    
    strncpy(str_cpy, str, 33);
    str_cpy[33] = '\0';

    reverse(str_cpy);
    assert(strcmp("enirambus wolley a ni evil lla eW", str_cpy) == 0);

    
    assert(index_of(str, "all ") == 3);
    assert(index_of(str, "marine") == 27);
    assert(index_of(str, "all good") == -1);
    assert(index_of(str, "marinett") == -1);
    
    reverse(str_cpy);

    assert(strcmp(str_cpy, str) == 0);

    reverse_by_words(str_cpy);

    assert(strcmp("eW lla evil ni a wolley enirambus", str_cpy) == 0);
    reverse_by_words(str_cpy);

    assert(strcmp(str_cpy, str) == 0);
    
    print_str(str_cpy, 33);
    tokenize(str_cpy, " wi");
    print_str(str_cpy, 33); 
    
    
    assert(tokenize(NULL, " ") == NULL);
    
    token = tokenize(str_cpy, " ");
    assert(token == str_cpy);
    assert(strcmp(token, "We") == 0);
    
    token = tokenize(NULL, " ");
    
    assert(token == str_cpy + 3);
    assert(strcmp(token, "all") == 0);
    
    
    token = tokenize(NULL, " ");
    assert(token == str_cpy + 7);
    assert(strcmp(token, "live") == 0);
    
    token = reverse_tokenize(NULL, " ");
    assert(token == str_cpy + 12);
    assert(strcmp(token, "ni") == 0);

    token = reverse_tokenize(NULL, " ");
    token = reverse_tokenize(NULL, " ");
    assert(token == str_cpy + 17);
    assert(strcmp(token, "wolley") == 0);
    printf("clear test");
    return 0;
    
    
} */

