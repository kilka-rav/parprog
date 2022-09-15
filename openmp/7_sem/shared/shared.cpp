#include <iostream>
#include <omp.h>
#include <stdio.h>


int main() {
        int shared = 0;
	int cur = 0;
#pragma omp parallel
{
        int id = omp_get_thread_num();
	while(1) {
                if ( cur == id ) {
                        shared += id;
                        printf("my id %d, shared += id %d\n", id, shared);
			cur++;
                        break;
                }
        }
}
        return 0;
}
