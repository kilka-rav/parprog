#pragma once
#include <iostream>
#include <vector>

#define Isz 5000
#define Jsz 5000

void compare(const std::vector<std::array<double, Jsz>>& a, const std::vector<std::array<double, Jsz>>& b) {
    double epsilon = 0.001;
    for(int i = 0; i < Isz; ++i) {
        for(int j = 0; j < Jsz; ++j) {
            if ( abs(a[i][j] - b[i][j]) > epsilon) {
                std::cout << "TEST FAILED" << std::endl;
                return;
            }
        }
    }
    std::cout << "TEST OK" << std::endl;
}