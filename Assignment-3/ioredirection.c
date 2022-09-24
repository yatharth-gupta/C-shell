#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "ioredirection.h"
#include "variables.h"
void ioredirection__(char *command[], char *file1, char *file2, int check, int flag_append, int size)
{
    int fd, fd1;
    if (check != 0 && file2 == NULL)
    {
        fd = dup(0);
        fd1 = open(file1, O_CREAT | O_RDONLY, 0644);
        close(0);
        dup2(fd1, 0);
        // int pid = fork();
        // if (pid == 0)
        // {
        // char *arg[] = {command, file1, NULL};
        // command[size] = file1;
        if (function(command, size))
        {
            command[size] = NULL;
            if (execvp(command[0], command) == -1)
            {
                printf("error : no such command or file exists\n");
            }
        }
        // }
        // else
        // {
        // goto re;
        close(fd1);
        dup2(fd, 0);
        close(fd);
        return;
        // }
    }
    else if (check == 0 && file2 == NULL)
    {
        int fd = 0;
        int fd1 = 0;
        // char *arg[] = {command, file1, NULL};
        if (flag_append == 1)
        {
            fd = dup(1);
            close(STDOUT_FILENO);
            fd1 = open(file1, O_CREAT | O_WRONLY | O_APPEND, 0644);
            dup2(fd1, 1);
        }
        else
        {
            fd = dup(STDOUT_FILENO);
            close(STDOUT_FILENO);
            fd1 = open(file1, O_CREAT | O_TRUNC | O_WRONLY, 0644);
            dup2(fd1, 1);
        }
        // int pid = fork();
        // if (pid == 0)
        // {
        // char *arg[] = {command, file1, NULL};
        // command[size] = file1;
        if (function(command, size))
        {
            command[size] = NULL;
            if (execvp(command[0], command) == -1)
            {
                printf("error : no such command or file exists\n");
            }
        }
        // }
        // else
        // {
        // goto re;
        close(fd1);
        dup2(fd, 1);
        close(fd);
        return;
        // }
    }
    else if (file2 != NULL)
    {
        int fd, fd__, fd1, fd2;
        // char *arg[] = {command, file1, file2, NULL};
        if (flag_append == 1)
        {
            fd = dup(1);
            close(STDOUT_FILENO);
            fd1 = open(file2, O_CREAT | O_WRONLY | O_APPEND, 0644);
            dup2(fd1, 1);
            fd__ = dup(0);
            fd2 = open(file1, O_CREAT | O_RDONLY, 0644);
            close(0);
            dup2(fd2, 0);
        }
        else
        {
            fd = dup(1);
            close(STDOUT_FILENO);
            fd1 = open(file2, O_CREAT | O_TRUNC | O_WRONLY, 0644);
            dup2(fd1, 1);
            fd__ = dup(0);
            fd2 = open(file1, O_CREAT | O_RDONLY, 0644);
            close(0);
            dup2(fd2, 0);
        }
        // int pid = fork();
        // if (pid == 0)
        // {
        // char *arg[] = {command, file1, NULL};
        // command[size++] = file1;
        // command[size++] = file2;
        if (function(command, size))
        {
            command[size] = NULL;
            if (execvp(command[0], command) == -1)
            {
                printf("error : no such command or file exists\n");
            }
        }
        // }
        // else
        // {
        // goto re;
        close(fd1);
        dup2(fd, 1);
        close(fd);
        close(fd2);
        dup2(fd__, 0);
        close(fd__);
        return;
        // }
    }
}
