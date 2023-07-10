#include<stdio.h>

int main()
{
    FILE* ptr;
    ptr = fopen("test.bin","wb");
    int a[10] ={1,2,3,4,5,6,7,8,9,0};
    fwrite(&a,sizeof(int),10,ptr);

}