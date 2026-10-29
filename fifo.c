#include "fifo.h"

fifo_state_e fifo_init(fifo_t *f, uint32_t size)
{
    if (f == NULL) {
        return FIFO_ERROR_INVALID_ARGUMENT;
    }

    if (size == 0U) {
        return FIFO_ERROR_INVALID_ARGUMENT;
    }

    f->buf = (uint8_t *)malloc((size_t)size * sizeof(uint8_t));
    if (f->buf == NULL) {
        return FIFO_ERROR_MEMORY_ALLOCATION;
    }

    f->size = size;
    f->head = 0U;
    f->tail = 0U;
    f->count = 0U;

    return FIFO_OK;
}

void fifo_reset(fifo_t *f)
{
    if (f == NULL) {
        return;
    }

    f->head = 0U;
    f->tail = 0U;
    f->count = 0U;
}

void fifo_deinit(fifo_t *f)
{
    if (f == NULL) {
        return;
    }

    free(f->buf);
    f->buf = NULL;
    f->size = 0U;
    f->head = 0U;
    f->tail = 0U;
    f->count = 0U;
}

uint32_t fifo_get_len(const fifo_t *f)
{
    if (f == NULL) {
        return 0U;
    }

    return f->count;
}

uint32_t fifo_get_buffer_size(const fifo_t *f)
{
    return fifo_get_capacity(f);
}

uint32_t fifo_get_capacity(const fifo_t *f)
{
    if (f == NULL) {
        return 0U;
    }

    return f->size;
}

bool fifo_is_empty(const fifo_t *f)
{
    if (f == NULL) {
        return true;
    }

    return f->count == 0U;
}

fifo_state_e fifo_add(fifo_t *f, uint8_t b)
{
    if (f == NULL || f->buf == NULL) {
        return FIFO_ERROR_INVALID_ARGUMENT;
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
