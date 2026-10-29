#ifndef _FIFO_H_
#define _FIFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define FIFO_SIZE 256

typedef enum {
    FIFO_OK = 0,
    FIFO_ERROR_EMPTY,
    FIFO_ERROR_OVERFLOW,
    FIFO_ERROR_MEMORY_ALLOCATION,
    FIFO_ERROR_INVALID_ARGUMENT
} fifo_state_e;

typedef struct {
    uint32_t end;
    uint32_t start;
    uint8_t buf[FIFO_SIZE];
} fifo_t;

fifo_state_e	fifo_init(fifo_t *f);
fifo_state_e	fifo_add(fifo_t *f,uint8_t b);
fifo_state_e    fifo_read(fifo_t *f,uint8_t *b);
uint32_t 		fifo_get_len(fifo_t *f);
void 			fifo_reset(fifo_t *f);

#ifdef __cplusplus
}
#endif

#endif
