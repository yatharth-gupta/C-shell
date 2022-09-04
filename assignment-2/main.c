#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "process.h"
char current_dir[100];
char tilda[100];
int pids[100000] = {0};
int pid_fg;
// int x = 0;
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
void sig_handler(int signum)
{
    int status;
    pid_t pid__ = wait(&status);
    // printf("%d\n", pid_value);
    if (WIFEXITED(status))
    {
        int exit_status = WEXITSTATUS(status);
        // printf("Exit status of the child was %d\n", exit_status);
    }
    // printf("%d\n", pids[pid__]);
    if (pids[pid__])
    {
        // printf("%d\n", pid_fg);
        waitpid(pid_fg, &status, WUNTRACED | WCONTINUED);
        printf("process with pid = %d has ended", pid__);
        // printf("\n");
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
        char tokens_[100][100];
        char *tokens__[100];
        char relative_curr_dir[100] = "~";
        find_tilda(current_dir, tilda, relative_curr_dir);
        printf("\n");
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
        // for (int i = 0; i <= h; i++)
        // {
        //     char input_copy1[100];
        //     strcpy(input_copy1, tokens__[i]);
        //     char *u;
        //     // if (input_copy1[0] == '\0')
        //     // {
        //     //     goto label;
        //     // }
        //     u = strtok(input_copy1, s_);
        //     printf("%s\n", u);
        //     if (u == NULL)
        //     {
        //         printf("syntax error1\n");
        //         goto label;
        //     }
        // }

        for (int i = 0; i <= h; i++)
        {
            int count = 0;
            for (int s = 0; s < strlen(tokens__[i]); s++)
            {
                if (tokens__[i][s] == '&')
                {
                    count++;
                }
            }
            char input_copy[100];
            strcpy(input_copy, tokens__[i]);
            // printf("%s\n", input_copy);
            char *t;
            t = strtok(input_copy, s_);
            // printf("%s\n", t);
            // tokens_[0] = strdup(t);
            // tokens_[0] = (char*)malloc(sizeof(char*));
            strcpy(tokens_[0], t);
            // //     // strcpy(t, tokens[0]);
            // printf("%s\n", tokens_[0]);
            t = strtok(NULL, s_);
            int p = 0;
            while (t != NULL)
            {
                // printf("%s ", t);
                strcpy(tokens_[++p], t);
                t = strtok(NULL, s_);
            }
            // printf("%d\n", p);
            // for (int j = 0; j <= p; j++)
            // {
            //     char input_copy2[100];
            //     strcpy(input_copy2, tokens_[j]);
            //     char *u;
            //     if (input_copy2[0] == '\0')
            //     {
            //         goto label;
            //     }
            //     u = strtok(input_copy2, s);
            //     if (u == NULL)
            //     {
            //         printf("syntax error2\n");
            //         goto label;
            //     }
            // }
            int bg = 0;
            if (count == p + 1)
            {
                bg = 1;
            }
            // printf("%d\n", bg);
            memset(pids, 0, sizeof(int) * 100000);
            for (int j = 0; j <= p; j++)
            {
                char *tokens[100];
                // x = 0;
                char input_copy2[100];
                strcpy(input_copy2, tokens_[j]);
                // printf("%s\n", input_copy2);
                char *k;
                k = strtok(input_copy2, s);
                if (k == NULL)
                {
                    // printf("syntax error3\n");
                    goto label;
                }
                // printf("%s\n", k);
                tokens[0] = strdup(k);
                //     // strcpy(t, tokens[0]);
                // printf("%s\n", tokens[0]);
                k = strtok(NULL, s);
                int o = 0;
                while (k != NULL)
                {
                    // printf("%s ", t);
                    tokens[++o] = strdup(k);
                    k = strtok(NULL, s);
                }
                // char *separated = strtok(tokens_[i], s);
                // printf("%s\n", separated);
                // if (separated == NULL)
                //     continue;
                if (bg == 1 || (bg == 0 && j != p))
                {
                    // puts("hi\n");
                    bg__(tokens, o + 1);
                }
                else
                {
                    if (strcmp(tokens[0], "pwd") == 0)
                    {
                        pwd__();
                    }
                    else if (strcmp(tokens[0], "cd") == 0)
                    {
                        // puts("hi");
                        cd__(tokens, s, current_dir, prev, tilda, temp1);
                    }
                    else if (strcmp(tokens[0], "echo") == 0)
                    {
                        echo__(tokens[0], s);
                    }
                    else if (strcmp(tokens[0], "ls") == 0)
                    {
                        ls__(tokens, o + 1);
                    }
                    else if (strcmp(tokens[0], "pinfo") == 0)
                    {
                        pinfo__(tokens, o + 1);
                    }
                    else if (fg__(tokens, o + 1))
                    {
                    }
                    else
                    {
                        printf("wrong command\n");
                    }
                }
            }
        }
    label:;
        signal(SIGCHLD, sig_handler);
    }
}
// ls ;; , ls ; space (concat a default " ")
// ls &;
// .. in ls -al