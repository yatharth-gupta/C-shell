#include<stdlib.h>
#include "echo.h"
#include <stdio.h>
#include<string.h>
void echo__(char* separated,char *s)
{
    separated = strtok(NULL, s);
    if (separated != NULL)
        printf("%s ", separated);
    separated = strtok(NULL, s);
    while (separated != NULL)
    {
        printf("%s ", separated);
        separated = strtok(NULL, s);
    }
    printf("\n");
}