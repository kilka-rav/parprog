#include <iostream>
#include <omp.h>
#include <stdio.h>

int main() {
#pragma omp parallel
{
	int num_threads = omp_get_num_threads();
	int id = omp_get_thread_num();
	printf("Hello everyone threads: %d. My name is %d\n", num_threads, id);
}
	return 0;
}
