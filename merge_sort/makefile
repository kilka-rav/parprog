all: run

run: main.o sort.o
	g++ main.o sort.o -O0 -pthread -o run

sort.o:
	g++ sort.cpp -c -O0 -pthread

main.o:
	g++ main.cpp -c -O0 -pthread

clean:
	rm -rf *.o run
