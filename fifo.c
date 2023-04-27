/**
 *	FIFO Lib
 * 	By Liyanboy74
 *	https://github.com/liyanboy74
 */

#include <stdint.h>
#include <stdlib.h>

#include "fifo.h"

fifo_state_e fifo_init(fifo_t *f,uint32_t size)
{
    f->end=0;
    f->start=0;
    f->size=0;
    f->buf=(uint8_t*)malloc(size*sizeof(uint8_t));
    if(f->buf==NULL)return FIFO_ERROR_MEMORY_ALLOCATION;
    else f->size=size;
    return FIFO_OK;
}

void fifo_deinit(fifo_t *f)
{
    free(f->buf);
    f->size=0;
}

void fifo_reset(fifo_t *f)
{
    f->end=0;
    f->start=0;
}

uint32_t fifo_get_buffer_size(fifo_t *f)
{
    return f->size;
}

fifo_state_e fifo_add(fifo_t *f,uint8_t b)
{
    f->buf[f->end++]=b;
    f->end%=f->size;
    if(f->end==f->start)return FIFO_ERROR_BYFFER_OVF;
    return FIFO_OK;
}

uint32_t fifo_get_len(fifo_t *f)
{
    if(f->end>=f->start)return f->end - f->start;
    else return f->size-(f->start - f->end);
}

fifo_state_e fifo_read(fifo_t *f,uint8_t *b)
{
    if(fifo_get_len(f))
    {
        *b=f->buf[f->start++];
        f->start%=f->size;
        return FIFO_OK;
    }
    else return FIFO_ERROR_EMPTY;
}

