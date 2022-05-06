#include "sort.hpp"

void TEST2(int num);

void TEST1(int num_threads, int num_elements) {				//merge_sort std::list on threads
	if ( num_threads == 1 ) {
		TEST2(num_elements);
		return;
	}
	std::vector<std::list<int>> lst{num_threads};
	int step = num_elements / num_threads;
	for(int i = 0; i < num_threads; ++i) {
		if ( i != num_threads - 1 ) {
			for(int j = 0; j < step; ++j) {
				lst[i].push_back(rand() % 1000);
			}
		}
		else {
			int new_step = step + ( num_elements % num_threads );
			for(int j = 0; j < new_step; ++j) {
				lst[i].push_back(rand() % 1000);
			}
		}
	}
	std::vector<std::thread> threads;
	int start = clock();
	for(int i = 0; i < num_threads; ++i) {
		void (*fps)(std::list<int>&) = &merge_sort;
		threads.push_back(std::thread(fps, std::ref(lst[i])));
	}
	for(std::thread& t : threads) {
		t.join();
	}
	for(int i = 0; i < num_threads - 1; ++i) {
		lst[i].merge(lst[i + 1]);
	}
	int end = clock();
	//print_list(lst[0]);
	std::cout << "TEST THREADS\ttime = " << (end - start) / (double) CLOCKS_PER_SEC << std::endl;
}

void TEST2(int num) {
	std::list<int> lst;
	for(int i = 0; i < num; ++i) {
		lst.push_back(rand() % 1000);
	}
	int start = clock();
	merge_sort(lst.begin(), lst.end());
	int end = clock();
	std::cout << "TEST2\ttime = " << (end - start) / (double) CLOCKS_PER_SEC << std::endl;
}

void TEST3(int num) {
	std::list<int> lst;
	for(int i = 0; i < num; ++i) {
		lst.push_back(rand() % 1001);
	}
	int start = clock();
	lst.sort();
	int end = clock();
        std::cout << "TEST STL\ttime = " << (end - start) / (double) CLOCKS_PER_SEC << std::endl;
}

int main(int argc, char** argv) {
	check_argc(argc);
	int num_threads = atoi(argv[1]);
	int num_elements = atoi(argv[2]);
	num_threads = check_atoi(num_threads);
	num_elements = check_atoi(num_elements);
	TEST1(num_threads, num_elements);
	TEST3(num_elements);
	return 0;
}
	
