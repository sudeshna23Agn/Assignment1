#include<stdio.h>
#include"staticFunction.c"
int main()
{
    add(2,3);
    FILE* fp;
    fp = fopen("test.txt","w");
    fprintf(fp,"%s %s %d","TA","anubhab",43);
}
