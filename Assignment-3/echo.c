#include <stdlib.h>
#include "echo.h"
#include <stdio.h>
#include <string.h>
void echo__(char *tokens[], int token_size)
{
    int i = 1;
    while (i < token_size)
    {
        printf("%s ", tokens[i]);
        i++;
    }
    printf("\n");
}