#include "numerov.h"


int main() {
	omp_set_num_threads(4);
	Grid grid(0.001220703125, 0.001, 1000, 16384);

	double currentEpsilon = 1.0;
	grid.initial_solution();
	double startTime = omp_get_wtime();
	int iter = 0;
	while ( currentEpsilon > grid.getEpsilon() ) {
		grid.count_beta();
		grid.count_F();
		grid.count_alpha_gamma(1.0);
		grid.cycle_parallel();
		currentEpsilon = grid.compare();
		std::swap(grid.y, grid.y_new);
		
	}
	double endTime = omp_get_wtime();
	grid.print_result(startTime, endTime);
	return 0;
}
