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
void cd__(char *tokens[], char *s, char *current_dir, char *prev, char *tilda, char *temp1)
{
    // tokens = strtok(NULL, s);
    // if (tokens == NULL)
    // {
    //     tokens = strdup("~");
    // }
    // char *abc;
    // abc = strtok(NULL, s);
    // // printf("%s/n", abc);
    // if (abc != NULL)
    // {
    //     printf("no such file or directory present");
    //     return;
    // }
    // printf("%s", tokens);
    if (strcmp(tokens[1], "..") == 0)
    {
        char prev_dir[100];
        // chdir(tokens);
        // getcwd(prev_dir, 100);
        // chdir(current_dir);
        // strcpy(current_dir, prev_dir);
        strcpy(prev, current_dir);
        cut_(current_dir, prev_dir);
        // printf("%s\n", prev_dir);
        strcpy(current_dir, prev_dir);
        // printf("%s\n", current_dir);
    }
    else if (strcmp(tokens[1], ".") == 0)
    {
        strcpy(prev, current_dir);
    }
    else if (strcmp(tokens[1], "~") == 0 || strcmp(tokens[1], "~/") == 0)
    {
        strcpy(prev, current_dir);
        strcpy(current_dir, tilda);
    }
    else if (strcmp(tokens[1], "-") == 0)
    {
        // chdir(tokens);
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
        // if (chdir(tokens) != -1)
        // {
        //     strcpy(current_dir, tokens);
        //     printf("%s\n",current_dir);
        // }
        // else
        // {
        if (strcmp(tokens[1], "~") == 0)
        {
            // char new_dir[100];
            strcat(temp1, tilda);
            strcat(temp1, &tokens[1][0]);
        }
        else
        {
            if (chdir(tokens[1]) != -1)
            {
                strcpy(prev, current_dir);
                getcwd(tokens[1], 100);
                strcpy(current_dir, tokens[1]);
                // printf("%s\n", current_dir);
            }
            else
            {

                // strcat(temp1, current_dir);
                // // printf("%s\n", temp1);
                // // if (tokens[0] == '.' && tokens[1] == '/')
                // // {
                // //     strcat(temp1, &tokens[1]);
                // // }
                // if (tokens[0] == '/')
                // {
                //     printf("no such file or directory present");
                // }
                // else
                // {
                //     strcat(temp1, "/");
                //     strcat(temp1, tokens);
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