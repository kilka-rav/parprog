#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "omp.h"


class Grid {
    double h;
    double epsilon;
    double a;
    double num_points;
    double left = -10;
public:
    Grid(double a, double b, double c, double d);
    void print_result(double start, double end);
    double getEpsilon() const;
    void initial_solution();

    void count_beta();
    void count_F();
    void count_alpha_gamma(double value);
    void cycle_parallel();
    double compare();

    void backward(int a, int b, int c);
    void forward(int a, int b, int c);

    std::vector<double> alpha;
	std::vector<double> beta;
	std::vector<double> gamma;
	std::vector<double> F;
	std::vector<double> y;
	std::vector<double> y_new;
};

double g_derivative(double y, double A);
double numerov(double y_left, double y, double y_right, double A);
double func(double y, double A);