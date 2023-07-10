#include<stdio.h>
#include<stdint.h>

typedef struct{
    uint8_t sequence_id;
    uint8_t phase_id;
    uint8_t command_id;
}engine_sequence_struct;

void main()
{
    FILE* ptr;
    ptr= fopen("engine_sequence_struct.bin","rb");
    engine_sequence_struct* sp;
    fread(sp,sizeof(engine_sequence_struct),5,ptr);
    for(int i = 0; i<5;i++)
    {
        printf("sequence_id: %d ",sp->sequence_id);
        printf("phase_id: %d ",sp->phase_id);
        printf("command_id: %d ",sp->command_id);
        printf("\n");
        sp++;
    }
}