#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <array>
#include "test.hpp"



std::vector<std::array<double, Jsz>> sequential(const std::vector<std::array<double, Jsz>>& a) {
    auto res = a;
    double start_time = omp_get_wtime();
    for(int i = 0; i < Isz; ++i) {
        for(int j = 0; j < Jsz; ++j) {
            res[i][j] = sin(2 * a[i][j]);
        }
    }
    double end_time = omp_get_wtime();
    std::cout << "Sequential time: " << end_time - start_time << std::endl;
    return res;
}

std::vector<std::array<double, Jsz>> parallel(const std::vector<std::array<double, Jsz>>& a) {
    auto res = a;
    double start_time = omp_get_wtime();
#pragma omp parallel for shared(a, res)    
    for(int i = 0; i < Isz; ++i) {
        for(int j = 0; j < Jsz; ++j) {
            res[i][j] = sin(2 * a[i][j]);
        }
    }
    double end_time = omp_get_wtime();
    std::cout << "Parallel time: " << end_time - start_time << std::endl;
    return res;
}


int main(int argc, char** argv) {
    std::cout << "OMP" << std::endl;
    std::vector<std::array<double, Jsz>> a(Isz);

    //подготовительная часть - заполнение некими данными
    for(int i = 0; i < Isz; ++i) {
        for(int j = 0; j < Jsz; ++j) {
            a[i][j] =  (10 * i + j);
        }
    }
    std::cout << "test1\n";
    auto&& result1 = sequential(a);
    auto&& result2 = parallel(a);
    return 0;
}