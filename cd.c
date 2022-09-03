#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include "cd.h"
// #include "variables.h"
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
void cd__(char *separated, char *s, char *current_dir, char *prev, char *tilda, char *temp1)
{
    separated = strtok(NULL, s);
    if (separated == NULL)
    {
        separated = strdup("~");
    }
    char *abc;
    abc = strtok(NULL, s);
    // printf("%s/n", abc);
    if (abc != NULL)
    {
        printf("no such file or directory present");
        return;
    }
    // printf("%s", separated);
    if (strcmp(separated, "..") == 0)
    {
        char prev_dir[100];
        // chdir(separated);
        // getcwd(prev_dir, 100);
        // chdir(current_dir);
        // strcpy(current_dir, prev_dir);
        strcpy(prev, current_dir);
        cut_(current_dir, prev_dir);
        // printf("%s\n", prev_dir);
        strcpy(current_dir, prev_dir);
        // printf("%s\n", current_dir);
    }
    else if (strcmp(separated, ".") == 0)
    {
        strcpy(prev, current_dir);
    }
    else if (strcmp(separated, "~") == 0 || strcmp(separated, "~/") == 0)
    {
        strcpy(prev, current_dir);
        strcpy(current_dir, tilda);
    }
    else if (strcmp(separated, "-") == 0)
    {
        // chdir(separated);
        // getcwd(current_dir, 100);
        if (strcmp(prev, "\0") == 0)
        {
            // strcpy(current_dir, tilda);
            printf("cd - error");
        }
        else
        {
            char y[100];
            strcpy(y, current_dir);
            strcpy(current_dir, prev);
            strcpy(prev, y);
            printf("%s", current_dir);
            printf("\n");
        }
    }
    else
    {
        // printf("%s\n", temp1);
        // if (chdir(separated) != -1)
        // {
        //     strcpy(current_dir, separated);
        //     printf("%s\n",current_dir);
        // }
        // else
        // {
        if (separated[0] == '~')
        {
            // char new_dir[100];
            strcat(temp1, tilda);
            strcat(temp1, &separated[1]);
        }
        else
        {
            if (chdir(separated) != -1)
            {
                strcpy(prev, current_dir);
                getcwd(separated, 100);
                strcpy(current_dir, separated);
                // printf("%s\n", current_dir);
            }
            else
            {

                // strcat(temp1, current_dir);
                // // printf("%s\n", temp1);
                // // if (separated[0] == '.' && separated[1] == '/')
                // // {
                // //     strcat(temp1, &separated[1]);
                // // }
                // if (separated[0] == '/')
                // {
                //     printf("no such file or directory present");
                // }
                // else
                // {
                //     strcat(temp1, "/");
                //     strcat(temp1, separated);
                // }
                // printf("%s\n",temp1);
                // int h = chdir(temp1);
                // if (h == -1)
                // {
                perror("chdir() error");
                // }
                // else
                // {
                    // strcpy(prev, current_dir);
                //     getcwd(current_dir, 100);
                //     // printf("%s\n", current_dir);
                // }
            }
        }
        // printf("%s\n", temp1);
        // }
    }
}