#include "fft.h"

namespace fft
{


    size_t bitReverse(size_t x, size_t log2n)
    {
        int n = 0;
        for (int i = 0; i < log2n; i++)
        {
            n <<= 1;
            n |= (x & 1);
            x >>= 1;
        }
        return n;
    }

    std::vector<std::complex<double>> fft_opt(std::vector<std::complex<double>> &xIn)
    {
        std::complex<double> J = {0, 1};
        auto N = xIn.size();
        auto log2n = std::bit_width(N) - 1;
        int n = 1 << log2n;

        std::vector<std::complex<double>> res(N);
        for (unsigned int i = 0; i < n; ++i)
        {
            res[bitReverse(i, log2n)] = xIn[i];
        }
        for (int s = 1; s <= log2n; ++s)
        {
            int m = 1 << s;
            int m2 = m >> 1;
            std::complex<double> w(1, 0);
            std::complex<double> wm = exp(-J * (M_PI / m2));
            for (int j = 0; j < m2; ++j)
            {
                for (int k = j; k < n; k += m)
                {
                    std::complex<double> t = w * res[k + m2];
                    std::complex<double> u = res[k];
                    res[k] = u + t;
                    res[k + m2] = u - t;
                }
                w *= wm;
            }
        }
        return res;
    }

    std::vector<std::complex<double>> fft_opt_par(std::vector<std::complex<double>> &xIn)
    {
        std::complex<double> J = {0, 1};
        auto N = xIn.size();
        auto log2n = std::bit_width(N) - 1;
        int n = 1 << log2n;

        std::vector<std::complex<double>> res(N);
        #pragma omp parallel for shared(res, xIn)
        for (int i = 0; i < n; ++i)
        {
            res[bitReverse(i, log2n)] = xIn[i];
        }
        
        //#pragma omp parallel for shared(res)
        for (int s = 1; s <= log2n; ++s)
        {
            int m = 1 << s;
            int m2 = m >> 1;
            std::complex<double> w(1, 0);
            std::complex<double> wm = exp(-J * (M_PI / m2));
            #pragma omp parallel for shared(res)
            for (int j = 0; j < m2; ++j)
            {
                for (int k = j; k < n; k += m)
                {
                    std::complex<double> t = w * res[k + m2];
                    std::complex<double> u = res[k];
                    res[k] = u + t;
                    res[k + m2] = u - t;
                }
                w *= wm;
            }
        }
        return res;
    }

} // namespace fft