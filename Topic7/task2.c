#include<stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr,*fp;
    char c[1000];
    fp = fopen("new.csv", "w");
    if ((fptr = fopen("MyFile.csv", "r")) == NULL) {
        printf("Error! File cannot be opened.");
        exit(1);
    }
    int arr[4],col=0,row = 0,sum=0;
    do{
        col = fscanf(fptr, "%d,%d,%d,%d\n",&arr[0],&arr[1],&arr[2],&arr[3]);
        if(col == 4) row++;
        fprintf(fp,"%d, %d, %d, %d\n", arr[0]+100, arr[1]+100, arr[2]+100, arr[3]+100);
    }while(row<10);
    fclose(fptr);
    fclose(fp);
}
