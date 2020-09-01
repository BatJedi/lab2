all:	
	gcc -o executable.o -I headers src/*.c

clean:
	rm executable.o
