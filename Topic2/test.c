#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    pid_t p = fork();
    // printf("the value of p is %d\n",p);
    if( p == 0){
        printf("child process\n");
        int i =0;
        for (i=0;i<10;i++)
        {
            sleep(0.1);
            printf("hello world %d\n",i);
        }
        // while(1)
        // {
        //     sleep(0.1);
        //     printf("hello world %d\n",i);
        // }
    }
    if (p <0)
        printf("the creation of child failed");
    if (p>0){
        wait();
        printf("parent process\n");
    }
}