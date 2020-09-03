all:	
	gcc -o executable.o -I headers src/main.c src/matrix.c src/matrixmath.c src/transformations.c

clean:
	rm executable.o
