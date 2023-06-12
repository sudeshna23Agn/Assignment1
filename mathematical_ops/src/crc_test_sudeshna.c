#include<stdio.h>
#include <stdint.h>
#define testcases 5

#define CRC_POLY 				0x04C11DB7
uint32_t crc32_calc(uint16_t len, unsigned char *data)
{
	/**<Check for null pointer*/
	if(data == NULL){
		perror("NULL pointer detected!\n");
		return 0;
	}

	/**<Check for 0 value of len*/
	if(len <= 0){
		perror("Invalid parameter!\n");
		return 0;
	}

	unsigned char *buffer = (unsigned char*) data;
	int32_t crc = -1; //binary bit pattern 111111111111111 32 times 1

	while( len-- )
	{
		crc = crc ^ (*buffer++ << 24); //first derefencing is done, then pointer gets incremented by one, 
                                    //appending 24 bit to the 8 bit char, input is inverted ?
		for( int bit = 0; bit < 8; bit++ )
		{
			if( crc & (1L << 31)) crc = (crc << 1) ^ CRC_POLY;
			else                  crc = (crc << 1);
		}
	}
	return (uint32_t)crc;
}

int main() 
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
    return 0;
}