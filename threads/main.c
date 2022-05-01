#include "count.h"

int main(int argc, char** argv) {
	check_arg(argc);
	int threads_num = atoi(argv[1]);
	threads_num = check_atoi(threads_num);
	double begin = 0.0001;
	double end = 5.0;
	double len = end - begin;
	double res = 0;
	void* kek;
	Threads* threads = (Threads*) malloc(threads_num * sizeof(Threads));
	for(int i = 0; i < threads_num; ++i) {
		threads[i].id = i;
		threads[i].begin = begin;
		threads[i].end = end;
		threads[i].len = len;
		threads[i].result = 0;
		threads[i].threads_num = threads_num;
		if ( pthread_create(&(threads[i].thread), NULL, count, &(threads[i])) == -1 ) {
			ERROR("ERROR IN CREATE THREADS");
		}
	}
	for(int i = 0; i < threads_num; ++i) {
		if ( pthread_join(threads[i].thread, &(kek)) == -1 )  {
			ERROR("ERROR IN JOIN THREADS");
		}
		res += threads[i].result;
	}
	printf("result = %.5lf\n", res);
	print_time(threads);
	free(threads);
	return 0;
}
