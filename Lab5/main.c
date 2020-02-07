#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "receipter.h"

int main(void)
{
    time_t time = 1569472997;
    int i;
    char* filename;
    
    
    
    for (i = 0 ; i < 50 ; i ++ ) {
        filename = NULL;
        
        assert(TRUE == add_item("Magarita", 12.45));

        add_tip(20.55);

        add_message("Thanks for dining with us!");

        assert(FALSE == print_receipt(filename, time));
    }

    printf("Done!\n");

	return 0;
}

