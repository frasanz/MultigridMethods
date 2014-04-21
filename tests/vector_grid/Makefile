CC=gcc
OPS=-g -Wall

default: vector_grid

vector_grid: vector_grid.c memory.o initialize.o output.o
	$(CC) $(OPS) output.o initialize.o memory.o vector_grid.c -o vector_grid

memory.o: memory.c
	$(CC) $(OPS) -c memory.c -o memory.o

initialize.o: initialize.c
	$(CC) $(OPS) -c initialize.c -o initialize.o

output.o: output.c
	$(CC) $(OPS) -c output.c -o output.o

clean:
	rm -rf *.o vector_grid
