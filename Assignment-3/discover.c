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
#include "discover.h"
#include "variables.h"
#include "ls.h"
char initial_dir_path[1000];
char relative_curr_dir[1000];
void find_rel_path(char *dir_path)
{
    int i = 0;
    int b = strlen(initial_dir_path);
    strcpy(relative_curr_dir, "./");
    while (dir_path[i] == initial_dir_path[i] && i < b)
    {
        i++;
    }

    if (strcmp(initial_dir_path, dir_path) == 0)
    {
        strcpy(relative_curr_dir, ".");
    }
    else
    {
        if (dir_path[i + 1] == '.')
        {
            strcpy(relative_curr_dir, &dir_path[i + 1]);
        }
        else
        {
            strcat(relative_curr_dir, &dir_path[i + 1]);
        }
    }
}
void print_discover(char *dir_path, bool d, bool f)
{
    if (d & !f)
    {
        find_rel_path(dir_path);
        printf("%s\n", relative_curr_dir);
        DIR *di;
        struct dirent *dir;
        di = opendir(dir_path);
        while ((dir = readdir(di)) != NULL)
        {
            char tp[1000];
            strcpy(tp, dir_path);
            struct stat s;
            if (dir->d_name[0] != '.')
            {
                strcat(tp, "/");
                strcat(tp, dir->d_name);
                stat(tp, &s);
                if (S_ISDIR(s.st_mode))
                {
                    print_discover(tp, true, false);
                }
            }
        }
    }
    else if (!d & f)
    {
        DIR *di;
        struct dirent *dir;
        di = opendir(dir_path);
        while ((dir = readdir(di)) != NULL)
        {
            char tp[1000];
            strcpy(tp, dir_path);
            struct stat s;
            if (dir->d_name[0] != '.')
            {
                strcat(tp, "/");
                strcat(tp, dir->d_name);
                stat(tp, &s);
                if (S_ISDIR(s.st_mode))
                {
                    print_discover(tp, false, true);
                }
                else
                {
                    find_rel_path(tp);
                    printf("%s\n", relative_curr_dir);
                }
            }
        }
    }
    else if ((d & f) || (!d & !f))
    {
        find_rel_path(dir_path);
        printf("%s\n", relative_curr_dir);
        DIR *di;
        struct dirent *dir;
        di = opendir(dir_path);
        while ((dir = readdir(di)) != NULL)
        {
            char tp[1000];
            strcpy(tp, dir_path);
            struct stat s;
            if (dir->d_name[0] != '.')
            {
                strcat(tp, "/");
                strcat(tp, dir->d_name);
                stat(tp, &s);
                if (S_ISDIR(s.st_mode))
                {
                    print_discover(tp, false, true);
                }
                else
                {
                    find_rel_path(tp);
                    printf("%s\n", relative_curr_dir);
                }
            }
        }
    }
}
void search_file(char *dir_path, char *file)
{
    DIR *di;
    struct dirent *dir;
    di = opendir(dir_path);
    while ((dir = readdir(di)) != NULL)
    {
        char tp[1000];
        strcpy(tp, dir_path);
        struct stat s;
        if (dir->d_name[0] != '.')
        {
            strcat(tp, "/");
            strcat(tp, dir->d_name);
            stat(tp, &s);
            if (S_ISDIR(s.st_mode))
            {
                search_file(tp, file);
            }
            else
            {
                if (strcmp(dir->d_name, file) == 0)
                {
                    find_rel_path(tp);
                    printf("%s\n", relative_curr_dir);
                    return;
                }
            }
        }
    }
}
void discover__(char *tokens[], int token_size)
{
    bool d = false;
    bool f = false;
    char file[1000] = "a";
    char dir_path[1000] = "\0";
    strcpy(dir_path, current_dir);
    strcpy(initial_dir_path, dir_path);
    if (token_size > 5)
    {
        printf("extra arguments\n");
        return;
    }
    int flag = 0;
    for (int i = 1; i < token_size; i++)
    {
        if (strcmp(tokens[i], "-d") == 0)
        {
            d = true;
        }
        else if (strcmp(tokens[i], "-f") == 0)
        {
            f = true;
        }
        else if (tokens[i][0] == '"')
        {
            strcpy(file, &tokens[i][1]);
            file[strlen(file) - 1] = '\0';
        }
        else
        {
            flag = 1;
            if (tokens[i][0] == '~')
            {
                strcpy(dir_path, tilda);
                strcat(dir_path, &tokens[i][1]);
                strcpy(initial_dir_path, dir_path);
            }
            else
            {
                if (tokens[i][0] != '/')
                {
                    strcat(dir_path, "/");
                    strcat(dir_path, tokens[i]);
                }
                else
                {
                    strcpy(dir_path, tokens[i]);
                }
            }
        }
    }
    struct stat s;
    char g[1000];
    strcpy(g, dir_path);
    stat(g, &s);
    if (strcmp(file, "a") != 0)
    {
        search_file(dir_path, file);
    }
    else
    {
        if (S_ISDIR(s.st_mode))
        {
            print_discover(dir_path, d, f);
        }
        else
        {
            printf("no such directory\n");
        }
    }
}