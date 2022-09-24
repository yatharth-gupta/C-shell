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
// #include <sys/stat.h>

// #include "echo.h"
// #include "pwd.h"
// #include "cd.h"
// #include "ls.h"
// #include "pinfo.h"
// #include "process.h"
// #include "history.h"
// #include "discover.h"
// // #define SIGUSR1 16;
// char current_dir[1000];
// char tilda[1000];
// int pids[1000];
// int done[1000];
// int pid_fg[1000];
// char his_array[1000][1000];
// int x;
// int y;
// int time_ = 0;
// int c = 0;
// int items_in_history = 0;
// int c_flag = 0;
// pid_t fg_pid = 0;
// FILE *filepntr;
// FILE *filepntr1;
// void hiss()
// {
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
// }
// struct data
// {
//     int a;
//     int w;
// };
// struct data arr[1000];
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
//     for (int i = 0; i < x; i++)
//     {
//         if (done[i] == 0)
//         {
//             if (waitpid(pids[i], &status, WNOHANG) != 0)
//             {
//                 done[i] = 1;
//                 if (WIFEXITED(status))
//                 {
//                     arr[i].a = 1;
//                     arr[i].w = pids[i];
//                 }
//                 else
//                 {
//                     arr[i].a = -1;
//                     arr[i].w = pids[i];
//                 }
//                 c++;
//                 pids[i] = 0;
//             }
//         }
//     }
// }
// void print_()
// {
//     for (int i = 0; i < c; i++)
//     {
//         if (arr[i].a == 1)
//         {
//             printf("process with pid = %d has ended normally\n", arr[i].w);
//         }
//         if (arr[i].a == -1)
//         {
//             printf("process with pid = %d has ended abnormally\n", arr[i].w);
//         }
//         arr[i].a = 0;
//         arr[i].w = 0;
//     }
// }
// void EOF_handle(int signum)
// {
//     if (signum == SIGUSR1)
//     {
//         printf("\nEOF\n");
//     }
//     hiss();
//     exit(1);
// }
// void C_handle(int signum)
// {
//     if (signum == SIGINT)
//     {
//         // if (y != 0)
//         // {
//         //     y = 0;
//         //     // hiss();
//         //     // return;
//         // }
//         if (fg_pid == pid_fg[0])
//             return;
//         c_flag++;
//         // printf("%d\n", y);
//         for (int i = 0; i < y; i++)
//         {
//             // printf("%d ", pid_fg[i]);
//             // pid_t v = getpid();
//             // printf("%d\n", v);
//             // if (v != fg_pid)
//             // if (fg_pid != pid_fg[i])
//             kill(pid_fg[i], SIGKILL);
//         }
//         y = 0;
//         // printf("%d ", pid_fg[0]);
//     }
//     // printf("%d ", pid_fg[0]);
// }
// int main()
// {
//     // int fd = dup(1);
//     // int fd1 = open();
//     // dup2(fd1,1);
//     // execvp("cat",)
    // fg_pid = getpid();
// //     char *user_name = getlogin();
// //     char name[1000];
// //     gethostname(name, 1000);
// //     char temp[1000];
// //     // char *separated = "\0";
// //     getcwd(tilda, 1000);
// //     strcpy(current_dir, tilda);
// //     char prev[1000] = "\0";
// //     char s[] = " \t\n";
// //     char s_[] = "&";
// //     char s__[] = ";";
// //     items_in_history = 0;
// //     char prev_[1000] = "\0";
// //     filepntr1 = fopen("history.txt", "r");
// //     if (filepntr1 == NULL)
// //     {
// //         filepntr1 = fopen("history.txt", "w");
// //         goto here;
// //     }
// //     while (1)
// //     {
// //         char uh[1000];
// //         if (fgets(uh, 1000, filepntr1) == NULL)
// //         {
// //             break;
// //         }
// //         uh[strlen(uh) - 1] = '\0';
// //         char up[1000];
// //         strcpy(up, uh);
// //         char *w = strtok(uh, " /n");
// //         if (w == NULL)
// //         {
// //             continue;
// //         }
// //         strcpy(his_array[items_in_history], up);
// //         items_in_history++;
// //     }
// // here:;
// //     filepntr = fopen("history.txt", "w");
//     signal(SIGUSR1, EOF_handle);
//     while (1)
//     {
//         char temp1[1000] = "\0";
//         char tokens_[1000][1000];
//         char tokens__[1000][1000];
//         // char relative_curr_dir[1000] = "~";
//         // find_tilda(current_dir, tilda, relative_curr_dir);
//         // if (strcmp(tilda, current_dir) == 0)
//         // {
//         //     if (time_ >= 1)
//         //     {
//         //         printf("\033[;36m<%s@%s:~ took %ds>\033[0m", user_name, name, time_);
//         //         time_ = 0;
//         //     }
//         //     else
//         //     {
//         //         printf("\033[;36m<%s@%s:~>\033[0m", user_name, name);
//         //     }
//         // }
//         // else
//         // {
//         //     if (time_ >= 1)
//         //     {
//         //         printf("\033[;36m<%s@%s:\033[0m", user_name, name);
//         //         printf("\033[;33m%s took %ds>\033[0m", relative_curr_dir, time_);
//         //         time_ = 0;
//         //     }
//         //     else
//         //     {
//         //         printf("\033[;36m<%s@%s:\033[0m", user_name, name);
//         //         printf("\033[;33m%s>\033[0m", relative_curr_dir);
//         //     }
//         // }
//         // char *input;
//         // char *tw;
//         // char b;
//         // input = (char *)malloc(sizeof(char) * 1000);
//         // size_t input_size = 1000;
//         // input[0] = getchar();
//         // input[1] = '\0';
//         // c_flag = 0;
//         // if (input[0] == EOF)
//         // {
//         //     raise(SIGUSR1);
//         // }
//         // print_();
//         // if (input[0] == '\n')
//         // {
//         //     continue;
//         // }
//         // getline(&tw, &input_size, stdin);
//         // tw[strlen(tw) - 1] = '\0';
//         // strcat(input, tw);
//         // printf("%s\n", input);
//         if (c == x)
//         {
//             memset(done, 0, sizeof(int) * 1000);
//             x = 0;
//             c = 0;
//         }
//         // char his_ke_liye_copy[1000];
//         // strcpy(his_ke_liye_copy, input);
//         // char *q = strtok(his_ke_liye_copy, s);
//         // if (items_in_history != 0)
//         //     strcpy(prev_, his_array[items_in_history - 1]);
//         // if (q != NULL)
//         // {
//         //     if (strcmp(prev_, input) != 0)
//         //     {
//         //         strcpy(his_array[items_in_history++], input);
//         //     }
//         // }
//         // int h = 0;
//         // char *g;
//         // g = strtok(input, s__);
//         // if (g == NULL)
//         // {
//         //     continue;
//         // }
//         // strcpy(tokens__[h], g);
//         // g = strtok(NULL, s__);
//         // while (g != NULL)
//         // {
//         //     h++;
//         //     strcpy(tokens__[h], g);
//         //     g = strtok(NULL, s__);
//         // }
//         for (int i = 0; i <= h && c_flag == 0; i++)
//         {
//             signal(SIGINT, C_handle);
//             // printf("%d ", c_flag);
//             // y = 0;
//             char *tokens_redirection[1000];
//             for (int q = 0; q < 1000; q++)
//             {
//                 tokens_redirection[q] = (char *)malloc(sizeof(char) * 1000);
//             }

//             char u[1000];
//             strcpy(u, tokens__[i]);
//             // printf("%s\n", u);
//             int w = 0;
//             char *g;
//             g = strtok(u, " ><\t\n");
//             if (g == NULL)
//             {
//                 continue;
//             }
//             strcpy(tokens_redirection[w], g);
//             g = strtok(NULL, " ><\t\n");
//             while (g != NULL)
//             {
//                 // printf("%s\n", tokens_redirection[w]);
//                 w++;
//                 strcpy(tokens_redirection[w], g);
//                 g = strtok(NULL, " ><\t\n");
//             }
//             // printf("%s\n", tokens_redirection[w]);
//             int count_ = 0, count___ = 0; // count_ for '>', count___ for '<'
//             for (int q = 0; q < strlen(tokens__[i]); q++)
//             {
//                 if (tokens__[i][q] == '>')
//                 {
//                     count_++;
//                 }
//                 if (tokens__[i][q] == '<')
//                 {
//                     count___++;
//                 }
//             }
//             int fd, fd__, fd1, fd2;
//             if (count_ == 1)
//             {
//                 fd = dup(STDOUT_FILENO);
//                 close(STDOUT_FILENO);
//                 fd1 = open(tokens_redirection[w], O_CREAT | O_TRUNC | O_WRONLY, 0644);
//                 dup2(fd1, 1);
//             }
//             if (count_ == 2)
//             {
//                 fd = dup(1);
//                 close(STDOUT_FILENO);
//                 fd1 = open(tokens_redirection[w], O_CREAT | O_WRONLY | O_APPEND, 0644);
//                 dup2(fd1, 1);
//             }
//             if (count___ == 1)
//             {
//                 fd__ = dup(0);
//                 fd2 = open(tokens_redirection[w-1], O_CREAT | O_RDONLY, 0644);
//                 close(0);
//                 dup2(fd2, 0);   
//             }
//             if (count___ == 1 && count_ == 0)
//             {
//                 // FILE *ptr = fopen(tokens_redirection[w], "r");
//                 // int fd = dup(1);
//                 // int fd1 = open()
//                 if (strcmp(tokens_redirection[0], "ls") == 0 || strcmp(tokens_redirection[0], "pwd") == 0 || strcmp(tokens_redirection[0], "cd") == 0 || strcmp(tokens_redirection[0], "echo") == 0 || strcmp(tokens_redirection[0], "pinfo") == 0 || strcmp(tokens_redirection[0], "exit") == 0 || strcmp(tokens_redirection[0], "discover") == 0 || strcmp(tokens_redirection[0], "history") == 0)
//                 {
//                     int ab = 0;
//                     for (int q = 0; q < strlen(tokens__[i]); q++)
//                     {
//                         if (tokens__[i][q] != '<')
//                             ab++;
//                         else
//                             break;
//                     }
//                     char po[1000];
//                     strncpy(po, tokens__[i], ab);
//                     po[ab] = '\0';
//                     strcpy(tokens__[i], po);
//                     // printf("%s\n", tokens__[i]);
//                 }
//                 else
//                 {
//                     int pid = fork();
//                     if (pid == 0)
//                     {
//                         tokens_redirection[w] = NULL;
//                         if (execvp(tokens_redirection[0], tokens_redirection) == -1)
//                         {
//                             printf("error : no such file exists\n");
//                         }
//                     }
//                     else
//                     {
//                         goto re;
//                     }
//                 }
//             }
//             else if (count_ == 1 && count___ == 0)
//             {
//                 // puts("hi");
//                 // printf("%s\n", tokens_redirection[w]);
//                 if (strcmp(tokens_redirection[0], "ls") == 0 || strcmp(tokens_redirection[0], "pwd") == 0 || strcmp(tokens_redirection[0], "cd") == 0 || strcmp(tokens_redirection[0], "echo") == 0 || strcmp(tokens_redirection[0], "pinfo") == 0 || strcmp(tokens_redirection[0], "exit") == 0 || strcmp(tokens_redirection[0], "discover") == 0 || strcmp(tokens_redirection[0], "history") == 0)
//                 {
//                     int ab = 0;
//                     for (int q = 0; q < strlen(tokens__[i]); q++)
//                     {
//                         if (tokens__[i][q] != '>')
//                             ab++;
//                         else
//                             break;
//                     }
//                     char po[1000];
//                     strncpy(po, tokens__[i], ab);
//                     po[ab] = '\0';
//                     // printf("%s------\n", po);
//                     strcpy(tokens__[i], po);
//                     // printf("%s------\n", tokens__[i]);
//                 }
//                 else
//                 {
//                     int pid = fork();
//                     if (pid == 0)
//                     {
//                         tokens_redirection[w] = NULL;
//                         if (execvp(tokens_redirection[0], tokens_redirection) == -1)
//                         {
//                             printf("error : no such file exists\n");
//                         }
//                     }
//                     else
//                     {
//                         goto re;
//                     }
//                 }
//             }
//             else if (count_ == 2)
//             {
//                 // printf("%s\n", tokens_redirection[w]);
//                 if (strcmp(tokens_redirection[0], "ls") == 0 || strcmp(tokens_redirection[0], "pwd") == 0 || strcmp(tokens_redirection[0], "cd") == 0 || strcmp(tokens_redirection[0], "echo") == 0 || strcmp(tokens_redirection[0], "pinfo") == 0 || strcmp(tokens_redirection[0], "exit") == 0 || strcmp(tokens_redirection[0], "discover") == 0 || strcmp(tokens_redirection[0], "history") == 0)
//                 {
//                     int ab = 0;
//                     for (int q = 0; q < strlen(tokens__[i]); q++)
//                     {
//                         if (tokens__[i][q] != '>')
//                             ab++;
//                         else
//                             break;
//                     }
//                     char po[1000];
//                     strncpy(po, tokens__[i], ab);
//                     po[ab] = '\0';
//                     // printf("%s------\n", po);
//                     strcpy(tokens__[i], po);
//                     // printf("%s------\n", tokens__[i]);
//                 }
//                 else
//                 {
//                     int pid = fork();
//                     if (pid == 0)
//                     {
//                         tokens_redirection[w] = NULL;
//                         if (execvp(tokens_redirection[0], tokens_redirection) == -1)
//                         {
//                             printf("error : no such file exists\n");
//                         }
//                     }
//                     else
//                     {
//                         goto re;
//                     }
//                 }
//             }
//             else if ((count_ == 1 || count_ == 2) && count___ == 1)
//             {
//                 int pid = fork();
//                 if (pid == 0)
//                 {
//                     tokens_redirection[w] = NULL;
//                     if (execvp(tokens_redirection[0], tokens_redirection) == -1)
//                     {
//                         printf("error : no such file exists\n");
//                     }
//                 }
//                 else
//                 {
//                     goto 
//                     re;
//                 }
//             }
//             int count = 0;
//             for (int s = 0; s < strlen(tokens__[i]); s++)
//             {
//                 if (tokens__[i][s] == '&')
//                 {
//                     count++;
//                 }
//             }
//             char input_copy[1000];
//             strcpy(input_copy, tokens__[i]);
//             char *t;
//             t = strtok(input_copy, s_);
//             strcpy(tokens_[0], t);
//             t = strtok(NULL, s_);
//             int p = 0;
//             while (t != NULL)
//             {
//                 strcpy(tokens_[++p], t);
//                 t = strtok(NULL, s_);
//             }
//             int bg = 0;
//             if (count == p + 1)
//             {
//                 bg = 1;
//             }
//             for (int j = 0; j <= p; j++)
//             {
//                 char *tokens[1000];
//                 for (int d = 0; d < 1000; d++)
//                 {
//                     tokens[d] = (char *)malloc(sizeof(char *) * 1000);
//                 }

//                 char input_copy2[1000];
//                 strcpy(input_copy2, tokens_[j]);
//                 char *k;
//                 k = strtok(input_copy2, s);
//                 if (k == NULL)
//                 {
//                     goto label;
//                 }
//                 strcpy(tokens[0], k);
//                 k = strtok(NULL, s);
//                 int o = 0;
//                 while (k != NULL)
//                 {
//                     strcpy(tokens[++o], k);
//                     k = strtok(NULL, s);
//                 }
//                 if (bg == 1 || (bg == 0 && j != p))
//                 {
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

//                         cd__(tokens, prev, temp1, o + 1);
//                     }
//                     else if (strcmp(tokens[0], "echo") == 0)
//                     {
//                         echo__(tokens, o + 1);
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
//                     else if (strcmp(tokens[0], "discover") == 0)
//                     {

//                         discover__(tokens, o + 1);
//                     }
//                     else if (strcmp(tokens[0], "exit") == 0)
//                     {
//                         hiss();
//                         goto his;
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
//         re:;
//             if (count_ >= 1)
//             {
//                 close(fd1);
//                 dup2(fd, 1);
//                 close(fd);
//             }
//             if (count___ >= 1)
//             {
//                 close(fd2);
//                 dup2(fd__, 0);
//                 close(fd__);
//             }
//         }
//     label:;
//         signal(SIGCHLD, sig_handler);
//     }
// his:;
//     return 0;
// }
