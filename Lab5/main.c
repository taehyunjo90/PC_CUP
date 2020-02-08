#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "receipter.h"

int main(void)
{
    time_t time = 1569472997;
    int i;
    char test_file_name[] = "receipt.txt"; 
    char* filename;
    
    
    
    for (i = 0 ; i < 10 ; i ++ ) {        
        assert(TRUE == add_item("", 12.45));

        add_tip(20.55);

        add_message("Thanks for dining with ussldafkadfjlkadjflkajdfkladjfklcajdfklajdfklcajdfkladjfckdlafjalkdfck!");

        print_receipt(test_file_name, time);
    }
    
    for (i = 0 ; i < 10 ; i ++ ) {        
        assert(TRUE == add_item("Magarita", 12.45));

        add_tip(20.55);

        print_receipt("receipt1.txt", time);
    }
    
    for (i = 0 ; i < 10 ; i ++ ) {        
        assert(TRUE == add_item("Magarita", 12.45));
        assert(TRUE == add_item("Magarita", 12.45));
        assert(TRUE == add_item("Magarita", 12.45));
        assert(TRUE == add_item("Magarita", 12.45));
        

        add_message("Thanks for dining with ussldafkadfjlkadjflkajdfkladjfklcajdfklajdfklcajdfkladjfckdlafjalkdfck!");

        print_receipt("receipt2.txt", time);
    }

    printf("Done!\n");

	return 0;
}

