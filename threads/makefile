all: run

run: main.o count.o
	gcc main.o count.o -lm -pthread -o run

main.o:	main.c
	gcc -c -O0 main.c -lm -pthread

count.o: count.c
	gcc -c -O0 count.c

clean:
	rm -rf *.o run
