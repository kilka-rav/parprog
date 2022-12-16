#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <mpi.h>

#include <vector>
#include <array>


const int JSIZE = 10000;
const int ISIZE = 10000;
const bool TEST_SEQ = true;


int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank = 0, comm_size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (rank == 0) {
        std::cout << "Size: " << JSIZE << "x" << ISIZE << std::endl;
    }

    std::vector<std::array<double, JSIZE>> a(ISIZE);
    //подготовительная часть – заполнение некими данными
    for (size_t i = 0; i < ISIZE; i++) {
        for (size_t j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }

    double start_time = MPI_Wtime();

    int start_col = rank * (JSIZE - 1) / comm_size;
    int stop_col = (rank + 1) * (JSIZE - 1) / comm_size - 1;

    for (int line = 1; line < ISIZE; line++) {
        // get right border from next process
        if (rank != comm_size - 1 and line > 2)
            MPI_Recv(&(a[line - 1][stop_col + 1]), 2, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, &status);

        for (int column = stop_col; column >= start_col; column--)
            a[line][column] = sin(2 * a[line + 1][column - 1]);

        // send left border
        if (rank != 0 and line < ISIZE - 1)
            MPI_Send(&(a[line][start_col]), 2, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD);
    }

    // collect all data
    if (rank != 0) {
        for (int line = 1; line < ISIZE; line++) {
            MPI_Send(&(a[line][start_col]), stop_col - start_col + 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
        }
    } 
    else {
        for (int sender_rank = 1; sender_rank < comm_size; sender_rank++) {
            int sender_start_col = sender_rank * (JSIZE + 1) / comm_size;
            int sender_stop_col = (sender_rank + 1) * (JSIZE + 1) / comm_size - 1;

            for (int line = 1; line < ISIZE; line++) {
                MPI_Recv(&(a[line][sender_start_col]), sender_stop_col - sender_start_col + 1, MPI_DOUBLE, sender_rank, 1, MPI_COMM_WORLD, &status);
            }
        }
    }


    double duration = MPI_Wtime() - start_time;

    if (rank == 0) {
        std::cout << "Time par: " << duration << " sec" <<  std::endl;

        // compare with seq way
        if (TEST_SEQ) {
            std::vector<std::array<double, JSIZE>> a_seq(ISIZE);

            for (size_t i = 0; i < ISIZE; i++) {
                for (size_t j = 0; j < JSIZE; j++) {
                    a_seq[i][j] = 10 * i + j;
                }
            }
            double start_seq = MPI_Wtime();

            for (size_t i = 1; i < ISIZE; i++) {
                for (size_t j = 0; j < JSIZE - 1; j++) {
                    a_seq[i][j] = std::sin(2 * a_seq[i - 1][j + 1]);
                }
            }
            std::cout << "Time seq: " << MPI_Wtime() - start_seq << " sec" << std::endl;

            size_t loss = 0;
            for (size_t i = 0; i < ISIZE; i++)
            {
                for (size_t j = 0; j < JSIZE; j++)
                {
                    loss += (a_seq[i][j] != a[i][j]);
                }
            }
            std::cout << "Loss: " << loss << std::endl;
        }
    }

    MPI_Finalize();

    return 0;
}
