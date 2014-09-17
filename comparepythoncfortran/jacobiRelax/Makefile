CC=gcc
CF=gfortran
OPS=-O3

default: jacobirelaxf jacobirelaxc

jacobirelaxc: jacobirelax.c
	$(CC) $(OPS) jacobirelax.c -o jacobirelaxc

jacobirelaxf: jacobirelax.f90
	$(CF) $(OPS) jacobirelax.f90 -o jacobirelaxf

clean:
	rm -f *.o jacobirelaxf jacobirelaxc


