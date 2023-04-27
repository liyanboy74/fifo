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
	f->fifo_index=0;
	f->fifo_read_index=0;
	f->fifo_buffer_size=0;
	f->fifo_buffer=(uint8_t*)malloc(size*sizeof(uint8_t));
	if(f->fifo_buffer==NULL)return FIFO_ERROR_MEMORY_ALLOCATION;
	else f->fifo_buffer_size=size;
	return FIFO_OK;
}

void fifo_deinit(fifo_t *f)
{
	free(f->fifo_buffer);
	f->fifo_buffer_size=0;
}

void fifo_reset(fifo_t *f)
{
	f->fifo_index=0;
	f->fifo_read_index=0;
}

uint32_t fifo_get_buffer_size(fifo_t *f)
{
	return f->fifo_buffer_size;
}

fifo_state_e fifo_add(fifo_t *f,uint8_t b)
{
	f->fifo_buffer[f->fifo_index]=b;
	f->fifo_index++;
	if(f->fifo_index>f->fifo_buffer_size)f->fifo_index=0;
	if(f->fifo_index==f->fifo_read_index)return FIFO_ERROR_BYFFER_OVF;
	return FIFO_OK;
}

uint32_t fifo_get_len(fifo_t *f)
{
	if(f->fifo_index>=f->fifo_read_index)return f->fifo_index - f->fifo_read_index;
	else return f->fifo_buffer_size-(f->fifo_read_index - f->fifo_index)+1;
}

fifo_state_e fifo_read(fifo_t *f,uint8_t * b)
{
	if(fifo_get_len(f))
	{
		*b=f->fifo_buffer[f->fifo_read_index];
		f->fifo_read_index++;
		if(f->fifo_read_index>f->fifo_buffer_size)f->fifo_read_index=0;
		return FIFO_OK;
	}
	else return FIFO_ERROR_EMPTY;
}

