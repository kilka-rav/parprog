#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <vector>

void check(int num) {
	bool flag = !(std::cin.good());
	if ( num < 0 ||  flag ) {
		std::cerr << "Wrong number" << std::endl;
		exit(1);
	}
}

double summa(int id, int num_thread, int num) {
	double mini_sum = 0;
	++id;
	while( id <= num ) {
		mini_sum += 1 / static_cast<double>(id);
		id += num_thread;
	}
	return mini_sum;
}

double summ_arr(std::vector<double>& arr) {
	double sum = 0;
	for(int i = 0; i < arr.size(); ++i) {
		sum += arr[i];
	}
	return sum;
}
			

int main() {
	double reply = 0.0;
	int num;
	std::cout << "Enter the number of row members" << std::endl;
	std::cin >> num;
	check(num);
	int max_threads = omp_get_max_threads();
	std::cout << "max threads: " << max_threads << std::endl;
	omp_set_dynamic(max_threads);
	std::vector<double> arr(max_threads);
#pragma omp parallel
{
	int num_thread = omp_get_num_threads();
	int id = omp_get_thread_num();
	arr[id] = summa(id, num_thread, num);
}
	reply = summ_arr(arr);
	std::cout << "Sum: " << reply << std::endl;
	return 0;
}
