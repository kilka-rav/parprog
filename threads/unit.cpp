#include <iostream>
#include <fstream>
#include "count.h"


int check_arguments(int argc, char** argv) {
	int res = 16;
	if ( argc == 2 ) {
		res = atoi(argv[1]);
		if ( res == 0 ) {
			ERROR("ERROR IN ATOI");
			exit(1);
		}
	}
	else if ( argc == 1 ) {
		std::cout << "AUTO 16 Threads" << std::endl;
	}
	else {
		ERROR("ERROR IN INPUT UNIT_TEST");
		exit(1);
	}
	return res;
}

void compare(int num, std::string& base) {
	std::string mini_s = std::to_string(1);
	std::string main_result;
	std::string other_result;
	std::string mini_base = base + mini_s;
	std::ifstream in(mini_base);
	if ( in.is_open() ) {
		getline(in, main_result);
	}
	//std::cout << main_result << std::endl;
	in.close();
	for(int i = 2; i <= num; ++i) {
		std::string line = base + std::to_string(i);
		std::ifstream res(line);
		if ( res.is_open() ) {
			getline(res, other_result);
			size_t pos = other_result.find("result");
			if ( pos == std::string::npos ) {
				getline(res, other_result);
			}
			if ( main_result == other_result ) {
				std::cout << "UNIT_TEST" << i << " OK" << std::endl;
			}
			else {
				std::cout << "UNIT_TEST" << i << " NOT_OK" << std::endl;
			}
			//std::cout << other_result << std::endl;
		}
		res.close();
	}
}




int main(int argc, char** argv) {
	int num = check_arguments(argc, argv);
	std::string begin = "./run ";
	std::string kek = " > ";
	std::string name = "test_res";
	for(int i = 1; i <= num; ++i) {
		std::string s = std::to_string(i);
		std::string mini_s = begin + s + kek + name + s;
		std::cout << mini_s << std::endl;
		system(mini_s.c_str());
	}
	compare(num, name);
	return 0;
}
		
