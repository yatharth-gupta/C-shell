#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <stdbool.h>
#include <time.h>

#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "variables.h"
#include "pinfo.h"
void find_exe_tilda(char *currunt_dir, char *relative_curr_dir)
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
        strcat(&relative_curr_dir[1], &currunt_dir[i]);
    }
}
void pinfo__(char *tokens[], int token_size)
{
    if (token_size > 2)
    {
        printf("too many arguments\n");
        return;
    }
    if (token_size == 1)
    {
        int pid = getpid();
        printf("pid : %d\n", pid);
        char buf[1000];
        sprintf(buf, "/proc/%d/stat", pid);
        FILE *fd = fopen(buf, "r");
        char number[1000];
        int pgrp, tpgid;
        for (int i = 0; i < 3; ++i)
        {
            fscanf(fd, "%s", number);
        }
        fscanf(fd, "%d", &pgrp);
        fscanf(fd, "%d", &pgrp);
        fscanf(fd, "%d", &tpgid);
        fscanf(fd, "%d", &tpgid);
        fscanf(fd, "%d", &tpgid);
        printf("%d %d", pgrp, tpgid);
        if (tpgid == pgrp)
            printf("Process Status : %s+\n", number);
        else
            printf("Process Status : %s\n", number);
        char buf1[1000];
        sprintf(buf1, "/proc/%d/status", pid);
        FILE *fd1 = fopen(buf1, "r");
        bool g = false;
        char memory[1000];
        while (strcmp("VmSize:", memory) != 0)
        {
            if (fscanf(fd1, "%s", memory) == -1)
            {
                g = true;
                break;
            }
        }
        if (!g)
        {
            fscanf(fd1, "%s", memory);
        }
        else
        {
            strcpy(memory, "0");
        }
        printf("Virtual Memory : %s\n", memory);
        char exe[1000];
        char rel_exe[1000] = "~";
        int read = readlink("/proc/self/exe", exe, 1000);
        exe[read] = '\0';
        find_exe_tilda(exe, rel_exe);
        printf("%s\n", rel_exe);
    }
    else
    {
        int pid = atoi(tokens[1]);
        printf("pid : %d\n", pid);
        char buf[1000];
        sprintf(buf, "/proc/%d/stat", pid);
        FILE *fd = fopen(buf, "r");
        char number[1000];
        int pgrp, tpgid;
        for (int i = 0; i < 3; ++i)
        {
            fscanf(fd, "%s", number);
        }
        fscanf(fd, "%d", &pgrp);
        fscanf(fd, "%d", &pgrp);
        fscanf(fd, "%d", &tpgid);
        fscanf(fd, "%d", &tpgid);
        fscanf(fd, "%d", &tpgid);
        printf("%d %d", pgrp, tpgid);
        if (tpgid == pgrp)
            printf("Process Status : %s+\n", number);
        else
            printf("Process Status : %s\n", number);
        char buf1[1000];
        sprintf(buf1, "/proc/%d/status", pid);
        FILE *fd1 = fopen(buf1, "r");
        bool g = false;
        char memory[1000];
        while (strcmp("VmSize:", memory) != 0)
        {
            if (fscanf(fd1, "%s", memory) == -1)
            {
                g = true;
                break;
            }
        }
        if (!g)
        {
            fscanf(fd1, "%s", memory);
        }
        else
        {
            strcpy(memory, "0");
        }
        printf("Virtual Memory : %s\n", memory);
        char exe[1000];
        char rel_exe[1000] = "~";
        char buf5[1000];
        sprintf(buf5, "/proc/%d/exe", pid);
        int read = readlink(buf5, exe, 1000);
        exe[read] = '\0';
        find_exe_tilda(exe, rel_exe);
        printf("%s\n", rel_exe);
    }
}