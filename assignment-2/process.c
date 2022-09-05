#include "process.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
void bg__(char *tokens[], int token_size)
{
    // puts("hi\n");
    tokens[token_size] = (char *)NULL;
    pid_t pid_value = fork();
    if (pid_value < 0)
    {
        printf("fork () error\n");
    }
    else if (pid_value == 0)
    {
        if (execvp(tokens[0], tokens) == -1)
        {
            printf("execvp() error\n");
        }
    }
    else
    {
        printf("[%d] %d\n", ++x, pid_value);
        pids[x-1] = pid_value;
    }
}
int fg__(char *tokens[], int token_size)
{
    int wstatus;
    tokens[token_size] = NULL;
    pid_t pid_value = fork();
    if (pid_value < 0)
    {
        printf("fork () error\n");
        return -1;
    }
    else if (pid_value == 0)
    {
        if (execvp(tokens[0], tokens) == -1)
        {
            printf("execvp() error\n");
            return -1;
        }
    }
    else
    {
        if (waitpid(pid_value, &wstatus, WUNTRACED | WCONTINUED) == -1)
        {
            printf("waitpid() error");
            return -1;
        }
        pid_fg = pid_value;
    }
    return 1;
}
// time