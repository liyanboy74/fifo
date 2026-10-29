#include <stdio.h>
#include <string.h>

#include "fifo.h"

static void check_error(fifo_state_e err)
{
    if (err != FIFO_OK) {
        printf("Error: code %d\r\n", err);
    }
}

static void add_data(fifo_t *fifo, const uint8_t *data, uint32_t size)
{
    uint32_t i;

    for (i = 0U; i < size; ++i) {
        check_error(fifo_add(fifo, data[i]));
    }
}

static void print_fifo_contents(fifo_t *fifo)
{
    uint32_t len = fifo_get_len(fifo);
    uint32_t i;
    uint8_t ch;

    printf("FIFO contents (%u): ", len);
    for (i = 0U; i < len; ++i) {
        fifo_state_e status = fifo_read(fifo, &ch);
        if (status != FIFO_OK) {
            check_error(status);
            return;
        }
        putchar(ch);
    }
    printf("\r\n");
}

int main(void)
{
    fifo_t fifo;
    fifo_state_e status;
    const uint8_t *data1 = (const uint8_t *)"Hello";
    const uint8_t *data2 = (const uint8_t *)"World!";
    const uint8_t *data3 = (const uint8_t *)"It Works!";

    status = fifo_init(&fifo, 10U);
    check_error(status);
    if (status != FIFO_OK) {
        return 1;
    }

    add_data(&fifo, data1, (uint32_t)strlen((const char *)data1));
    add_data(&fifo, (const uint8_t *)" ", 1U);
    print_fifo_contents(&fifo);

    add_data(&fifo, data2, (uint32_t)strlen((const char *)data2));
    add_data(&fifo, (const uint8_t *)"\r\n", 2U);
    print_fifo_contents(&fifo);

    add_data(&fifo, data3, (uint32_t)strlen((const char *)data3));
    print_fifo_contents(&fifo);

    add_data(&fifo, (const uint8_t *)"\r\n", 2U);
    print_fifo_contents(&fifo);

    printf("Queue length after writes: %u\r\n", fifo_get_len(&fifo));

    while (!fifo_is_empty(&fifo)) {
        uint8_t value = 0U;
        status = fifo_read(&fifo, &value);
        if (status != FIFO_OK) {
            check_error(status);
            break;
        }
        putchar(value);
    }
    printf("\r\n");

    fifo_deinit(&fifo);
    return 0;
}
