#include "count.h"


int main(int argc, char** argv) {
	check_number_arguments(argc);
	int M_step, T_step;	//number of step
	convert_to_step(argv, &M_step, &T_step);
	printf("%d %d\n", M_step, T_step);
	double m = ( end_x - begin_x ) / M_step;
	double t = ( end_t - begin_t ) / T_step;
	Data grid;
	init_grid(&grid, M_step, T_step);
	init_conditions(&grid, m, t);
	print_grid(&grid);
	solution(&grid, m, t);
	print_grid(&grid);
	clear_grid(&grid);
	printf("%lf %lf\n", m, t);
	return 0;
}

