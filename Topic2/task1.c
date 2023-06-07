#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    pid_t pid_child = fork();
    FILE* fp; int n=0; char *c;
    int process_id = getpid();
    printf("%d",sizeof(process_id));
    sprintf(c,"%d.txt",process_id) ;
    fp = fopen(c,"w");
    while(n<=10)
    {
        fprintf(fp,"%d",n);
        n++;
    }

    fclose(fp);

}
