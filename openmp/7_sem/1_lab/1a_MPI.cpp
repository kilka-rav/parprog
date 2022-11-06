#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <algorithm>
#include <numeric>
#include <vector>
#include <array>
#include <iostream>
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include "test.hpp"

std::vector<std::array<double, JSIZE>> sequential(const std::vector<std::array<double, JSIZE>> &a)
{
    auto result = a;

    for (size_t i = 3; i < ISIZE; i++)
    {
        for (size_t j = 0; j < JSIZE - 2; j++)
        {
            result[i][j] = std::sin(3 * result[i - 3][j + 2]);
        }
    }

    return result;
}

int main(int argc, char **argv)
{
    std::vector<std::array<double, JSIZE>> a(ISIZE);
    for (size_t i = 0; i < Isz; i++)
    {
        for (size_t j = 0; j < Jsz; j++)
        {
            a[i][j] = 10 * i + j;
        }
    }

    auto a_seq = sequential(a);

    MPI_Init(&argc, &argv);

    int num_proc = 0;
    int proc_id = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    double startTime = 0.f, endTime = 0.f;
    if ( proc_id == 0 ) {
        std::cout << "Num processes: " << num_proc << std::endl;
        startTime = MPI_Wtime();
    }

    std::vector<std::array<double, JSIZE>> a_par;
    int step = Jsz / num_proc;
    int start = proc_id * step;
    int end = start + step;

    if ( proc_id == 0 ) {
        a_par = a_seq;
    } else if ( proc_id == num_proc - 1 ) {
        a_par.resize(step - 2);
        for(int i = 1; i < Isz; ++i) {
            for(int j = start; j < end - 1; ++j) {
                a_par[i][j] = sin(2 * a[i-1][j+1]);
            }
        }
    }
    if (proc_id == 0)
    {
        endTime = MPI_Wtime();
    }
    MPI_Finalize();
    compare(a_par, a_seq);
    return 0;
}