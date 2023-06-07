#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <pthread.h>
int count  = 0;
void *myThreadFun(void *vargp)
{
    sleep(1);
    count = 1;
    return NULL;
}
int main()
{
    pid_t p = fork();
    if( p == 0){
        printf("child process\n");
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, myThreadFun, NULL);
        while(count == 0)
        {
            printf("hello world\n");
            usleep(100000);
        }
        pthread_join(thread_id, NULL);
        // int i =0;
        // for (i=0;i<10;i++)
        // {
        //     sleep(0.1);
        //     printf("hello world %d\n",i);
        // }
        // int milli_seconds = 1000 * 1;
 
        // // Storing start time
        // clock_t start_time = clock();
        // // looping till required time is not achieved
        // int c =0;
        // while (clock() < start_time + milli_seconds){
        //     printf("hello world %d\n",c);
        //     sleep(0.1);
        //     c++;
        // }

    }
    if (p <0)
        printf("the creation of child failed");
    if (p>0){
        wait();
        printf("parent process\n");
    }
}


    //child process
    // else{
    //     int milli_seconds = 1000 * 1;
 
    //     // Storing start time
    //     clock_t start_time = clock();
    //     // looping till required time is not achieved
    //     while (clock() < start_time + milli_seconds){
    //         printf("hello world\n");
    //         sleep(0.1);
    //     }
    //     return 0;
    // }

