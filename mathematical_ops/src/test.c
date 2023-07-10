#include<stdio.h>
#include <stdint.h>
void recheck_crc()
{
    FILE* ptr = fopen("results.txt","r");
    char higher_byte, lower_byte;
    for(int j =0;j<5;j++)
    {
        for(int i =0;i<4;i++)
        {
            fscanf(ptr,"%c",&higher_byte);
            printf("higher-byte %c\n", higher_byte);
            if(higher_byte<65 && higher_byte != '\n')
                higher_byte = higher_byte - 48;
            else if(higher_byte != '\n')
                higher_byte = higher_byte-36;
            
            fscanf(ptr,"%c",&lower_byte);
            printf("lower-byte %c\n", lower_byte);
            if(lower_byte<65 && lower_byte != '\n')
            lower_byte= lower_byte- 48;
            else if (lower_byte != '\n')
                lower_byte= lower_byte - 36;
            // c[size+i] = (higher_byte<<4)| lower_byte;
        }
    }
    
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
int main()
{
    
}
// for(int i =0;i<4;i++)
// {
//     fscanf(write_file,"%c",&higher_byte);
//     printf("higher-byte %c\n", higher_byte);
//     if(higher_byte<65)
//         higher_byte = higher_byte - 48;
//     else
//         higher_byte = higher_byte-36;
//     printf("higher-byte %d\n", higher_byte);
//     fscanf(write_file,"%c",&lower_byte);
//     if(lower_byte<65)
//     lower_byte= lower_byte- 48;
//     else
//         lower_byte= lower_byte - 36;
//     // c[size+i] = (higher_byte<<4)| lower_byte;
// }

