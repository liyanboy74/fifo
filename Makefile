default:
	gcc -Wall -c fifo.c

test:
	gcc -Wall test.c fifo.o -o test

run:
	@./test

all:default test run

clean:
	rm -rf *.o *.exe

