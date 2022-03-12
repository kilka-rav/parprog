#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
	int commsize, my_rank;
	printf("Before MPI_INIT\n");
	MPI_Init(&argc, &argv);
	printf("parallel_section\n");
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	printf("Communicator_size = %d\nmy_rank = %d\n", commsize, my_rank);
	//MPI_send, MPI_recv
	MPI_Finalize();
	//printf("After MPI_FINALIZE\n");
}
