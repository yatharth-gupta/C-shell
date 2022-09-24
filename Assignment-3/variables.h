#include <stdio.h>
#ifndef __variables_h
#define __variables_h
extern char current_dir[1000];
extern char tilda[1000];
extern int pids_bg[1000];
extern int pids_fg[1000];
extern char his_array[1000][1000];
extern int items_in_history;
extern FILE *filepntr;
extern FILE *filepntr1;
extern void hiss();
extern void find_tilda(char *relative_curr_dir);
extern int no_of_bg;
extern int time_;
extern int x;
extern int y;
extern int function(char *token_space[], int o);
#endif