
#include <stdio.h>
#include<stdint.h>
void calcrc()
{
    FILE* fp = fopen("testinput.txt","r");
    FILE* write_file = fopen("results.txt","w+");
    uint8_t c[100];
    char higher_byte, lower_byte;
    char nl;
    int size;
    for(int j =0;j<testcases;j++)
    {   
        fscanf(fp, "%d ",&size);
        for(int i =0;i<size;i++)
        {
            fscanf(fp,"%d ",&c[i]);
        }
        printf("the CRC valus at transmitter %x\n",crc32_calc(size,c)); 
        uint32_t result = crc32_calc(size,c);
        fprintf(write_file,"%x\n", crc32_calc(size,c));
        c[size] = result>>24;
        c[size+1] = (result & 0x00ff0000)>>16;
        c[size+2] = (result & 0x0000ff00) >>8;
        c[size+3] = result & 0x000000ff;
        printf("the CRC value at the receiver is %x\n",crc32_calc(size+4,c));
    }
    fclose(fp);
    fclose(write_file);
}
void recheck_crc()
{
    FILE* ptr = fopen("results.txt","r");
    fseek(ptr,0,SEEK_SET);
    FILE* fp = fopen("testinput.txt","r");
    uint8_t c[100];
    char higher_byte, lower_byte;
    char nl;
    int size;
    for(int j =0;j<testcases;j++)
    {   
        fscanf(fp, "%d ",&size);
        for(int i =0;i<size;i++)
        {
            fscanf(fp,"%d ",&c[i]);
        }
        for(int i =0;i<4;i++)
        {
            fscanf(ptr,"%c",&higher_byte);
            printf("higher-byte %c\n", higher_byte);
            if(higher_byte<65)
                higher_byte = higher_byte - 48;
            else
                higher_byte = higher_byte-87;
            
            fscanf(ptr,"%c",&lower_byte);
            printf("lower-byte %c\n", lower_byte);
            if(lower_byte<65)
            lower_byte= lower_byte- 48;
            else
                lower_byte= lower_byte - 87;
            c[size+i] = (higher_byte<<4)| lower_byte;
        }
    }
    fscanf(ptr,"%c",&nl);
    fclose(ptr);
}
void recheck2()
{
    FILE* ptr = fopen("results.txt","r");
    char str[8];
    fgets(str, 9, ptr);
    printf("%s",str);
    fclose(ptr);
}
int main() {
    // Write C code here
    printf("Hello world\n");
    uint32_t d = 0x2714739f;char c[4];
    c[0] = d>>24;
    printf("%x\n",c[0]);
    // printf("%x\n",d);
    c[1] = (d & 0x00ff0000)>>16;
    printf("%x\n",c[1]);
    c[2] = (d & 0x0000ff00) >>8;
    printf("%x\n",c[2]);
    c[3] = d & 0x000000ff;
    printf("%x\n",c[3]);
    printf("size of char %d",sizeof(c));
    return 0;
}