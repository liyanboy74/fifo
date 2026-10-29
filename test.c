#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "fifo.h"

static void test_invalid_usage(void)
{
    fifo_t fifo;
    fifo_state_e status;

    status = fifo_init(NULL, 8U);
    assert(status == FIFO_ERROR_INVALID_ARGUMENT);

    status = fifo_init(&fifo, 0U);
    assert(status == FIFO_ERROR_INVALID_ARGUMENT);

    status = fifo_add(NULL, 'x');
    assert(status == FIFO_ERROR_INVALID_ARGUMENT);

    fifo.buf = NULL;
    status = fifo_add(&fifo, 'x');
    assert(status == FIFO_ERROR_INVALID_ARGUMENT);

    fifo_reset(NULL);
    fifo_deinit(NULL);
}

static void test_basic_enqueue_dequeue(void)
{
    fifo_t fifo;
    fifo_state_e status;
    uint8_t value = 0U;

    status = fifo_init(&fifo, 4U);
    assert(status == FIFO_OK);
    assert(fifo_is_empty(&fifo));
    assert(fifo_get_len(&fifo) == 0U);
    assert(fifo_get_capacity(&fifo) == 4U);
    assert(fifo_get_buffer_size(&fifo) == 4U);

    status = fifo_add(&fifo, 'A');
    assert(status == FIFO_OK);
    status = fifo_add(&fifo, 'B');
    assert(status == FIFO_OK);
    status = fifo_add(&fifo, 'C');
    assert(status == FIFO_OK);

    assert(fifo_get_len(&fifo) == 3U);
    assert(!fifo_is_empty(&fifo));

    status = fifo_read(&fifo, &value);
    assert(status == FIFO_OK && value == 'A');
    status = fifo_read(&fifo, &value);
    assert(status == FIFO_OK && value == 'B');

    assert(fifo_get_len(&fifo) == 1U);

    status = fifo_add(&fifo, 'D');
    assert(status == FIFO_OK);
    status = fifo_read(&fifo, &value);
    assert(status == FIFO_OK && value == 'C');
    status = fifo_read(&fifo, &value);
    assert(status == FIFO_OK && value == 'D');
    assert(fifo_get_len(&fifo) == 0U);
    assert(fifo_is_empty(&fifo));

    status = fifo_read(&fifo, &value);
    assert(status == FIFO_ERROR_EMPTY);

    fifo_deinit(&fifo);
}

static void test_full_and_wraparound(void)
{
    fifo_t fifo;
    fifo_state_e status;
    uint8_t value = 0U;
    uint32_t i;

    status = fifo_init(&fifo, 3U);
    assert(status == FIFO_OK);

    for (i = 0U; i < 3U; ++i) {
        status = fifo_add(&fifo, (uint8_t)('0' + i));
        assert(status == FIFO_OK);
    }

    status = fifo_add(&fifo, 'X');
    assert(status == FIFO_ERROR_OVERFLOW);
    assert(fifo_get_len(&fifo) == 3U);

    status = fifo_read(&fifo, &value);
    assert(status == FIFO_OK && value == '0');
    status = fifo_read(&fifo, &value);
    assert(status == FIFO_OK && value == '1');

    status = fifo_add(&fifo, 'A');
    assert(status == FIFO_OK);
    status = fifo_add(&fifo, 'B');
    assert(status == FIFO_OK);
    assert(fifo_get_len(&fifo) == 3U);

    status = fifo_read(&fifo, &value);
    assert(status == FIFO_OK && value == '2');
    status = fifo_read(&fifo, &value);
    assert(status == FIFO_OK && value == 'A');
    status = fifo_read(&fifo, &value);
    assert(status == FIFO_OK && value == 'B');
    assert(fifo_get_len(&fifo) == 0U);
    assert(fifo_is_empty(&fifo));

    fifo_deinit(&fifo);
}

static void test_reset_behavior(void)
{
    fifo_t fifo;
    fifo_state_e status;
    uint8_t value = 0U;

    fifo_s=fifo_init(&f);
    check_error_code(fifo_s);

    status = fifo_add(&fifo, 'M');
    assert(status == FIFO_OK);
    status = fifo_add(&fifo, 'N');
    assert(status == FIFO_OK);

    fifo_reset(&fifo);
    assert(fifo_get_len(&fifo) == 0U);
    assert(fifo_is_empty(&fifo));

    status = fifo_read(&fifo, &value);
    assert(status == FIFO_ERROR_EMPTY);

    fifo_deinit(&fifo);
}

int main(void)
{
    test_invalid_usage();
    test_basic_enqueue_dequeue();
    test_full_and_wraparound();
    test_reset_behavior();

    printf("All FIFO tests passed.\n");
    return 0;
}
