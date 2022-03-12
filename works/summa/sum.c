#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>

#define error(str) fprintf(stderr, "%s\n", str)

typedef struct Numbers {
	int rank;
	int begin;
	int end;
	double sum;
} Numbers;

int check_arguments(int arg, char** argv) {
	if ( arg != 2 ) {
		error("Wrong numbers of arguments");
		exit(-1);
	}
	return atoi(argv[1]);
}

void mini_sum(Numbers* t) {
	double mini_sum = 0;
	int i = 0;
	for(i = t->begin; i <= t->end; ++i) {
		mini_sum += 1.0 / i;
	}
	t->sum = mini_sum;
}

void init(Numbers* t, int N) {
	int rank = t->rank;
	if ( rank == 0 ) {
		t->begin = 1;
		t->end = ceil(N / 4);
	}
	else if ( rank == 3 ) {
		t->begin = rank * ceil(N / 4) + 1;
		t->end = N;
	}
	else {
		t->begin = rank * ceil(N / 4) + 1;
		t->end = ( rank + 1 ) * ceil(N / 4);
	}
	mini_sum(t);
}


int main(int argc, char** argv) {
	int N = check_arguments(argc, argv);
	int commsize, rank;
	double reply = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	Numbers t;
	t.rank = rank;
	init(&t, N);
	printf("rank = %d, sum = %lf, begin = %d, end = %d\n", t.rank, t.sum, t.begin, t.end);
	MPI_Reduce(&(t.sum), &reply, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if ( rank == 0 ) {
		printf("my_rank = %d\tsum = %lf\n", rank, reply);
	}
	MPI_Finalize();
	return 0;
}
