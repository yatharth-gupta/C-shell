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

void mode_to_letter(int mode, char *str)
{
    str[0] = '-';

    // judge file type
    if (S_ISDIR(mode))
        str[0] = 'd';
    if (S_ISCHR(mode))
        str[0] = 'c';
    if (S_ISBLK(mode))
        str[0] = 'b';

    // judge permission for owner
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

    // judge permission for owner group
    if (mode & S_IRGRP)
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

    // judge permission for others
    if (mode & S_IROTH)
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
void print_filedata(struct stat f, char *str, char *path)
{
    stat(path, &f);
    struct tm *mytime = (struct tm *)malloc(sizeof(struct tm));
    // permission information
    mode_to_letter(f.st_mode, str);
    // file type and permission
    printf("%s", str);
    // file hard links
    printf(" %ld", f.st_nlink);
    // file's owner
    printf(" %s", getpwuid(f.st_uid)->pw_name);
    // file's owner group
    printf(" %s", getgrgid(f.st_gid)->gr_name);
    // file size
    printf(" %ld", (long)f.st_size);
    // file time
    mytime = localtime(&f.st_mtime);
    printf(" %d-%02d-%02d %02d:%02d", mytime->tm_year + 1900, mytime->tm_mon + 1, mytime->tm_mday, mytime->tm_hour, mytime->tm_min);
    // file name
    printf(" %s", path);
    printf("\n");
}
void print_directories_al(char *path, bool hidden)
{
    char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    DIR *dir;
    struct dirent *ptr;
    struct stat fst;
    struct stat f;
    char *actual = strdup(path);
    char ls_path[1000];
    if (chdir(path) != -1)
    {
        getcwd(ls_path, 1000);
        chdir(current_dir);
        path = strdup(ls_path);
    }
    else
    {
        printf("no such file or directory\n");
    }

    stat(path, &f);
    // stat(path, &fst);
    char str[12];
    // if (f.st_mode & S_IFMT & S_IFREG)
    // {
    //     mode_to_letter(fst.st_mode, str);
    // }
    if (!S_ISDIR((f).st_mode))
    {
        mode_to_letter(f.st_mode, str);
        print_filedata(f, str, actual);
        return;
    }
    else
    {
        printf("%s:\n", actual);
    }
    // puts("reached");
    // void mode_to_letter(int mode, char *str);
    // puts("reached");
    // define struct stat
    struct tm *mytime = (struct tm *)malloc(sizeof(struct tm));
    dir = opendir(path);
    // skip . and ..
    readdir(dir);
    // readdir(dir);
    // puts("reached");
    char array[50][1000] = {};
    char array1[50][1000] = {};
    int i = 0, j = 0, k = 0;
    char tmp[1000];
    // puts("reached");
    while ((ptr = readdir(dir)) != NULL)
    {
        // printf("~~~~%s\n",ptr->d_name);
        sprintf(array[i], "%s/%s", path, ptr->d_name);
        strcpy(array1[i], ptr->d_name);
        // strcpy(array[i], );
        i++;
    }
    // puts("reached");
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
    // puts("reached");
    // printf("%d %d\n",u,i);
    while (u < i)
    {
        // printf("###%s\n", array1[u]);
        if (hidden == false)
        {
            if (array1[u][0] == '.')
            {
                u++;
                continue;
            }
        }
        // char ls_path[1000];
        // if (chdir(array[u]) != -1)
        // {
        //     getcwd(ls_path, 1000);
        //     chdir(current_dir);
        // }
        // strcpy(array[u], ls_path);
        // // printf("hi\n");
        // stat(array[u], &fst);
        stat(array[u], &fst);
        // printf("hi\n");
        // permission information
        mode_to_letter(fst.st_mode, str);
        // printf("csdvsd--- %s\n", array[u]);
        // puts("hi");
        // file type and permission
        printf("%s", str);
        // file hard links
        printf(" %ld", fst.st_nlink);
        // file's owner
        printf(" %s", getpwuid(fst.st_uid)->pw_name);
        // file's owner group
        printf(" %s", getgrgid(fst.st_gid)->gr_name);
        // file size
        printf(" %ld\t", (long)fst.st_size);
        // file time
        mytime = localtime(&fst.st_mtime);
        printf("%2s %2d %2d:%2d", months[mytime->tm_mon], mytime->tm_mday, mytime->tm_hour, mytime->tm_min);
        // file name
        // struct stat sb;
        if (str[0] == 'd' && str[9] == 'x')
        {
            printf("\033[;36m %s\033[0m", array1[u]);
            printf("\n");
        }
        else if (str[0] == '-' && str[9] == 'x')
        {
            printf("\033[;32m %s\033[0m", array1[u]);
            printf("\n");
        }
        else
        {
            printf("\033[;37m %s\033[0m", array1[u]);
            printf("\n");
        }
        // printf("%s is%s executable.\n", argv[1], stat(argv[1], &sb) == 0 && sb.st_mode & S_IXUSR ? "" : " not");
        // printf(" %s", array1[u]);
        // printf("\n");
        u++;
        // printf("%d\n", u);
    }
    printf("\n");
}
void print_directories(char *direc, bool hidden)
{
    char array[1000][1000] = {};
    int i = 0, j = 0, k = 0;
    DIR *d;
    struct dirent *dir;
    char tmp[1000];
    d = opendir(direc);
    // printf("d: %d \n", d);
    char ls_path[1000];
    if (chdir(direc) != -1)
    {
        getcwd(ls_path, 1000);
        chdir(current_dir);
        // printf("%s\n", ls_path);
        direc = strdup(ls_path);
    }
    else
    {
        printf("no such file or directory\n");
    }

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // printf("%s\n",dir->d_name);
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
        // printf("%s\n",array[a])
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
        // printf("%s\n", str);
        if (str[0] == 'd' && str[9] == 'x')
        {
            printf("\033[;36m %s\033[0m", array[a]);
            printf("\n");
        }
        else if (str[0] == '-' && str[9] == 'x')
        {
            printf("\033[;32m %s\033[0m", array[a]);
            printf("\n");
        }
        else
        {
            puts("hi");
            printf("\033[;37m %s\033[0m", array[a]);
            printf("\n");
        }
    }
    printf("\n");
}
void ls__(char *tokens[], int token_size)
{
    // printf("%s", tokens[1]);
    // printf("%d",token_size);
    // struct dirent *d;
    // char *temp_curr = strdup(current_dir);
    // DIR *dh = opendir(temp_curr);
    // printf("%d", (strcmp(tokens[1], "..") == 0));
    if (token_size == 1 || (token_size == 2 && (strcmp(tokens[1], ".") == 0)))
    {
        // closedir(dh);
        print_directories(current_dir, false);
    }
    else if ((token_size == 2 && (strcmp(tokens[1], "..") == 0)))
    {
        char pre[1000];
        cut_(current_dir, pre);
        // printf("%s\n", pre);
        print_directories(pre, false);
    }
    else if (token_size == 2 && (strcmp(tokens[1], "~") == 0 || strcmp(tokens[1], "~/") == 0))
    {
        // closedir(dh);
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
            // printf("%s\n", tokens[y]);
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
            if (stat(paths_[i], &s) == 0)
            {
                if (s.st_mode & S_IFDIR) // it's a directory
                {
                    if (!l)
                        print_directories(paths_[i], a);
                    else
                        print_directories_al(paths_[i], a);
                }
                else if (s.st_mode & S_IFREG) // it's a file
                {
                    if (!l)
                        printf("%s\n", paths_[i]);
                    else
                        print_directories_al(paths_[i], a);
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
// all file first in acending and the directories in acending
//..//