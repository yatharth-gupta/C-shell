// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
// #include <dirent.h>
// #include <errno.h>
// #include <sys/types.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <sys/wait.h>
// #include <fcntl.h>

// #include "echo.h"
// #include "pwd.h"
// #include "cd.h"
// #include "ls.h"
// #include "pinfo.h"
// #include "process.h"
// #include "history.h"
// #include "discover.h"
// char current_dir[100];
// char tilda[100];
// int pids[100000] = {0};
// int pid_fg;
// char his_array[1000][1000];
// // int x = 0;
// void find_tilda(char *currunt_dir, char *tilda, char *relative_curr_dir)
// {
//     int i = 0;
//     int a = strlen(currunt_dir);
//     int b = strlen(tilda);
//     if (a < b)
//     {
//         strcpy(relative_curr_dir, currunt_dir);
//     }
//     while (currunt_dir[i] == tilda[i] && i < b)
//     {
//         i++;
//     }
//     if (i != b)
//     {
//         strcpy(relative_curr_dir, currunt_dir);
//     }
//     else if (a == b)
//     {
//     }
//     else
//     {
//         strcpy(&relative_curr_dir[1], &currunt_dir[i]);
//     }
// }
// void sig_handler(int signum)
// {
//     int status;
//     pid_t pid__ = wait(&status);
//     // printf("%d\n", pid_value);
//     if (WIFEXITED(status))
//     {
//         int exit_status = WEXITSTATUS(status);
//         // printf("Exit status of the child was %d\n", exit_status);
//     }
//     // printf("%d\n", pids[pid__]);
//     if (pids[pid__])
//     {
//         // printf("%d\n", pid_fg);
//         waitpid(pid_fg, &status, WUNTRACED | WCONTINUED);
//         printf("process with pid = %d has ended", pid__);
//         // printf("\n");
//     }
// }
// int main()
// {
//     char *user_name = getlogin();
//     char name[100];
//     gethostname(name, 100);
//     char temp[100];
//     char *separated = "\0";
//     getcwd(tilda, 100);
//     strcpy(current_dir, tilda);
//     char prev[100] = "\0";
//     char s[] = " \t\n";
//     char s_[] = "&";
//     char s__[] = ";";
//     int items_in_history = 0;
//     char prev_[1000] = "\0";
//     FILE *filepntr;
//     FILE *filepntr1 = fopen("history.txt", "r");
//     while (1)
//     {
//         // puts("hi");
//         char uh[100];
//         if (fgets(uh, 1000, filepntr1) == NULL)
//         {
//             break;
//         }
//         char up[100];
//         strcpy(up, uh);
//         char *w = strtok(uh, s);
//         if (w == NULL)
//         {
//             break;
//         }
//         strcpy(his_array[items_in_history], up);
//         // puts("hi");

//         items_in_history++;
//     }
//     filepntr = fopen("history.txt", "w");
//     while (1)
//     {
//         signal(SIGCHLD, sig_handler);
//         char temp1[100] = "\0";
//         char tokens_[100][100];
//         char tokens__[100][100];
//         char relative_curr_dir[100] = "~";
//         find_tilda(current_dir, tilda, relative_curr_dir);
//         // printf("\n");
//         if (strcmp(tilda, current_dir) == 0)
//         {
//             printf("\033[;36m<%s@%s:~>\033[0m", user_name, name);
//         }
//         else
//         {
//             printf("\033[;36m<%s@%s:\033[0m", user_name, name);
//             printf("\033[;33m%s>\033[0m", relative_curr_dir);
//         }
//         // puts("hi");
//         char *input;
//         size_t input_size = 100;
//         getline(&input, &input_size, stdin);
//         input[strlen(input) - 1] = '\0';
//         // puts("hi");
//         // char *his_ke_liye_copy = strdup(input);
//         char his_ke_liye_copy[1000];
//         strcpy(his_ke_liye_copy, input);
//         char *q = strtok(his_ke_liye_copy, s);
//         // printf("%s\n", q);
//         if (items_in_history != 0)
//             strcpy(prev_, his_array[items_in_history - 1]);
//         // puts("hi");
//         if (q != NULL)
//         {
//             // puts("hi");
//             if (strcmp(prev_, input) != 0)
//             {
//                 // puts("hi");
//                 strcpy(his_array[items_in_history++], input);
//                 // puts("hi");
//             }
//         }
//         // puts("hi");
//         // printf("%s\n", input);
//         int h = 0;
//         char *g;
//         g = strtok(input, s__);
//         if (g == NULL)
//         {
//             continue;
//         }
//         // printf("%s\n", g);
//         strcpy(tokens__[h], g);

//         g = strtok(NULL, s__);
//         while (g != NULL)
//         {
//             // printf("%s ", g);
//             h++;
//             strcpy(tokens__[h], g);
//             // printf("%d %s\n", h, tokens__[h]);
//             g = strtok(NULL, s__);
//         }
//         // printf("%d\n", h);
//         // for (int i = 0; i <= h; i++)
//         // {
//         //     char input_copy1[100];
//         //     strcpy(input_copy1, tokens__[i]);
//         //     char *u;
//         //     // if (input_copy1[0] == '\0')
//         //     // {
//         //     //     goto label;
//         //     // }
//         //     u = strtok(input_copy1, s_);
//         //     printf("%s\n", u);
//         //     if (u == NULL)
//         //     {
//         //         printf("syntax error1\n");
//         //         goto label;
//         //     }
//         // }
//         memset(pids, 0, sizeof(int) * 100000);
//         for (int i = 0; i <= h; i++)
//         {
//             int count = 0;
//             // printf("%s\n", tokens__[i]);
//             for (int s = 0; s < strlen(tokens__[i]); s++)
//             {
//                 if (tokens__[i][s] == '&')
//                 {
//                     count++;
//                 }
//             }
//             char input_copy[100];
//             strcpy(input_copy, tokens__[i]);
//             // printf("%s\n", input_copy);
//             char *t;
//             t = strtok(input_copy, s_);
//             // printf("%s\n", t);
//             // tokens_[0] = strdup(t);
//             // tokens_[0] = (char*)malloc(sizeof(char*));
//             strcpy(tokens_[0], t);
//             // //     // strcpy(t, tokens[0]);
//             // printf("%s\n", tokens_[0]);
//             t = strtok(NULL, s_);
//             int p = 0;
//             while (t != NULL)
//             {
//                 // printf("%s ", t);
//                 strcpy(tokens_[++p], t);
//                 t = strtok(NULL, s_);
//             }
//             // printf("%d\n", p);
//             // for (int j = 0; j <= p; j++)
//             // {
//             //     char input_copy2[100];
//             //     strcpy(input_copy2, tokens_[j]);
//             //     char *u;
//             //     if (input_copy2[0] == '\0')
//             //     {
//             //         goto label;
//             //     }
//             //     u = strtok(input_copy2, s);
//             //     if (u == NULL)
//             //     {
//             //         printf("syntax error2\n");
//             //         goto label;
//             //     }
//             // }
//             int bg = 0;
//             if (count == p + 1)
//             {
//                 bg = 1;
//             }
//             // printf("%d\n", bg);
//             for (int j = 0; j <= p; j++)
//             {
//                 // puts("hi`");
//                 char *tokens[100];
//                 // x = 0;
//                 for (int d = 0; d < 100; d++)
//                 {
//                     tokens[d] = (char *)malloc(sizeof(char *) * 100);
//                 }

//                 char input_copy2[100];
//                 strcpy(input_copy2, tokens_[j]);
//                 // printf("%s\n", input_copy2);
//                 char *k;
//                 k = strtok(input_copy2, s);
//                 if (k == NULL)
//                 {
//                     // printf("syntax error3\n");
//                     goto label;
//                 }
//                 // printf("%s\n", k);
//                 strcpy(tokens[0], k);
//                 //     // strcpy(t, tokens[0]);
//                 // printf("%s\n", tokens[0]);
//                 k = strtok(NULL, s);
//                 int o = 0;
//                 while (k != NULL)
//                 {
//                     // printf("%s ", t);
//                     strcpy(tokens[++o], k);
//                     k = strtok(NULL, s);
//                 }
//                 // char *separated = strtok(tokens_[i], s);
//                 // printf("%s\n", separated);
//                 // if (separated == NULL)
//                 //     continue;
//                 if (bg == 1 || (bg == 0 && j != p))
//                 {
//                     // puts("hi\n");
//                     bg__(tokens, o + 1);
//                 }
//                 else
//                 {
//                     if (strcmp(tokens[0], "pwd") == 0)
//                     {
//                         pwd__();
//                     }
//                     else if (strcmp(tokens[0], "cd") == 0)
//                     {
//                         // puts("hi");
//                         cd__(tokens, s, current_dir, prev, tilda, temp1, o + 1);
//                     }
//                     else if (strcmp(tokens[0], "echo") == 0)
//                     {
//                         echo__(tokens[0], s);
//                     }
//                     else if (strcmp(tokens[0], "ls") == 0)
//                     {
//                         // puts("hi");
//                         ls__(tokens, o + 1);
//                     }
//                     else if (strcmp(tokens[0], "pinfo") == 0)
//                     {
//                         pinfo__(tokens, o + 1);
//                     }
//                     else if (strcmp(tokens[0], "history") == 0)
//                     {
//                         history__(items_in_history);
//                     }
//                     else if (strcmp(tokens[0], "exit") == 0)
//                     {
//                         // puts("hi");
//                         goto his;
//                     }
//                     else if (strcmp(tokens[0], "discover") == 0)
//                     {
//                         // puts("hi");
//                         discover__(tokens, o + 1);
//                     }
//                     else if (fg__(tokens, o + 1))
//                     {
//                     }
//                     else
//                     {
//                         printf("wrong command\n");
//                     }
//                 }
//             }
//         }
//     label:;
//     }
// his:;
//     if (items_in_history >= 20)
//     {
//         for (int i = items_in_history - 20; i < items_in_history; i++)
//         {
//             fprintf(filepntr, "%s \n", his_array[i]);
//         }
//     }
//     else
//     {
//         for (int i = 0; i < items_in_history; i++)
//         {
//             fprintf(filepntr, "%s \n", his_array[i]);
//         }
//     }
//     for (int i = 0; i < 1000; i++)
//     {
//         memset(his_array[i], '\0', sizeof(char) * 1000);
//     }
//     return 0;
// }
// // ls ;; , ls ; space (concat a default " ")
// // ls &;
// // .. in ls -al

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

#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "process.h"
#include "history.h"
#include "discover.h"
char current_dir[100];
char tilda[100];
int pids[100];
int done[100];
int pid_fg;
char his_array[1000][1000];
int x = 0;
void find_tilda(char *currunt_dir, char *tilda, char *relative_curr_dir)
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
        strcpy(&relative_curr_dir[1], &currunt_dir[i]);
    }
}
void sig_handler(int signum)
{
    int status;
    for (int i = 0; i < x; i++)
    {
        // printf("%d\n", i);
        if (done[i] == 0)
        {
            if (waitpid(pids[i], &status, WNOHANG) != 0)
            {
                done[i] = 1;
                if (WIFEXITED(status))
                {

                    printf("process with pid = %d has ended normally\n", pids[i]);

                    // printf("Exit status of the child was %d\n", exit_status);
                }
                else
                {
                    printf("process with pid = %d has ended abnormally\n", pids[i]);
                }
            }
        }
    }
    // e = 0;
    // x=0;

    // pid_t pid__ = wait(&status);
    // // printf("%d\n", pid_value);
    // if (WIFEXITED(status))
    // {
    //     int exit_status = WEXITSTATUS(status);
    //     // printf("Exit status of the child was %d\n", exit_status);
    // }
    // // printf("%d\n", pids[pid__]);
    // if (pids[pid__])
    // {
    //     // printf("%d\n", pid_fg);
    //     if (waitpid(pid_fg, &status, WNOHANG) != 0)
    //         printf("process with pid = %d has ended", pid__);
    //     // printf("\n");
    // }
}
int main()
{
    char *user_name = getlogin();
    char name[100];
    gethostname(name, 100);
    char temp[100];
    char *separated = "\0";
    getcwd(tilda, 100);
    strcpy(current_dir, tilda);
    char prev[100] = "\0";
    char s[] = " \t\n";
    char s_[] = "&";
    char s__[] = ";";
    int items_in_history = 0;
    char prev_[1000] = "\0";
    FILE *filepntr;
    FILE *filepntr1 = fopen("history.txt", "r");
    while (1)
    {
        // puts("hi");
        memset(pids, 0, sizeof(int) * 100);
        memset(done, 0, sizeof(int) * 100);
        x = 0;
        char uh[100];
        if (fgets(uh, 1000, filepntr1) == NULL)
        {
            break;
        }
        uh[strlen(uh) - 1] = '\0';
        char up[100];
        strcpy(up, uh);
        char *w = strtok(uh, " /n");
        if (w == NULL)
        {
            continue;
        }
        strcpy(his_array[items_in_history], up);
        // puts("hi");
        // printf("%s\n", his_array[items_in_history]);

        items_in_history++;
    }
    filepntr = fopen("history.txt", "w");
    while (1)
    {
        signal(SIGCHLD, sig_handler);
        char temp1[100] = "\0";
        char tokens_[100][100];
        char tokens__[100][100];
        char relative_curr_dir[100] = "~";
        find_tilda(current_dir, tilda, relative_curr_dir);
        // printf("\n");
        if (strcmp(tilda, current_dir) == 0)
        {
            printf("\033[;36m<%s@%s:~>\033[0m", user_name, name);
        }
        else
        {
            printf("\033[;36m<%s@%s:\033[0m", user_name, name);
            printf("\033[;33m%s>\033[0m", relative_curr_dir);
        }
        // puts("hi");
        char *input;
        size_t input_size = 100;
        getline(&input, &input_size, stdin);
        input[strlen(input) - 1] = '\0';
        // puts("hi");
        // char *his_ke_liye_copy = strdup(input);
        char his_ke_liye_copy[1000];
        strcpy(his_ke_liye_copy, input);
        char *q = strtok(his_ke_liye_copy, s);
        // printf("%s\n", q);
        if (items_in_history != 0)
            strcpy(prev_, his_array[items_in_history - 1]);
        // puts("hi");
        if (q != NULL)
        {
            // puts("hi");
            if (strcmp(prev_, input) != 0)
            {
                // puts("hi");
                strcpy(his_array[items_in_history++], input);
                // puts("hi");
            }
        }
        // puts("hi");
        // printf("%s\n", input);
        int h = 0;
        char *g;
        g = strtok(input, s__);
        if (g == NULL)
        {
            continue;
        }
        // printf("%s\n", g);
        strcpy(tokens__[h], g);

        g = strtok(NULL, s__);
        while (g != NULL)
        {
            // printf("%s ", g);
            h++;
            strcpy(tokens__[h], g);
            // printf("%d %s\n", h, tokens__[h]);
            g = strtok(NULL, s__);
        }
        // printf("%d\n", h);
        // for (int i = 0; i <= h; i++)
        // {
        //     char input_copy1[100];
        //     strcpy(input_copy1, tokens__[i]);
        //     char *u;
        //     // if (input_copy1[0] == '\0')
        //     // {
        //     //     goto label;
        //     // }
        //     u = strtok(input_copy1, s_);
        //     printf("%s\n", u);
        //     if (u == NULL)
        //     {
        //         printf("syntax error1\n");
        //         goto label;
        //     }
        // }

        for (int i = 0; i <= h; i++)
        {
            int count = 0;
            // printf("%s\n", tokens__[i]);
            for (int s = 0; s < strlen(tokens__[i]); s++)
            {
                if (tokens__[i][s] == '&')
                {
                    count++;
                }
            }
            char input_copy[100];
            strcpy(input_copy, tokens__[i]);
            // printf("%s\n", input_copy);
            char *t;
            t = strtok(input_copy, s_);
            // printf("%s\n", t);
            // tokens_[0] = strdup(t);
            // tokens_[0] = (char*)malloc(sizeof(char*));
            strcpy(tokens_[0], t);
            // //     // strcpy(t, tokens[0]);
            // printf("%s\n", tokens_[0]);
            t = strtok(NULL, s_);
            int p = 0;
            while (t != NULL)
            {
                // printf("%s ", t);
                strcpy(tokens_[++p], t);
                t = strtok(NULL, s_);
            }
            // printf("%d\n", p);
            // for (int j = 0; j <= p; j++)
            // {
            //     char input_copy2[100];
            //     strcpy(input_copy2, tokens_[j]);
            //     char *u;
            //     if (input_copy2[0] == '\0')
            //     {
            //         goto label;
            //     }
            //     u = strtok(input_copy2, s);
            //     if (u == NULL)
            //     {
            //         printf("syntax error2\n");
            //         goto label;
            //     }
            // }
            int bg = 0;
            if (count == p + 1)
            {
                bg = 1;
            }
            // printf("%d\n", bg);
            memset(pids, 0, sizeof(int) * 100000);
            for (int j = 0; j <= p; j++)
            {
                // puts("hi`");
                char *tokens[100];
                // x = 0;
                for (int d = 0; d < 100; d++)
                {
                    tokens[d] = (char *)malloc(sizeof(char *) * 100);
                }

                char input_copy2[100];
                strcpy(input_copy2, tokens_[j]);
                // printf("%s\n", input_copy2);
                char *k;
                k = strtok(input_copy2, s);
                if (k == NULL)
                {
                    // printf("syntax error3\n");
                    goto label;
                }
                // printf("%s\n", k);
                strcpy(tokens[0], k);
                //     // strcpy(t, tokens[0]);
                // printf("%s\n", tokens[0]);
                k = strtok(NULL, s);
                int o = 0;
                while (k != NULL)
                {
                    // printf("%s ", t);
                    strcpy(tokens[++o], k);
                    k = strtok(NULL, s);
                }
                // char *separated = strtok(tokens_[i], s);
                // printf("%s\n", separated);
                // if (separated == NULL)
                //     continue;
                if (bg == 1 || (bg == 0 && j != p))
                {
                    // puts("hi\n");
                    bg__(tokens, o + 1);
                }
                else
                {
                    if (strcmp(tokens[0], "pwd") == 0)
                    {
                        pwd__();
                    }
                    else if (strcmp(tokens[0], "cd") == 0)
                    {
                        // puts("hi");
                        cd__(tokens, prev, temp1, o + 1);
                    }
                    else if (strcmp(tokens[0], "echo") == 0)
                    {
                        echo__(tokens, o + 1);
                    }
                    else if (strcmp(tokens[0], "ls") == 0)
                    {
                        // puts("hi");
                        ls__(tokens, o + 1);
                    }
                    else if (strcmp(tokens[0], "pinfo") == 0)
                    {
                        pinfo__(tokens, o + 1);
                    }
                    else if (strcmp(tokens[0], "history") == 0)
                    {
                        history__(items_in_history);
                    }
                    else if (strcmp(tokens[0], "discover") == 0)
                    {
                        // puts("hi");
                        discover__(tokens, o + 1);
                    }
                    else if (strcmp(tokens[0], "exit") == 0)
                    {
                        // puts("hi");
                        goto his;
                    }
                    else if (fg__(tokens, o + 1))
                    {
                    }
                    else
                    {
                        printf("wrong command\n");
                    }
                }
            }
        }
    label:;
    }
his:;
    if (items_in_history >= 20)
    {
        for (int i = items_in_history - 20; i < items_in_history; i++)
        {
            fprintf(filepntr, "%s \n", his_array[i]);
        }
    }
    else
    {
        for (int i = 0; i < items_in_history; i++)
        {
            fprintf(filepntr, "%s \n", his_array[i]);
        }
    }
    for (int i = 0; i < 1000; i++)
    {
        memset(his_array[i], '\0', sizeof(char) * 1000);
    }
    return 0;
}
// ls ;; , ls ; space (concat a default " ")
// sleep 3&;ls..