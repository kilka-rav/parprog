#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "long.h"

//#include <mpi.h>

#define Error(string) fprintf(stderr, "%s\n", string)


double check_input(int argc, char** argv) {
	if ( argc != 2 ) {
		Error("Wrong numbers of Input");
		exit(1);
	}
	return atoi(argv[1]);
}

int count_accuracy(int order) {
	int k = 2;
	if ( order >= 1 ) {
		Long global;
		init(&global, 0, order);
		divide(order, &global);
		Long local;
		init(&local, 0, order);
		divide(k, &local);
		while( ( compare_long(&local, &global) ) > 0 ) {
			k++;
			divide_long(k, &local);
		}
		k *= 100;
		//k += 2;
		clear(&global);
		clear(&local);
		return k;
	}
	Error("Error in order");
	exit(-2);
}


void count_2(Long* result, int begin, int end, int order) {
	int cur = begin;
	int i;
	Long l1;
	init(&l1, 0, order);
	divide(cur, &l1);
	for(i = begin; i <= end; ++i) {
		//printf("cur = %d\n", i);
		//print(&l1);
		add(result, &l1, result);
		cur++;
		divide_long(cur, &l1);
	}
	//printf("exit foffrfro\n");
	clear(&l1);
}
/*
void count(Long* result, int begin, int end, int order) { //Interesting solution, but this algorithm isn't accelerate
	int i;
	Long l1;
	int sz = result->size;
	for(i = end; i >= begin; i--) {
		printf("cur = %d\n", i);
		Long l2;
		if ( i == end ) {
			init(&l1, 0, order);
			divide(i, &l1);
			add_one(&l1);
		}
		init(&l2, 1, order);
		divide(i, &l2);
		
		add_one(&l1);
		clear(&l2);
	}
	clear(&l1);
}	
*/		
int main(int argc, char** argv) {
	int p = check_input(argc, argv);
	int N = count_accuracy(p);	//До какога члена нужно считать раложение
	//printf("Number of Teulors = %d\n", N);
	Long result;
	p *= AMENDMENT;
	//printf("WORK_count\n");
	init(&result, 2, p);
	//printf("size = %d\n Number Teulor = %d\n", result.size, N);
	count_2(&result, 2, N, p);
	//printf("work\nsize = %d\nreal_size = %d\n", result.size, p);
	print(&result);
	clear(&result);
	return 0;
}
	
