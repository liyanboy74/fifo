# FIFO C Library

A small, portable circular FIFO implementation in C.

Features:
- Fixed-size ring buffer
- Thread-safe usage is not guaranteed; the caller owns synchronization
- Clear status codes for empty, overflow, and invalid input
- Simple API for enqueue/dequeue operations

## Build

```bash
make
```

## Run the example

```bash
make run
```

## API overview

```c
fifo_t fifo;
fifo_state_e status = fifo_init(&fifo, 32U);

status = fifo_add(&fifo, 'A');
uint8_t ch = 0U;
status = fifo_read(&fifo, &ch);

printf("Length: %u\n", fifo_get_len(&fifo));
```

## Notes

The implementation keeps a `count` field to distinguish between an empty queue and a full queue without ambiguity.
This avoids the common circular-buffer bug where `head == tail` is treated as both full and empty.

## License

This project is distributed under the BSD 3-Clause License.
