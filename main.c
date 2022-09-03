#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>

#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
char current_dir[100];
char tilda[100];
void find_tilda(char *currunt_dir, char *tilda, char *relative_curr_dir)
{
    int i = 0;
    int a = strlen(currunt_dir);
    int b = strlen(tilda);
    if (a < b)
    {
        strcpy(relative_curr_dir, currunt_dir);
    }
    while (currunt_dir[i] == tilda[i] && i < b)
    {
        i++;
    }
    if (i != b)
    {
        strcpy(relative_curr_dir, currunt_dir);
    }
    else if (a == b)
    {
    }
    else
    {
        strcpy(&relative_curr_dir[1], &currunt_dir[i]);
    }
}
int main()
{
    char *user_name = getlogin();
    char name[100];
    gethostname(name, 100);
    char temp[100];
    char *separated = "\0";
    getcwd(tilda, 100);
    strcpy(current_dir, tilda);
    char prev[100] = "\0";
    char s[] = " \t\n";
    char s_[] = "&";
    char s__[] = ";";
    while (1)
    {
        char temp1[100] = "\0";
        char *tokens[100];
        char *tokens_[100];
        char *tokens__[100];
        char relative_curr_dir[100] = "~";
        find_tilda(current_dir, tilda, relative_curr_dir);
        if (strcmp(tilda, current_dir) == 0)
        {
            printf("\033[;36m<%s@%s:~>\033[0m", user_name, name);
        }
        else
        {
            printf("\033[;36m<%s@%s:\033[0m", user_name, name);
            printf("\033[;33m%s>\033[0m", relative_curr_dir);
        }
        char *input;
        size_t input_size = 100;
        getline(&input, &input_size, stdin);
        input[strlen(input) - 1] = '\0';
        int h = 0;
        char *g;
        g = strtok(input, s__);
        if (g == NULL)
        {
            continue;
        }
        tokens__[h] = strdup(g);
        // printf("%s\n", tokens__[h]);
        g = strtok(NULL, s__);
        while (g != NULL)
        {
            // printf("%s ", g);
            h++;
            tokens__[h] = strdup(g);
            // printf("%d %s\n", h, tokens__[h]);
            g = strtok(NULL, s__);
        }
        // printf("%d\n", h);
        for (int i = 0; i <= h; i++)
        {
            char input_copy1[100];
            strcpy(input_copy1, tokens__[i]);
            // input_copy1[strlen(tokens__[0])] = '\0';
            // char *input_copy1 = strdup(tokens__[i]);
            // printf("%s\n", input_copy1);
            char *u;
            // if (input_copy1 == NULL)
            // {
            //     goto label;
            // }
            // u = strtok(input_copy1, s);
            // tokens__[h] = strdup(u);
            // printf("%s\n", u);
            u = strtok(input_copy1, s);
            if (u == NULL)
            {
                printf("syntax error\n");
                goto label;
            }
            // if (strlen(u) <= 1)
            // {
            //     printf("%d hi\n", i);
            //     goto label;
            // }
            // while (u != NULL)
            // {
            //     // printf("%s ", u);
            //     // h++;
            //     // tokens__[h] = strdup(u);
            //     // printf("%d %s\n",h, tokens__[h]);
            //     u = strtok(NULL, s);
            // }
        }

        for (int i = 0; i <= h; i++)
        {
            // puts("hi");
            //     // strcat(tokens__[i], " ");
            //     // if (strcmp(tokens__[i], " ") == 0)
            //     // {
            //     //     continue;
            //     // }
            char input_copy[100];
            strcpy(input_copy, tokens__[i]);
            // printf("%s\n", input_copy);
            char *t;
            t = strtok(input_copy, s);
            // printf("%s\n", t);
            tokens[0] = strdup(t);
            //     // strcpy(t, tokens[0]);
            t = strtok(NULL, s);
            int p = 0;
            while (t != NULL)
            {
                // printf("%s ", t);
                tokens[++p] = strdup(t);
                t = strtok(NULL, s);
            }
            char *separated = strtok(tokens__[i], s);
            if (separated == NULL)
                continue;
            // printf("%s\n", t);
            // while (t != NULL)
            // {
            //     t = strtok(NULL, s);
            //     printf("%s\n", t);
            //     tokens[++p] = strdup(t);
            // }
            if (strcmp(separated, "pwd") == 0)
            {
                pwd__();
            }
            else if (strcmp(separated, "cd") == 0)
            {
                cd__(separated, s, current_dir, prev, tilda, temp1);
            }
            else if (strcmp(separated, "echo") == 0)
            {
                echo__(separated, s);
            }
            else if (strcmp(separated, "ls") == 0)
            {
                ls__(tokens, p + 1);
            }
                else if (strcmp(separated, "pinfo") == 0)
                {
                    pinfo__(tokens, p + 1);
                }
                else
                {
                    printf("wrong command\n");
                }
        }
    label:;
    }
}
// ls ;;
// .. in ls -al