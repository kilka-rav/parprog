#include "numerov.h"



Grid::Grid(double a2, double b, double c, double d) {
    h = a2; //step
    epsilon = b; //error
    a = c; //coefficent
    num_points = d; //num_points
    std::cout << "Init grid" << std::endl;
}

void Grid::print_result(double start, double end) {
    std::cout << "Time: " << end - start << std::endl;
    std::ofstream stream;
    stream.open("output.txt");
    if ( stream.is_open() ) {
        std::cout << y.size() << std::endl;
        for(auto&& t : y_new) {
            stream << t << " ";
        }
    }
    else {
        std::cout << "file isn't open" << std::endl;
    }
    stream.close();
}

double Grid::getEpsilon() const {
    return epsilon;
}

void Grid::initial_solution() {
    int n = static_cast<int>(num_points);
    y.resize(n + 1);
    y_new.resize(n + 1);
    #pragma omp parallel for
    for (int i = 0; i < n + 1; ++i) {
        y[i] = 0.1;
        y_new[i] = 0.1;
    }
}

void Grid::count_alpha_gamma(double value) {
    int n = static_cast<int>(num_points);
    alpha.resize(n + 1);
    gamma.resize(n + 1);
    for(int i = 0; i < n + 1; ++i) {
        alpha[i] = value;
        gamma[i] = value;
    }
}

void Grid::count_beta() {
    int n = static_cast<int>(num_points);
    beta.resize(n + 1);
    #pragma omp parallel for
    for (int i = 1; i < n + 1; i++) {
        beta[i] = -2 - g_derivative(y[i], a) * h * h;
    }
}

void Grid::count_F() {
    int n = static_cast<int>(num_points);
    F.resize(n + 1);
    #pragma omp parallel for
    for (int i = 1; i < n; i++) {
        F[i] = (numerov(y[i - 1], y[i], y[i + 1], a) - y[i] * g_derivative(y[i], a)) * h * h;
    }
}

void Grid::cycle_parallel() {
    int start = 2;
    int step = 1;
    int nelem = num_points - 1;
    int barrier = static_cast<int>(log2(num_points));
    for(int p = 0; p < barrier; ++p) {
        nelem = (nelem - 1) / 2;
    #pragma omp parallel for
        for(int i = 0; i < nelem; ++i) {
            forward(i, start, step);
        }
        start <<= 1;
        step <<= 1;
    }
    //backward
    start = num_points / 2;
    step = num_points / 2;
    nelem = 1;
    for (int p = 0; p < barrier; p++) {
#pragma omp parallel for
        for (int i = 0; i < nelem; i++)
            backward(i, start, step);
        start >>= 1;
        step >>= 1;
        nelem <<= 1;
    }
}

void Grid::forward(int i, int start, int step) {
    int k = start * (i + 1);

    double alpha_val = -(alpha[k] * alpha[k - step]) / beta[k - step];
    double gamma_val = -(gamma[k] * gamma[k + step]) / beta[k + step];
    double beta_val = beta[k] - gamma[k - step] * alpha[k] / beta[k - step] - gamma[k] * alpha[k + step] / beta[k + step];
    double f_val = F[k] - alpha[k] * F[k - step] / beta[k - step] - gamma[k] * F[k + step] / beta[k + step];

    alpha[k] = alpha_val;
    beta[k] = beta_val;
    gamma[k] = gamma_val;
    F[k] = f_val;
}

void Grid::backward(int i, int start, int step) {
    int k = start * (2 * i + 1);
    double out = F[k] - gamma[k] * y_new[k + step] - alpha[k] * y_new[k - step];
    y_new[k] = out / beta[k];
}

double Grid::compare() {
    y_new[0] = y_new[num_points] = sqrt(2);
    double res = 0;
    for(int i = 0; i < y.size(); ++i) {
        res = std::max(res, std::fabs(y[i] - y_new[i]));
    }
    return res;
}

double func(double y, double A) {
    return A * (y * y * y - y);
}

double g_derivative(double y, double A) {
    return A * (3 * y * y - 1);
}

double numerov(double y_left, double y, double y_right, double A) {
    return (func(y_left, A) + 10. * func(y, A) + func(y_right, A)) / 12.;
}