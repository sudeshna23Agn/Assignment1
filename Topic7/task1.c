#include<stdio.h>
#include <stdlib.h>
#define num rand() % 10
void create_file()
{
    FILE *fp; int i;
    fp = fopen("MyFile.csv", "w+");
    for(i=0;i<10;i++)
    {
        fprintf(fp,"%d, %d, %d, %d\n", num, num, num, num);
    }
    fclose(fp);
}
void read_file()
{
    char c[1000];
    FILE *fptr;
    if ((fptr = fopen("MyFile.csv", "r")) == NULL) {
        printf("Error! File cannot be opened.");
        exit(1);
    }
    int arr[4],col=0,row = 0,sum=0;
    do{
        col = fscanf(fptr, "%d,%d,%d,%d\n",&arr[0],&arr[1],&arr[2],&arr[3]);
        if(col == 4) row++;
        sum = sum + arr[0] + arr[1] + arr[2] + arr[3];
    }while(row<10);
    printf("sum is %d\n",sum);
    fclose(fptr);
}
int main()
{
    create_file();
    read_file();

}
