#include "fft.h"

#include <fstream>

int main(int argc, char **argv)
{
    std::vector<double> resOpt;
    std::vector<double> res;
    // generate signal
    for(int index = 10; index < 20; ++index) {
    	size_t N = std::pow(2, index);
    	std::cout << "N: " << N << std::endl;
    	const double m = 4.0;
    	std::vector<std::complex<double>> x(N);
    	for (size_t i = 0; i < N; ++i) {
        	x[i] = std::sin(2 * M_PI / N * m * i) + std::sin(2 * M_PI / N * (m + 0.25) * i);
    	}


    	double start_time = omp_get_wtime();
    	auto && res_opt = fft::fft_opt(x);
    	double end_time = omp_get_wtime();
    	std::cout << "Time opt: " << end_time - start_time << std::endl;
	res.push_back(end_time - start_time);


    	start_time = omp_get_wtime();
    	auto && res_opt_par = fft::fft_opt_par(x);
    	end_time = omp_get_wtime();
    	std::cout << "Time opt par: " << end_time - start_time << std::endl;
	resOpt.push_back(end_time - start_time);
    }
    std::ofstream fileRes("result1.txt");
    std::ofstream file("result2.txt");
    for (int i = 0; i < res.size(); ++i) {
        fileRes << res[i] << std::endl;
	file << resOpt[i] << std::endl;
    }
    fileRes.close();
    file.close();

    return 0;
}
