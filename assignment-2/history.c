#include <stdlib.h>
#include "history.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "variables.h"
void history__(int items_in_history)
{
    // int f = 0;
    // while (f<20)
    // {
        if (items_in_history >= 10)
        {
            for (int i = items_in_history - 10; i < items_in_history; i++)
            {
                printf("%s \n", his_array[i]);
            }
        }
        else
        {
            for (int i = 0; i < items_in_history; i++)
            {
                printf("%s \n", his_array[i]);
            }
        }
        // char *l;
        // if (feof(filepntr))
        // {
        //     break;
        // }
        // fgets(l, 1000, filepntr);
        // printf("%s\n", l);
    // }
}