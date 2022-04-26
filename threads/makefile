all: run

run: main.o count.o unit.o
	gcc main.o count.o -lm -pthread -o run

unit.o: 
	g++ unit.cpp -O0 -o unit_test

main.o:	main.c
	gcc -c -O0 main.c -lm -pthread

count.o: count.c
	gcc -c -O0 count.c

clean:
	rm -rf *.o run test_res* unit_test
