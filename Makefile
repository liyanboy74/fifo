default:
	gcc -Wall -c fifo.c

example:
	gcc -Wall example.c fifo.o -o example

run:
	@./example

all:default example run

clean:
	rm -rf *.o *.exe

