#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "string.h"
#include "sys/wait.h"
int shared_mem;
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
        for(l= 0; l<10;l++)
        {
            shared_mem = rand();
            write(fd[1],&shared_mem,sizeof(int));
            printf("printing from parent process %d\n",shared_mem);
            sleep(1);
        }
        close(fd[1]);

    }
    
    if(pid1 == 0)   //child process
    {
        close(fd[1]);
        int i,j;
        for(i=0;i<10;i++)
        {
            read(fd[0],&j,sizeof(int));
            printf("printing from child process %d\n",j);
        }
        
        close(fd[0]);
    }
    return 0;
}