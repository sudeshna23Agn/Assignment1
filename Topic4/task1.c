#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "string.h"
#include "sys/wait.h"

int main()
{   
    int fd[2];
    if(pipe(fd) == -1) {
        printf("Couldn't open the damn pipe.");
        return 1;
    }

    int pid1 = fork();
    if(pid1 != 0)       //parent process
    {
        close(fd[0]);
        int l =1;
        write(fd[1],&l,sizeof(int));
        close(fd[1]);

    }
    
    if(pid1 == 0)   //child process
    {
        close(fd[1]);
        int j;
        read(fd[0],&j,sizeof(int));
        printf("printing from child process %d\n",j);
        close(fd[0]);
    }
    return 0;
}