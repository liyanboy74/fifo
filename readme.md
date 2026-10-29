# FIFO C Library

A compact and portable circular FIFO (ring buffer) implementation in C.

This project demonstrates the standard pattern for a fixed-size queue using:
- a byte buffer
- a head index
- a tail index
- a count field to distinguish empty from full

## Why this version is safe

The common bug in ring buffers is this:
- `head == tail` is often used to mean both "empty" and "full"
- that makes the queue ambiguous

This implementation avoids that problem by tracking `count` explicitly:
- `count == 0` means empty
- `count == size` means full
- otherwise, the queue is partially filled

## Features

- Fixed-size circular buffer
- Simple API for add/read operations
- Safe status codes for invalid input, empty buffer, overflow, and memory failure
- Minimal dependency on external libraries
- Example program included

## Project structure

- `fifo.h` — public API and data structures
- `fifo.c` — implementation
- `test.c` — example usage
- `Makefile` — build helpers
- `LICENSE` — BSD 3-Clause license

## Build

```bash
make
```

This compiles the library object file.

## Run the example

```bash
make run
```

This builds the example and runs it.

## API

```c
fifo_t fifo;
fifo_state_e status;
uint8_t ch;

status = fifo_init(&fifo, 32U);
if (status != FIFO_OK) {
    return 1;
}

status = fifo_add(&fifo, 'A');
status = fifo_read(&fifo, &ch);

printf("Length: %u\n", fifo_get_len(&fifo));
```

## Main functions

```c
fifo_state_e fifo_init(fifo_t *f, uint32_t size);
void fifo_reset(fifo_t *f);
void fifo_deinit(fifo_t *f);

uint32_t fifo_get_len(const fifo_t *f);
uint32_t fifo_get_buffer_size(const fifo_t *f);
uint32_t fifo_get_capacity(const fifo_t *f);
bool fifo_is_empty(const fifo_t *f);

fifo_state_e fifo_add(fifo_t *f, uint8_t b);
fifo_state_e fifo_read(fifo_t *f, uint8_t *b);
```

## Status codes

```c
typedef enum {
    FIFO_OK = 0,
    FIFO_ERROR_EMPTY,
    FIFO_ERROR_OVERFLOW,
    FIFO_ERROR_MEMORY_ALLOCATION,
    FIFO_ERROR_INVALID_ARGUMENT
} fifo_state_e;
```

## Example output

```text
FIFO contents (5): Hello World!
```

## License

This project is distributed under the BSD 3-Clause License.

## Notes

This is intended as a small educational library and a practical template for a ring buffer. It is not a thread-safe queue; if multiple threads access it concurrently, the caller must add synchronization.
