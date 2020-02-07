#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "receipter.h"

int main(void)
{
    time_t time = 1569472997;
    int i;
    char filename[50];
    
    
    
    for (i = 0 ; i < 50 ; i ++ ) {
        sprintf(filename, "%02d.txt", i);
        
        assert(TRUE == add_item("Magarita", 12.45));

        add_tip(20.55);

        add_message("Thanks for dining with us!");

        assert(TRUE == print_receipt(filename, time));
    }

    printf("Done!\n");

	return 0;
}

