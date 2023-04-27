/**
 *	FIFO Lib
 * 	By Liyanboy74
 *	https://github.com/liyanboy74
 */
#ifndef _FIFO_H_
#define _FIFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

typedef enum {
    FIFO_OK,
    FIFO_ERROR_EMPTY,
    FIFO_ERROR_BYFFER_OVF,
    FIFO_ERROR_MEMORY_ALLOCATION
} fifo_state_e;

typedef struct {
    uint32_t size;
    uint32_t end;
    uint32_t start;
    uint8_t *buf;
} fifo_t;

fifo_state_e	fifo_init(fifo_t *f,uint32_t size);
fifo_state_e	fifo_add(fifo_t *f,uint8_t b);
fifo_state_e    fifo_read(fifo_t *f,uint8_t *b);
uint32_t 		fifo_get_len(fifo_t *f);
uint32_t 		fifo_get_buffer_size(fifo_t *f);
void 			fifo_reset(fifo_t *f);
void 			fifo_deinit(fifo_t *f);

#ifdef __cplusplus
}
#endif

#endif
