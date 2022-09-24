# OSN-assignment-2
> .h files contains respective function prototypes.

> .c contains the definings of the functions in respective in .h

## main.c 
> Taking the input and tokenising it w.r.t ";" and then again tokenising each of the above token w.r.t "&".Now sending each process before a '&' to bg__ in process.c. For the foreground process first check if it is built in, if not call execvp().
## ls.c
> first i am checking, the presence of -l and - a flag, and storing the rest in a array of strings. Then checking if they are directory or file or niether. '-a' flag prints all files including hidden. while '-l' prints all info of files excluding hidden files. colors of dir,files,exe is also handled.
## cd.c
>Cases are, if '~' , '.' , '..' ,'-' and else. Mainly chdir is used
to navigate to a directory.
## discover.c
> First find if '-d' and '-f' flag are present or not, if the token start from " then check if it a file and store it in array.If anything else it should be a directory, if not then error. then recursivly print the directory or find a file.We also have to ignore hidden files as the file '..' has prev dir, so in recursion it goes in infinite loop.
## echo.c
> printing the user input after echo with removed extra spaces.
## history.c
>Storing the contents of file history.txt in a global array of strings and then storing the given inputs in the same array from that index only. On input "exit" the contents of the array are written to the file again.
## pinfo.c
>printing the process pid,process status, memory used and exe path.
using proc/pid/stat , proc/pid/status and proc/pid/exe.
## pwd.c
>just printing the current_dir.
## process.c
>for background processes,for the parent condition, storing the pids of the childs in a global array,printing it also.Also when the child process ends, printing the pid and the exiting status of the process when user give "enter" command.
for foreground processes,the parent will wait for the child process to complete and print the time taken by it. if more than one fg process then printing the total time taken by both.
## variable.h
>using extern, making a variable global across all the .c files.