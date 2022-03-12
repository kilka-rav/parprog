#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char** argv) {
	int commsize, rank, prev, next;
	int buf[2];
	MPI_Status stats[4];
	MPI_Request reqs[4];
	int tag1 = 111;
	int tag2 = 222;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	prev = rank - 1;
	next = rank + 1;
	if ( prev < 0 ) {
		prev = commsize - 1;
	}
	if ( next >= commsize ) {
		next = 0;
	}
	MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
	MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);
	MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[2]);
	MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[3]);
	MPI_Waitall(4, reqs, stats);
	printf("id = %d\tprev = %d\tnext = %d\n", rank, buf[0], buf[1]);
	MPI_Finalize();
	return 0;
}

