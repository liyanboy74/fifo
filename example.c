/**
 *	Example for FIFO Lib
 * 	By Liyanboy74
 *	https://github.com/liyanboy74
 */

#include <stdio.h>
#include <string.h>

#include "fifo.h"

fifo_t f;

void check_error_code(fifo_state_e err)
{
    if(err)printf("Error : Code %d\r\n",err);
}

void add_data(uint8_t * Data,uint32_t Size)
{
    uint32_t i;
    for(i=0;i<Size;i++)
    {
        check_error_code(fifo_add(&f,Data[i]));
    }
}

void print_fifo()
{
    uint8_t Ch;
    uint32_t i,Len;
    fifo_state_e fifo_s;

    Len=fifo_get_len(&f);
    for(i=0;i<Len;i++)
    {
        fifo_s=fifo_read(&f,&Ch);
        if(fifo_s==FIFO_OK)
        {
            putchar(Ch);
        }
        else check_error_code(fifo_s);
    }
}

int main()
{
    fifo_state_e fifo_s;

    uint8_t *DATA1=(uint8_t*)"Hello";
    uint8_t *DATA2=(uint8_t*)"World!";
    uint8_t *DATA3=(uint8_t*)"It Works!";

    fifo_s=fifo_init(&f,10);
    check_error_code(fifo_s);

    add_data(DATA1,strlen((char*)DATA1));
    add_data((uint8_t*)" ",1);
    print_fifo();

    add_data(DATA2,strlen((char*)DATA2));
    add_data((uint8_t*)"\r\n",2);
    print_fifo();

    add_data(DATA3,strlen((char*)DATA3));
    print_fifo();


    return 0;
}
