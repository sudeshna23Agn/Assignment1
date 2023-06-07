#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t pd = fork();
    if (pd == 0){
        // printf("childs process id %d\n",getpid());
        while(1)
        {
            printf("child is alive\n");
            usleep(10000);
        }
    }
    else{
        sleep(1);
        // printf("childs process id from parent %d\n",pd);
        char command[20];
        sprintf(command, "kill -9 %d", pd);
        system(command);
        printf("parent killed child");
    }
}