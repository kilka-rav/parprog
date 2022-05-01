#include "count.h"

double integrate(double a, double b) {
	double result = 0;
	double eps = 0.000001;
	int n = 1 / ( M_PI * 10);
	if ( n < 1 ) {
		n = 1;
	}
	double len = 1 / ( M_PI * n * (n + 1));
	double right = 1 / ( M_PI * n );
	double step = len / 100000;		//number of step on one 2pi
	double x = a;
	double prev;
	while( x < b ) {
		if ( ( x > right ) && ( n != 1 ) ) {
			n--;
			right = 1 / ( M_PI * n );
			len = ( M_PI * n * (n + 1));
			step = len / 100000;
		}
		double tmp = function(x);
		x += step;
		if ( x + eps >= b ) {
			break;
		}
		tmp += function(x);
		tmp *= 0.5 * step;
		result += tmp;
	}
	x -= step;
	result += 0.5 * (function(b) + function(x)) * ( b - x );
	return result;
}


double function(double x) {
	return sin(1 / x);
}


void* count(void* param) {
	Threads* t = (Threads*) param;
	struct timeval begin, end, interval;
	count_interval(t);
	gettimeofday(&begin, NULL);
	t->result = integrate(t->a, t->b);
	gettimeofday(&end, NULL);
	timersub(&end, &begin, &interval);
	t->time = interval.tv_sec + 0.000001 * interval.tv_usec;
	return NULL;
}

void count_interval(Threads* t) {
	if ( t->id == 0 ) {
		t->a = t->begin;
		if ( t->threads_num == 1 ) {
			t->b = t->end;
		}
		else {
			t->b = ( (double) (t->id + 1) * t->len / t->threads_num);
		}
	}

	else {
		t->a = ( (double) (t->id) * t->len / t->threads_num );
		t->b = ( (double) (t->id + 1) * t->len / t->threads_num);
	}
	if ( t->id == t->threads_num - 1 ) {
		t->b = t->end;
	}
}



void check_arg(int argc) {
	if ( argc <= 1 ) {
		ERROR("ERROR IN INPUT");
		exit(1);
	}
}

int check_atoi(int num_threads) {
	//if ( num_threads > get_nprocs() ) {
        //        fprintf(stdout, "num_threads < currency, programm should changed number of threads\n");
        //        num_threads = get_nprocs();
        //}
	if ( num_threads <= 0 ) {
		ERROR("ERROR IN ATOI");
		exit(2);
	}
	return num_threads;
}

void print_time(Threads* threads) {
	int num = threads[0].threads_num;
	for(int i = 0; i < num; ++i) {
		printf("rang = %d a = %lf, b = %lf, result = %lf, time = %lf\n", threads[i].id, threads[i].a, threads[i].b, threads[i].result, threads[i].time);
	}
}
