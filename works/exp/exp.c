#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "long.h"

#include <mpi.h>

#define Error(string) fprintf(stderr, "%s\n", string)


typedef struct Numbers {
	int id;
	int num_proc;
	Long* res;
} Numbers;

void Numbers_init(Numbers* t, Long* result, int my_id, int commsize) {
	t->id = my_id;
	t->res = result;
	t->num_proc = commsize;
}

void my_print(Numbers* t) {
	printf("id = %d\tnum_proc = %d\t", t->id, t->num_proc);
	print(t->res);
}

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

int factorial(int n) {
	int reply = 1;
	while( n > 1 ) {
		reply *= n;
		n--;
	}
}

void count_2(Long* result, int begin, int end, int order, int id, int num_proc) {
	int cur = begin + id;
	int i, j;
	Long l1;
	init(&l1, 0, order);
	divide(factorial(cur), &l1);
	for(i = begin + id; i <= end; i += num_proc) {
		//printf("cur = %d\n", i);
		//print(&l1);
		add(result, &l1, result);
		for(j = 0; j < num_proc; ++j) {
			cur++;
			divide_long(cur, &l1);
		}
			
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

void transform(Long* result, int rank, MPI_Status status) {
	Long res1, res2, res3;
	int tag = 7779;
	init(&res1, 0, result->size);
	init(&res2, 0, result->size);
	init(&res3, 0, result->size);
	if ( rank == 0 ) {
		MPI_Recv(res1.digits, res1.size, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(res2.digits, res2.size, MPI_INT, 2, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(res3.digits, res3.size, MPI_INT, 3, tag, MPI_COMM_WORLD, &status);	
	}
	else {
		MPI_Send(result->digits, result->size, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}
	if ( rank == 0 ) { 
		add(result, &res1, result);
		add(result, &res2, result);
		add(result, &res3, result);
		add_one(result);
		add_one(result);
		printf("exp = ");
		print(result);
	}
	clear(&res1);
	clear(&res2);
	clear(&res3);
}
		

int main(int argc, char** argv) {
	int p = check_input(argc, argv);
	int N = count_accuracy(p);	//До какога члена нужно считать раложение
	int commsize, rank;
	Long result;
	p *= AMENDMENT;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	Numbers t;
	init(&result, 0, p);
	Numbers_init(&t, &result, rank, commsize);
	//init(&result, 2, p);
	
	//printf("size = %d\n Number Teulor = %d\n", result.size, N);
	count_2(&result, 2, N, p, rank, commsize);
	//printf("work\nsize = %d\nreal_size = %d\n", result.size, p);
	//print(&result);
	//my_print(&t);
	if ( commsize == 4 ) {
		transform(&result, rank, status);
	}
	else {
		my_print(&t);
	}
	clear(&result);
	MPI_Finalize();
	return 0;
}
	
