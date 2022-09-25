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

#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "process.h"
#include "history.h"
#include "discover.h"
#include "ioredirection.h"

char current_dir[1000];
char tilda[1000];
int pids_bg[1000];
int pids_fg[1000];
char his_array[1000][1000];
int items_in_history = 0;
FILE *filepntr;
FILE *filepntr1;
int no_of_bg = 0;
int time_ = 0;
char *user_name;
char name[1000];
int x = 0;
int y = 0;
int fg_pid = 0;
int c_flag = 0;

void hiss()
{
    if (items_in_history >= 20)
    {
        for (int i = items_in_history - 20; i < items_in_history; i++)
        {
            fprintf(filepntr1, "%s \n", his_array[i]);
        }
    }
    else
    {
        for (int i = 0; i < items_in_history; i++)
        {
            fprintf(filepntr1, "%s \n", his_array[i]);
        }
    }
    for (int i = 0; i < 1000; i++)
    {
        memset(his_array[i], '\0', sizeof(char) * 1000);
    }
}
void find_tilda(char *relative_curr_dir)
{
    int i = 0;
    int a = strlen(current_dir);
    int b = strlen(tilda);
    if (a < b)
    {
        strcpy(relative_curr_dir, current_dir);
    }
    while (current_dir[i] == tilda[i] && i < b)
    {
        i++;
    }
    if (i != b)
    {
        strcpy(relative_curr_dir, current_dir);
    }
    else if (a == b)
    {
    }
    else
    {
        strcpy(&relative_curr_dir[1], &current_dir[i]);
    }
}
struct data
{
    int a;
    int w;
};
int done[1000];
struct data arr[1000];
int no_of_exited = 0;
void sig_handler(int signum)
{
    int status;
    for (int i = 0; i < no_of_bg; i++)
    {
        if (done[i] == 0)
        {
            if (waitpid(pids_bg[i], &status, WNOHANG) != 0)
            {
                done[i] = 1;
                if (WIFEXITED(status))
                {
                    arr[i].a = 1;
                    arr[i].w = pids_bg[i];
                }
                else
                {
                    arr[i].a = -1;
                    arr[i].w = pids_bg[i];
                }
                no_of_exited++;
                pids_bg[i] = 0;
            }
        }
    }
}
void print_process()
{
    for (int i = 0; i < no_of_exited; i++)
    {
        if (arr[i].a == 1)
        {
            printf("process with pid = %d has ended normally\n", arr[i].w);
        }
        if (arr[i].a == -1)
        {
            printf("process with pid = %d has ended abnormally\n", arr[i].w);
        }
        arr[i].a = 0;
        arr[i].w = 0;
    }
}
void EOF_handle(int signum)
{
    if (signum == SIGUSR1)
    {
        printf("\nEOF\n");
    }
    hiss();
    exit(0);
}
void prompt()
{
    char relative_curr_dir[1000] = "~";
    find_tilda(relative_curr_dir);
    if (strcmp(tilda, current_dir) == 0)
    {
        if (time_ >= 1)
        {
            printf("\033[;36m<%s@%s:~ took %ds>\033[0m", user_name, name, time_);
            time_ = 0;
        }
        else
        {
            printf("\033[;36m<%s@%s:~>\033[0m", user_name, name);
        }
    }
    else
    {
        if (time_ >= 1)
        {
            printf("\033[;36m<%s@%s:\033[0m", user_name, name);
            printf("\033[;33m%s took %ds>\033[0m", relative_curr_dir, time_);
            time_ = 0;
        }
        else
        {
            printf("\033[;36m<%s@%s:\033[0m", user_name, name);
            printf("\033[;33m%s>\033[0m", relative_curr_dir);
        }
    }
}
// void functions(char *);
int function(char *token_space[], int o)
{
    if (strcmp(token_space[0], "pwd") == 0)
    {
        pwd__();
    }
    else if (strcmp(token_space[0], "cd") == 0)
    {

        cd__(token_space, o);
    }
    else if (strcmp(token_space[0], "echo") == 0)
    {
        echo__(token_space, o);
    }
    else if (strcmp(token_space[0], "ls") == 0)
    {
        // puts("hi");
        ls__(token_space, o);
    }
    else if (strcmp(token_space[0], "pinfo") == 0)
    {
        pinfo__(token_space, o);
    }
    else if (strcmp(token_space[0], "history") == 0)
    {
        history__(items_in_history);
        // hiss();
    }
    else if (strcmp(token_space[0], "discover") == 0)
    {

        discover__(token_space, o);
    }
    else if (strcmp(token_space[0], "exit") == 0)
    {
        hiss();
        exit(0);
    }
    // else if (fg__(token_space, o))
    // {
    //     puts("hi");
    //     return 1;
    // }
    else
    {
        return 1;
    }
    return 0;
}
void C_handle(int signum)
{
    // printf("%d %d\n", pids_fg[0], fg_pid);
    if (signum == SIGINT)
    {
        if (x == 0)
        {
            // prompt();
            x = 1;
            return;
        }
        // if (y != 0)
        // {
        //     y = 0;
        //     // hiss();
        //     // return;
        // }
        c_flag++;
        // printf("%d\n", y);
        for (int i = 0; i < y; i++)
        {
            // printf("%d ", pids_fg[i]);
            // pid_t v = getpid();
            // printf("%d\n", v);
            // if (v != fg_pid)
            // if (fg_pid !s= pid_fg[i])
            kill(pids_fg[i], SIGKILL);
        }
        y = 0;
        // printf("%d ", pid_fg[0]);
    }
    // printf("%d ", pid_fg[0]);
}
void Z_handle(int signum)
{
    if (signum == SIGTSTP)
    {
    }
}
int main()
{
    fg_pid = getpid();
    x = 0;
    user_name = getlogin();
    gethostname(name, 1000);
    getcwd(tilda, 1000);
    strcpy(current_dir, tilda);
    items_in_history = 0;
    char space[] = " \n\t";
    char semicolon[] = ";";
    char and_sign[] = "&";
    char prev_[1000] = "\0";
    FILE *filepntr = fopen("history.txt", "r");
    if (filepntr != NULL)
    {
        while (1)
        {
            char uh[1000];
            if (fgets(uh, 1000, filepntr) == NULL)
            {
                break;
            }
            uh[strlen(uh) - 1] = '\0';
            char up[1000];
            strcpy(up, uh);
            char *w = strtok(uh, " /n");
            if (w == NULL)
            {
                continue;
            }
            strcpy(his_array[items_in_history], up);
            items_in_history++;
        }
    }
    filepntr1 = fopen("history.txt", "w");
    signal(SIGCHLD, sig_handler);
    signal(SIGUSR1, EOF_handle);
    signal(SIGINT, C_handle);
    signal(SIGTSTP, Z_handle);
    while (1)
    {
        c_flag = 0;
        // time_ = 0;
        print_process();
        prompt();
        if (no_of_bg == no_of_exited)
        {
            memset(done, 0, sizeof(int) * 1000);
            no_of_exited = 0;
            no_of_bg = 0;
        }
        char *input;
        size_t input_size = 1000;
        input = (char *)malloc(sizeof(char) * 1000);
        input[0] = getchar();
        input[1] = '\0';
        if (input[0] == EOF)
            raise(SIGUSR1);
        if (input[0] == '\n')
            continue;
        char *rest_input;
        getline(&rest_input, &input_size, stdin);
        rest_input[strlen(rest_input) - 1] = '\0';
        strcat(input, rest_input);
        char his_ke_liye_copy[1000];
        strcpy(his_ke_liye_copy, input);
        char *q = strtok(his_ke_liye_copy, space);
        if (items_in_history != 0)
            strcpy(prev_, his_array[items_in_history - 1]);
        if (q != NULL)
        {
            if (strcmp(prev_, input) != 0)
            {
                strcpy(his_array[items_in_history++], input);
            }
        }
        char token_semi[1000][1000];
        int command_semicolon = 0;
        char *semi_tok;
        semi_tok = strtok(input, semicolon);
        if (semi_tok == NULL)
            continue;
        strcpy(token_semi[command_semicolon], semi_tok);
        semi_tok = strtok(NULL, semicolon);
        while (semi_tok != NULL)
        {
            command_semicolon++;
            strcpy(token_semi[command_semicolon], semi_tok);
            semi_tok = strtok(NULL, semicolon);
        }
        for (int i = 0; i <= command_semicolon && c_flag == 0; i++)
        {
            // puts("hi1");
            signal(SIGINT, C_handle);
            char *token_pipe[1000];
            for (int i = 0; i < 10; i++)
            {
                token_pipe[i] = (char *)malloc(sizeof(char) * 1000);
            }

            int command_pipe = 0;
            char *pipe_tok;
            pipe_tok = strtok(token_semi[i], "|");
            if (pipe_tok == NULL)
                continue;
            strcpy(token_pipe[command_pipe], pipe_tok);
            pipe_tok = strtok(NULL, "|");
            while (pipe_tok != NULL)
            {
                command_pipe++;
                strcpy(token_pipe[command_pipe], pipe_tok);
                pipe_tok = strtok(NULL, "|");
            }
            int fd = 0;
            fd = dup(1);
            int org_inp = dup(0);
            // close(STDOUT_FILENO);
            // close(STDIN_FILENO);
            int fildes[2];
            for (int k = 0; k <= command_pipe; k++)
            {
                // create a pipe
                if (pipe(fildes) < 0)
                {
                    perror("Could not create pipe.");
                    exit(1);
                }
                if (k == command_pipe)
                    dup2(fd, 1);
                // int fd1 = 0;
                // fd1 = open(file1, O_CREAT | O_WRONLY | O_APPEND, 0644);
                // dup2(fildes[1], 1);
                int comm_length = strlen(token_pipe[k]);
                int flag_redirection = 0;
                char command[1000] = "\0";
                int command_no = 0;
                char file1[1000] = "\0";
                int file1_no = 0;
                char file2[1000] = "\0";
                int file2_no = 0;
                int flag_append = 0;
                int check = 0;
                for (int j = 0; j < comm_length; j++)
                {
                    if (token_pipe[k][j] == '>')
                    {
                        flag_redirection = 1;
                        if (check == 0)
                        {
                            strncpy(command, token_pipe[k], j);
                            command[j] == '\0';
                            if (token_pipe[k][j + 1] == '>')
                            {
                                flag_append = 1;
                                strcpy(file1, &token_pipe[k][j + 2]);
                            }
                            else
                            {
                                strcpy(file1, &token_pipe[k][j + 1]);
                            }
                        }
                        else
                        {
                            strncpy(file1, &token_pipe[k][check], j - check);
                            file1[j - check] == '\0';
                            if (token_pipe[k][j + 1] == '>')
                            {
                                flag_append = 1;
                                strcpy(file2, &token_pipe[k][j + 2]);
                            }
                            else
                            {
                                strcpy(file2, &token_pipe[k][j + 1]);
                            }
                        }
                        // command_no = j;
                    }
                    else if (token_pipe[k][j] == '<')
                    {
                        flag_redirection = 1;
                        strncpy(command, token_pipe[k], j);
                        command[j] == '\0';
                        check = j + 1;
                        strcpy(file1, &token_pipe[k][check]);
                        // file1[j - check] == '\0';
                        // if (token_pipe[k][j + 1] == '>')
                        // {
                        //     flag_append = 1;
                        //     file
                        // }
                    }
                }
                if (check > 0 && strcmp(file2, "\0") == 0 && command_pipe != 0)
                {
                    if (k != command_pipe)
                        dup2(fildes[1], 1);
                    else if (k == command_pipe)
                        dup2(fd, 1);
                }
                if (flag_redirection)
                {
                    char *token_commands[1000];
                    for (int p = 0; p < 10; p++)
                    {
                        token_commands[p] = (char *)malloc(sizeof(char) * 1000);
                    }
                    int t = 0;
                    char *command_tok;
                    command_tok = strtok(command, space);
                    if (command_tok == NULL)
                        continue;
                    strcpy(token_commands[t], command_tok);
                    command_tok = strtok(NULL, space);
                    while (command_tok != NULL)
                    {
                        t++;
                        strcpy(token_commands[t], command_tok);
                        command_tok = strtok(NULL, space);
                    }
                    char *file1_ = strtok(file1, space);
                    char *file2_ = strtok(file2, space);
                    // puts("hi2");
                    ioredirection__(token_commands, file1_, file2_, check, flag_append, t + 1);
                }
                else
                {
                    // puts("hi");
                    if (k != command_pipe)
                        dup2(fildes[1], 1);
                    else if (k == command_pipe)
                        dup2(fd, 1);
                    int count = 0;
                    for (int s = 0; s < strlen(token_pipe[k]); s++)
                    {
                        if (token_pipe[k][s] == '&')
                        {
                            count++;
                        }
                    }
                    char input_copy[1000];
                    strcpy(input_copy, token_pipe[k]);
                    char *token_and[1000];
                    for (int p = 0; p < 10; p++)
                    {
                        token_and[p] = (char *)malloc(sizeof(char) * 1000);
                    }
                    char *t;
                    t = strtok(input_copy, and_sign);
                    strcpy(token_and[0], t);
                    t = strtok(NULL, and_sign);
                    int p = 0;
                    while (t != NULL)
                    {
                        strcpy(token_and[++p], t);
                        t = strtok(NULL, and_sign);
                    }
                    int bg = 0;
                    if (count == p + 1)
                    {
                        bg = 1;
                    }
                    for (int j = 0; j <= p; j++)
                    {
                        char *token_space[1000];
                        for (int d = 0; d < 10; d++)
                        {
                            token_space[d] = (char *)malloc(sizeof(char *) * 1000);
                        }

                        char input_copy2[1000];
                        strcpy(input_copy2, token_and[j]);
                        char *k;
                        k = strtok(input_copy2, space);
                        if (k == NULL)
                        {
                            break;
                        }
                        strcpy(token_space[0], k);
                        k = strtok(NULL, space);
                        int o = 0;
                        while (k != NULL)
                        {
                            strcpy(token_space[++o], k);
                            k = strtok(NULL, space);
                        }
                        if (bg == 1 || (bg == 0 && j != p))
                        {
                            bg__(token_space, o + 1);
                        }
                        else
                        {
                            if (function(token_space, o + 1))
                            {
                                fg__(token_space, o + 1);
                                // printf("wrong command\n");
                            }
                        }
                    }
                    if (k != command_pipe)
                        dup2(fildes[0], 0);
                    else if (k == command_pipe)
                        dup2(org_inp, 0);
                }
                if (check && strcmp(file2, "\0") == 0 && command_pipe != 0)
                {
                    if (k != command_pipe)
                        dup2(fildes[0], 0);
                    else if (k == command_pipe)
                        dup2(org_inp, 0);
                }
                close(fildes[1]);
            }
            close(STDIN_FILENO);
            dup2(org_inp, 0);
            close(STDOUT_FILENO);
            dup2(fd, 1);
        }
    }
    return 0;
}