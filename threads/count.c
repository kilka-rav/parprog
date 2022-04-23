#include "count.h"


double integrate(int id, double length, int num) {
	double a = ( (double) id ) * length / num;
	double b = ( (double) (id + 1)) * length / num;
	double eps = 0.0001;
	double result = 0;
	int n = 1 / ( M_PI * a);
	if ( n < 1 ) {
		n = 1;
	}
	double len = 1 / ( M_PI * n * (n + 1));
	double right = 1 / ( M_PI * n );
	double step = len / 100000;		//number of step on one 2pi
	double x = a;
	while( x - eps < b ) {
		if ( ( x > right ) && ( n != 1 ) ) {
			n--;
			right = 1 / ( M_PI * n );
			len = ( M_PI * n * (n + 1));
			step = len / 100000;
		}
		x += step;
		result += sin(1 / x) * 0.5 * step;
	}
	return result;
}

void* count(void* param) {
	Threads* t = (Threads*) param;
	struct timeval begin, end, interval;
	gettimeofday(&begin, NULL);
	t->result = integrate(t->id, t->len, t->threads_num);
	gettimeofday(&end, NULL);
	timersub(&end, &begin, &interval);
	t->time = interval.tv_sec + 0.000001 * interval.tv_usec;
	return NULL;
}

void check_arg(int argc) {
	if ( argc <= 1 ) {
		ERROR("ERROR IN INPUT");
		exit(1);
	}
}

int check_atoi(int num_threads) {
	if ( num_threads > get_nprocs() ) {
                fprintf(stdout, "num_threads < currency, programm should changed number of threads\n");
                num_threads = get_nprocs();
        }
	if ( num_threads <= 0 ) {
		ERROR("ERROR IN ATOI");
		exit(2);
	}
	return num_threads;
}

void print_time(Threads* threads) {
	int num = threads[0].threads_num;
	for(int i = 0; i < num; ++i) {
		printf("rang = %d time = %lf\n", threads[i].id, threads[i].time);
	}
}
