#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

#include<syscall.h>
#include<pthread.h>
// /*signal test code starts*/
// int main()
// {
//     pid_t pd = fork();
//     if (pd == 0){
//         // printf("childs process id %d\n",getpid());
//         while(1)
//         {
//             printf("child is alive\n");
//             usleep(10000);
//         }
//     }
//     else{
//         sleep(1);
//         // printf("childs process id from parent %d\n",pd);
//         char command[20];
//         sprintf(command, "kill -9 %d", pd);
//         system(command);
//         printf("parent killed child");
//     }
// }
// /*signal test code ends*/

void *add()
{
    printf("hello from thread\n");
    printf("thread id: %d\n",syscall(SYS_gettid));
    printf("pid: %d\n",getpid());
}
int main()
{
    printf("hello world\n");
    printf("thread id: %d\n",syscall(SYS_gettid));
    printf("pid: %d\n",getpid());
    pthread_t thread_1;
    pthread_create(&thread_1,NULL,&add,NULL);
    printf("pthread id: %d\n",thread_1);
    pthread_join(thread_1,NULL);
}