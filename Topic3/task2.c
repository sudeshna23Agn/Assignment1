
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <pthread.h>

void *myThreadFun(void *vargp)
{
    int times = 0;
    while(1){
        times++;
        printf("hello %d\n",times);
        usleep(100000);
    }
    return NULL;
}
int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    sleep(2);
    // pthread_join(thread_id, NULL);
    pthread_cancel(thread_id);
    printf("parent thread\n");
}

