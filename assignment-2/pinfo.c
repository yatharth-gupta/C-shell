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
void pinfo__(char *tokens[], int token_size)
{
    if (token_size > 2)
    {
        printf("too many arguments\n");
        return;
    }
    pid_t pid_value;
    if (token_size == 1)
    {
        pid_value = getpid();
    }
    else
    {
        pid_value = atoi(tokens[1]);
    }
    printf("pid : %d\n", pid_value);
    char status_path[1000];
    char buffer[1000];
    sprintf(status_path, "/proc/%d/status", pid_value);
    FILE *file_status = fopen(status_path, "r");
    char status;
    long unsigned memory;
    if (file_status)
    {
        // printf("%s ", file_status);
        // fgets(buffer, 1000, file_status);
        // // printf("%s", buffer);
        // sscanf(buffer, "State:\t%c", &state);
        // printf("Process Status : %c\n", state);
        // fscanf(file_status, "%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &pid_value, &status, &memory);
        // fclose(file_status);
        // printf("pid -- %d\n", pid_value);
        // printf("Process Status -- %c\n", status);
        // printf("Memory -- %lu\n", memory);
    }
    
}