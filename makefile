all: main.o data.o
	gcc -o structrw main.o data.o

main.o: main.c data.c data.h
	gcc -c main.c

data.o: data.c data.h
	gcc -c data.c

run:
	./structrw

clear:
	rm pop.data