/**
 *	Example for FIFO Lib
 * 	By Liyanboy74
 *	https://github.com/liyanboy74
 */

#include <stdio.h>
#include <string.h>

#include "fifo.h"

void check_error_code(FIFO_State_e err)
{
    if(err)printf("Error : Code %d\r\n",err);
}

void add_data(uint8_t * Data,uint32_t Size)
{
    uint32_t i;
    for(i=0;i<Size;i++)
    {
        check_error_code(FIFO_Add(Data[i]));
    }
}

void print_fifo()
{
    uint8_t Ch;
    uint32_t i,Len;
    FIFO_State_e fifo_s;

    Len=FIFO_GetLen();
    for(i=0;i<Len;i++)
    {
        fifo_s=FIFO_Read(&Ch);
        if(fifo_s==FIFO_OK)
        {
            putchar(Ch);
        }
        else check_error_code(fifo_s);
    }
}

int main()
{
    uint8_t *DATA1=(uint8_t*)"Hello ";
    uint8_t *DATA2=(uint8_t*)"World!\r\n";
    uint8_t *DATA3=(uint8_t*)"It Works!";

    FIFO_State_e fifo_s;

    fifo_s=FIFO_Init(14);
    check_error_code(fifo_s);

    add_data(DATA1,6);
    add_data(DATA2,8);
    print_fifo();

    add_data(DATA3,9);
    print_fifo();

    return 0;
}