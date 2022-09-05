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
    // puts("hi\n");
    // printf("%s\n", tokens[token_size]);
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
        // printf("%d\n", pids[pid_value]);
        // signal(SIGCHLD)
        // // if (SIGCHLD)
        // // {
        // //     printf("hi");
        // // }

        // int status;
        // wait(&status);
        // // printf("%d\n", pid_value);
        // if (WIFEXITED(status))
        // {
        //     int exit_status = WEXITSTATUS(status);
        //     printf("Exit status of the child was %d\n", exit_status);
        // }
        // parent does not wait
    }
}
int fg__(char *tokens[], int token_size)
{
    int wstatus;
    tokens[token_size] = NULL;
    // printf("%s\n", tokens[token_size]);
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
            // fprintf(stderr, "execvp() failed!\n");
            return -1;
        }
        // fprintf(stderr, "execvp() failed1!\n");
        // printf("%s with pid = %d")
    }
    else
    {
        if (waitpid(pid_value, &wstatus, WUNTRACED | WCONTINUED) == -1)
        {
            printf("waitpid() error");
            return -1;
        }
        pid_fg = pid_value;
        // signal(SIGCHLD, SIG_IGN);
        // if (wait(&wstatus) == -1)
        // {
        //     printf("waitpid() error");
        //     return -1;
        // }
        // else
        // {
        //     printf("%d\n", wstatus);
        // }
    }
    return 1;
}
// time