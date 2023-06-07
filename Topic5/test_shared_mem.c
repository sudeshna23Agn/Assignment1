#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
 
int main()
{
   pid_t pd = fork();
   if (pd == 0)
   {
      key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    int *str = (int*) shmat(shmid,(void*)0,0);
    int j;
    for(j=0;j<10;j++)
    {
       printf("printing from child %d\n",*str);
       str++;
    }
    
   }
   else{
      key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    int *str = (int*) shmat(shmid,(void*)0,0);
    int i;
    for(i=0;i<10;i++)
    {
      *str = rand();
      
    printf("Data written in memory %d is: %d\n",&str,*str);
    str++;
   }
   shmdt(str);
   }
    return 0;
}