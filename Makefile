all: dedos.o
	gcc dedos.o -o dedos

dedos.o: dedos.c
	gcc -c dedos.c

clean: 
	rmm -rf *.o