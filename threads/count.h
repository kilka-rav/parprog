#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include <sys/sysinfo.h>



#define ERROR(message) fprintf(stderr, "LINE = %d\tFILE = %s\tMESSAGE: %s\n", __LINE__, __FILE__, message)
#define print(s) fprintf(stdout, "%d\n", s)

typedef struct _Threads {
	int id;
	double result;
	double len;
	int threads_num;
	pthread_t thread;
	double time;
} Threads;

void* count(void* param); 	//to parallel algo
double integrate(int id, double dx, int num, double a, double b);	//integrate
void check_arg(int argc);
int check_atoi(int num_threads);	
void print_time(Threads* threads);
double dynamic_step(double x, double len, double end, int n);
