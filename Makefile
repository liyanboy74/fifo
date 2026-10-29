default: fifo.o

fifo.o: fifo.c fifo.h
	gcc -Wall -Wextra -std=c11 -c fifo.c -o fifo.o

test: fifo.o
	gcc -Wall -Wextra -std=c11 test.c fifo.o -o test

run: test
	./test

all: test run

clean:
	rm -f *.o test
