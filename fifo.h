#ifndef _FIFO_H_
#define _FIFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    FIFO_OK = 0,
    FIFO_ERROR_EMPTY,
    FIFO_ERROR_OVERFLOW,
    FIFO_ERROR_MEMORY_ALLOCATION,
    FIFO_ERROR_INVALID_ARGUMENT
} fifo_state_e;

typedef struct {
    uint32_t size;
    uint32_t head;
    uint32_t tail;
    uint32_t count;
    uint8_t *buf;
} fifo_t;

fifo_state_e fifo_init(fifo_t *f, uint32_t size);
void fifo_reset(fifo_t *f);
void fifo_deinit(fifo_t *f);

uint32_t fifo_get_len(const fifo_t *f);
uint32_t fifo_get_buffer_size(const fifo_t *f);
uint32_t fifo_get_capacity(const fifo_t *f);
bool fifo_is_empty(const fifo_t *f);

fifo_state_e fifo_add(fifo_t *f, uint8_t b);
fifo_state_e fifo_read(fifo_t *f, uint8_t *b);

#ifdef __cplusplus
}
#endif

#endif
