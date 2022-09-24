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
char array[1000][1000];
char array1[1000][1000];
char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
void mode_to_letter(int mode, char *str)
{
    str[0] = '-';
    if (S_ISDIR(mode))
        str[0] = 'd';
    if (mode & S_IRUSR)
        str[1] = 'r';
    else
        str[1] = '-';
    if (mode & S_IWUSR)
        str[2] = 'w';
    else
        str[2] = '-';
    if (mode & S_IXUSR)
        str[3] = 'x';
    else
        str[3] = '-';
    if (mode & S_IRGRP) // judge permission for owner group
        str[4] = 'r';
    else
        str[4] = '-';
    if (mode & S_IWGRP)
        str[5] = 'w';
    else
        str[5] = '-';
    if (mode & S_IXGRP)
        str[6] = 'x';
    else
        str[6] = '-';
    if (mode & S_IROTH) // judge permission for others
        str[7] = 'r';
    else
        str[7] = '-';
    if (mode & S_IWOTH)
        str[8] = 'w';
    else
        str[8] = '-';
    if (mode & S_IXOTH)
        str[9] = 'x';
    else
        str[9] = '-';

    str[10] = '\0';
}
void print_filedata(struct stat f, char *str, char *path, int i)
{
    stat(path, &f);
    struct tm *Date_time = (struct tm *)malloc(sizeof(struct tm));

    mode_to_letter(f.st_mode, str);
    printf("%s", str);
    printf(" %ld", f.st_nlink);
    printf(" %s", getpwuid(f.st_uid)->pw_name);
    printf(" %s", getgrgid(f.st_gid)->gr_name);
    printf(" %ld\t", (long)f.st_size);
    Date_time = localtime(&f.st_mtime);
    printf("%2s %2d %2d:%2d", months[Date_time->tm_mon], Date_time->tm_mday, Date_time->tm_hour, Date_time->tm_min);
    if (i == 1)
        printf(" \033[;32m %s\033[0m\n", path);
    else
        printf(" %s", path);
    printf("\n");
}
void print_color(char *str, int u, int p)
{
    if (str[0] == 'd' && str[9] == 'x' || (str[0] == 'd' && str[9] == '-'))
    {
        printf("\033[;34m %s\033[0m", (p == 0) ? array[u] : array1[u]);
        printf("\n");
    }
    else if (str[0] == '-' && str[9] == 'x')
    {
        printf("\033[;32m %s\033[0m", (p == 0) ? array[u] : array1[u]);
        printf("\n");
    }
    else
    {
        printf("\033[;37m %s\033[0m", (p == 0) ? array[u] : array1[u]);
        printf("\n");
    }
}
void print_directories_al(char *path, bool hidden)
{
    DIR *dir;
    struct dirent *ptr;
    struct stat fst;
    struct stat f;
    char actual[1000];
    strcpy(actual, path);
    char ls_path[1000];
    stat(path, &f);
    char str[12];
    if (!S_ISDIR((f).st_mode))
    {
        mode_to_letter(f.st_mode, str);
        if (f.st_mode & S_IXUSR)
            print_filedata(f, str, actual, 1);
        else
            print_filedata(f, str, actual, 0);
        return;
    }
    struct tm *Date_time = (struct tm *)malloc(sizeof(struct tm));
    dir = opendir(path);
    int i = 0, j = 0, k = 0;
    char tmp[1000];
    int total_block = 0;
    while ((ptr = readdir(dir)) != NULL)
    {
        struct stat sbuf;
        sprintf(array[i], "%s/%s", path, ptr->d_name);
        strcpy(array1[i], ptr->d_name);
        lstat(array[i], &sbuf);
        int nBlocks = sbuf.st_size / 4096;
        if (sbuf.st_size % 4096 > 0)
            nBlocks++;
        if (S_ISLNK(sbuf.st_mode))
            nBlocks = 0;
        total_block += nBlocks;
        i++;
    }
    for (k = 0; k < i; k++) /* Sorting files alphabetically */
        for (j = k + 1; j < i; j++)
        {
            if (strcasecmp(array[k], array[j]) > 0)
            {
                strcpy(tmp, array[k]);
                strcpy(array[k], array[j]);
                strcpy(array[j], tmp);
            }
            if (strcasecmp(array1[k], array1[j]) > 0)
            {
                strcpy(tmp, array1[k]);
                strcpy(array1[k], array1[j]);
                strcpy(array1[j], tmp);
            }
        }
    closedir(dir);
    int u = 0;
    if (!hidden)
        printf("total %d\n", 4 * total_block - 8);
    else
        printf("total %d\n", 4 * total_block);
    while (u < i)
    {
        if (hidden == false)
        {
            if (array1[u][0] == '.')
            {
                u++;
                continue;
            }
        }
        stat(array[u], &fst);
        mode_to_letter(fst.st_mode, str);
        printf("%s", str);                            // file type and permission
        printf(" %ld", fst.st_nlink);                 // file hard links
        printf(" %s", getpwuid(fst.st_uid)->pw_name); // file's owner
        printf(" %s", getgrgid(fst.st_gid)->gr_name); // file's owner group
        printf(" %ld\t", (long)fst.st_size);          // file size
        Date_time = localtime(&fst.st_mtime);         // file time
        printf("%2s %2d %2d:%2d", months[Date_time->tm_mon], Date_time->tm_mday, Date_time->tm_hour, Date_time->tm_min);
        print_color(str, u, 1);
        u++;
    }
    printf("\n");
}
void print_directories(char *direc, bool hidden)
{
    int i = 0, j = 0, k = 0;
    DIR *d;
    struct dirent *dir;
    char tmp[1000];
    d = opendir(direc);
    char ls_path[1000];
    if (chdir(direc) != -1)
    {
        getcwd(ls_path, 1000);
        chdir(current_dir);
        direc = strdup(ls_path);
    }

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            strcpy(array[i], dir->d_name);
            i++;
        }
        for (k = 0; k < i; k++) /* Sorting files alphabetically */
            for (j = k + 1; j < i; j++)
            {
                if (strcasecmp(array[k], array[j]) > 0)
                {
                    strcpy(tmp, array[k]);
                    strcpy(array[k], array[j]);
                    strcpy(array[j], tmp);
                }
            }
        closedir(d);
    }
    char str[12];
    for (int a = 0; a < i; a++)
    {
        struct stat f;
        char tr[1000] = {};
        sprintf(tr, "%s/%s", direc, array[a]);
        stat(tr, &f);
        mode_to_letter(f.st_mode, str);
        if (hidden == false)
        {
            if (array[a][0] == '.')
            {
                a++;
                continue;
            }
        }
        print_color(str, a, 0);
    }
}
void ls__(char *tokens[], int token_size)
{
    if (token_size == 2 && (strcmp(tokens[1], "~") == 0 || strcmp(tokens[1], "~/") == 0))
    {
        print_directories(tilda, false);
    }
    else
    {
        int y = 1;
        bool a = false;
        bool l = false;
        char *paths_[token_size];
        int path_number = 0;
        while (y < token_size) // iterating through all tokens and setting bools a and l. storing paths/names of directories
        {
            if (strcmp(tokens[y], "-a") == 0)
            {
                a = true;
            }
            else if (strcmp(tokens[y], "-l") == 0)
            {
                l = true;
            }
            else if (strcmp(tokens[y], "-al") == 0 || strcmp(tokens[y], "-la") == 0)
            {
                l = true;
                a = true;
            }
            else
            {
                paths_[path_number] = strdup(tokens[y]);
                path_number++;
            }
            y++;
        }
        char tmp[1000];
        for (int k = 0; k < path_number; k++)
        { /* Sorting files alphabetically */
            for (int j = k + 1; j < path_number; j++)
            {
                if (strcasecmp(paths_[k], paths_[j]) > 0)
                {
                    strcpy(tmp, paths_[k]);
                    strcpy(paths_[k], paths_[j]);
                    strcpy(paths_[j], tmp);
                }
            }
        }
        if (path_number == 0) // no files or directories are given as inputs
        {
            if (!l)
                print_directories(current_dir, a);
            else
                print_directories_al(current_dir, a);
        }
        for (int i = 0; i < path_number; i++) // considering each file one by one
        {
            if (path_number != 1)
            {
                printf("%s:\n", paths_[i]); // to distinguish between directories
            }
            if (strcmp(paths_[i], "~") == 0 || strcmp(paths_[i], "~/") == 0)
            {
                strcpy(paths_[i], tilda);
            }
            struct stat s;
            char g[1000];
            if (paths_[i][0] != '/')
            {
                sprintf(g, "%s/%s", current_dir, paths_[i]);
            }
            else
            {
                strcpy(g, paths_[i]);
            }
            if (stat(g, &s) == 0)
            {
                if (S_ISDIR(s.st_mode)) // it's a directory
                {
                    if (!l)
                        print_directories(g, a);
                    else
                    {
                        print_directories_al(g, a);
                    }
                }
                else if (s.st_mode & S_IXUSR)
                {
                    if (!l)
                        printf("\033[;32m %s\033[0m\n", paths_[i]);
                    else
                    {
                        print_directories_al(g, a);
                    }
                }
                else if (s.st_mode & S_IFREG) // it's a file
                {
                    if (!l)
                        printf("%s\n", paths_[i]);
                    else
                        print_directories_al(g, a);
                }
                else
                {
                    printf("neither file nor direcrtory");
                }
            }
            else
            {
                printf("no such file or directory \n");
            }
        }
    }
}