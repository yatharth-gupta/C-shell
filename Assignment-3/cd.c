#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include "cd.h"
#include "variables.h"
void cut_(char *current_dir, char *previous_dir)
{
    int size = 0;
    int i = 0;
    for (i = strlen(current_dir) - 1; i >= 0; i--)
    {
        if (current_dir[i] != '/')
        {
            size++;
        }
        else
        {
            break;
        }
    }
    if (i == 0)
    {
        strncpy(previous_dir, current_dir, strlen(current_dir) - size);
        previous_dir[strlen(current_dir) - size] = '\0';
    }
    else
    {
        strncpy(previous_dir, current_dir, strlen(current_dir) - size - 1);
        previous_dir[strlen(current_dir) - size - 1] = '\0';
    }
}
void cd__(char *tokens[], int token_size)
{
    char prev[1000];
    if (token_size == 1)
    {
        strcpy(prev, current_dir);
        strcpy(current_dir, tilda);
    }
    else if (strcmp(tokens[1], "..") == 0)
    {
        char prev_dir[1000];
        chdir(tokens[1]);
        strcpy(prev, current_dir);
        cut_(current_dir, prev_dir);
        strcpy(current_dir, prev_dir);
    }
    else if (strcmp(tokens[1], ".") == 0)
    {
        chdir(tokens[1]);
        strcpy(prev, current_dir);
    }
    else if (strcmp(tokens[1], "~") == 0 || strcmp(tokens[1], "~/") == 0 || tokens[1] == NULL)
    {
        strcpy(prev, current_dir);
        strcpy(current_dir, tilda);
        chdir(current_dir);
    }
    else if (strcmp(tokens[1], "-") == 0)
    {
        if (strcmp(prev, "\0") == 0)
        {
            printf("cd - error");
        }
        else
        {
            char y[1000];
            strcpy(y, current_dir);
            strcpy(current_dir, prev);
            strcpy(prev, y);
            printf("%s", current_dir);
            chdir(current_dir);
            printf("\n");
        }
    }
    else
    {
        // if (strcmp(tokens[1], "~") == 0)
        // {
        //     strcat(temp1, tilda);
        //     strcat(temp1, &tokens[1][0]);
        // }
        // else
        // {
        if (chdir(tokens[1]) != -1)
        {
            strcpy(prev, current_dir);
            getcwd(tokens[1], 1000);
            strcpy(current_dir, tokens[1]);
        }
        else
        {
            perror("chdir() error");
        }
        // }
    }
}