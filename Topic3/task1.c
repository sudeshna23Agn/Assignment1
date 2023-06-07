
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <pthread.h>

void *myThreadFun(void *arg)
{
    FILE* fp; char* c;
    c = (char*)arg;
    fp = fopen(c,"w");
    return NULL;
}
int main()
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, myThreadFun, "thread1.txt");
    pthread_create(&th2, NULL, myThreadFun, "thread2.txt");
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf("parent thread\n");
}

