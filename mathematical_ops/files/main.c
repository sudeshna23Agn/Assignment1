#include<stdio.h>
#include<stdint.h>

int main()
{
    // FILE* fp = fopen("text.txt","r");
    // char string[20]; int num; char c;
    // // fscanf(fp,"%s",string);
    // // fscanf(fp,"%d\n",&num);
    // // fscanf(fp,"%c\n",&c);
    // fscanf(fp,"%c\n",&c);
    // // printf("%s\n",string);
    // // printf("%d %d\n",num,sizeof(num));
    // printf("%x\n",c);
    FILE* ptr = fopen("hextext.txt","r");
    char higher_byte, lower_byte; uint8_t d;
    fscanf(ptr,"%c",&higher_byte);
    
    if(higher_byte<65)
        higher_byte = higher_byte- 48;
    else
        higher_byte = higher_byte-36;
    printf("%d\n",higher_byte);
    
    fscanf(ptr,"%c",&lower_byte);
    if(lower_byte<65)
       lower_byte= lower_byte- 48;
    else
        lower_byte= lower_byte - 36;
    printf("%d\n",lower_byte);

    d = (higher_byte<<4)| lower_byte;
    printf("%x\n",d);
    fclose(ptr);
    // fclose(fp);
}