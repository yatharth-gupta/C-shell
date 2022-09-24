#include <stdlib.h>
#include "history.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "variables.h"
void history__(int items_in_history)
{
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
}