#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#include "process.h"
#include "variables.h"
void bg__(char *tokens[], int token_size)
{
    tokens[token_size] = (char *)NULL;
    pid_t pid_value = fork();
    if (pid_value < 0)
    {
        printf("fork () error\n");
    }
    else if (pid_value == 0)
    {
        setpgrp();
        if (execvp(tokens[0], tokens) == -1)
        {
            printf("execvp() error\n");
        }
    }
    else
    {
        printf("[%d] %d\n", ++no_of_bg, pid_value);
        pids_bg[no_of_bg - 1] = pid_value;
        // printf("%d\n", pids_bg[0]);
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
        // y++;
    }
    else
    {
        time_t initial = time(NULL);
        if (waitpid(pid_value, &wstatus, WUNTRACED | WCONTINUED) == -1)
        {
            printf("waitpid() error");
            return -1;
        }
        time_t ending = time(NULL);
        // y++;
        pids_fg[y++] = pid_value;
        // printf("%d ", pid_fg[y-1]);
        // y++;
        time_ += ending - initial;
    }
    return 1;
}