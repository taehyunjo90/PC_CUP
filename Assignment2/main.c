#include "translate.h"
#include <stdio.h>

int main(int argc, const char* argv[])
{
    error_code_t err_code;
    err_code =  translate(argc, argv);
    /* printf("%d", err_code); */
    return err_code;
}
