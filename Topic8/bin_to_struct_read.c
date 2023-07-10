#include<stdio.h>

int main()
{
    FILE* ptr;
    ptr= fopen("test.bin","rb");
    int a = 0;
    // int a[10]={0};
    // fread(a,sizeof(int),6,ptr);
    // for(int i=0;i<6;i++)
    //     printf("%d\n",a[i]);
    fread(&a,sizeof(int),1,ptr);
    printf("%d\n",a);
}
