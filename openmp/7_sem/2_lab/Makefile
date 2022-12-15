CC=clang++

all: run
run: main.o numerov.o
	$(CC) main.o numerov.o -fopenmp -o run

main.o: main.cpp
	$(CC) -c -fopenmp main.cpp

numerov.o:
	$(CC) -c -fopenmp numerov.cpp

clean:
	rm -rf *.o run