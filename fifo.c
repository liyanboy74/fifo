#include "fifo.h"

fifo_state_e fifo_init(fifo_t *f)
{
    f->end=0;
    f->start=0;
    return FIFO_OK;
}

void fifo_reset(fifo_t *f)
{
    if (f == NULL) {
        return 0U;
    }

    return f->count;
}

fifo_state_e fifo_add(fifo_t *f,uint8_t b)
{
    f->buf[f->end++]=b;
    f->end%=FIFO_SIZE;
    if(f->end==f->start)return FIFO_ERROR_BYFFER_OVF;
    return FIFO_OK;
}

bool fifo_is_empty(const fifo_t *f)
{
    if(f->end>=f->start)return f->end - f->start;
    else return FIFO_SIZE-(f->start - f->end);
}

fifo_state_e fifo_add(fifo_t *f, uint8_t b)
{
    if(fifo_get_len(f))
    {
        *b=f->buf[f->start++];
        f->start%=FIFO_SIZE;
        return FIFO_OK;
    }

    if (f->count >= f->size) {
        return FIFO_ERROR_OVERFLOW;
    }

    f->buf[f->tail] = b;
    f->tail = (f->tail + 1U) % f->size;
    f->count++;

    return FIFO_OK;
}

fifo_state_e fifo_read(fifo_t *f, uint8_t *b)
{
    if (f == NULL || b == NULL) {
        return FIFO_ERROR_INVALID_ARGUMENT;
    }

    if (f->buf == NULL || f->count == 0U) {
        return FIFO_ERROR_EMPTY;
    }

    *b = f->buf[f->head];
    f->head = (f->head + 1U) % f->size;
    f->count--;

    if (f->count == 0U) {
        f->head = 0U;
        f->tail = 0U;
    }

    return FIFO_OK;
}
