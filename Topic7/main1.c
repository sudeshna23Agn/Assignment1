// #include<stdio.h>
// int main()
// {
//     // FILE *fp; int i; int c =0;
//     // fp = fopen("MyFile.csv", "r");
//     // char ch;
//     // do {
//     //     c++;
//     //     ch = fgetc(fp);
//     //     printf("%c", ch);
//     // } while (ch != EOF);
//     // printf("the value of c %d",c);
//     // fclose(fp);

// //    char line[10+1];
// //     int aux[4];
// //     FILE *fd;

// //     int count;
// //     fd = fopen("MyFile.csv","r");
// //     while(fgets(line,10,fd)){
// //         count = sscanf(line,"%d,%d,%d,%d",aux[0],aux[1],aux[2]);
// //         if(count == 2 && aux[1] == 4){
// //             printf("ok");
// //         }
// //         /* Do we need to store data here? */
// //     }
//     char line[200];
//     FILE *fp = fopen("MyFile.csv", "r");
//     while(fgets(line,sizeof(line),fp))
//     {
//         char* token;
//         token = strtok(line,",");
//         while(token!=NULL)
//         {
//             printf("%s",token);
//             token = strtok(NULL,",");
//         }
//         printf("\n");
//     }
//     fclose(fp);
// }
#include <stdio.h>
#include <stdlib.h>
int main() {
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
    // fscanf(fptr, "%[^\n]", c);
    
    printf("Data from the file:\n%d", arr[0]);
    fclose(fptr);

    return 0;
}