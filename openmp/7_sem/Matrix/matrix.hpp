#pragma once
#pragma vector
#include <iostream>
#include <fstream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
#include <chrono>
#include <thread>
#include <vector>
#include <immintrin.h>
#define my_print(s) std::cout << s << std::endl

namespace linear {
    class Matrix {
        private:
            int row;
            int col;
        public:
            int** arr;
            Matrix(int _row, int _col);
            Matrix(int _row, int _col, int** _arr);
            Matrix(Matrix& A);
            Matrix(Matrix& A, int a);               //it is constructor first version
            int get_row() const;
            int get_col() const;
            bool mul_impr(const Matrix& right, Matrix& result);
            bool mul(Matrix& right, Matrix& result);          //it is mul first version
            bool mul_thread(const Matrix& right, Matrix& result);
            bool mul_intrinsic(const Matrix& right, Matrix& result);
            bool strassen(linear::Matrix& D_A, linear::Matrix& D1_A, linear::Matrix& D2_A, \
                linear::Matrix& H1_A, linear::Matrix& H2_A, linear::Matrix& V1_A, linear::Matrix& V2_A, \
                linear::Matrix& D_B, linear::Matrix& D1_B, linear::Matrix& D2_B, \
                linear::Matrix& H1_B, linear::Matrix& H2_B, linear::Matrix& V1_B, linear::Matrix& V2_B, \
                linear::Matrix& D, linear::Matrix& D1, linear::Matrix& D2, linear::Matrix& H1, \
                linear::Matrix& H2, linear::Matrix& V1, linear::Matrix& V2, \
                linear::Matrix& result1, linear::Matrix& result2, linear::Matrix& result3, linear::Matrix& result4, \
                linear::Matrix& result);
            void before_calc(linear::Matrix& result, int x1, int x2, int y1, int y2, bool flag);
            void before_calc(linear::Matrix& result, int x, int y);
            bool compare(const Matrix& B) const;
            void sum(linear::Matrix& A, linear::Matrix& B, linear::Matrix& result);
            void sub(linear::Matrix& A, linear::Matrix& B, linear::Matrix& result);
            void complex_sum_strassen(linear::Matrix& A, linear::Matrix& B, linear::Matrix& C, linear::Matrix& D, linear::Matrix& res);
            void print() const;
            void record(std::string name) const;
            ~Matrix();
    };

    Matrix::Matrix(int _row, int _col) {
        row = _row;
        col = _col;
        arr = new int*[row];
        for(int i = 0; i < row; ++i) {
            arr[i] = new int[col];
        }
    }
    
    Matrix::Matrix(int _row, int _col, int** _arr) {
        row = _row;
        col = _col;
        arr = new int*[row];
        for(int i = 0; i < row; ++i) {
            arr[i] = new int[col];
        }
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                arr[i][j] = _arr[i][j];
            }
        }
    }

    int Matrix::get_row() const {
        return row;
    }

    int Matrix::get_col() const {
        return col;
    }

    Matrix::Matrix(Matrix& A) {
        row = A.row;
        col = A.col;
        arr = new int*[row];
        for(int i = 0; i < row; ++i) {
            arr[i] = new int[col];
        }
        for(int j = 0; j < col; ++j) {
            int i = 7;
            while( i < row ) {
                arr[i-7][j] = A.arr[i-7][j];
                arr[i-6][j] = A.arr[i-6][j];
                arr[i-5][j] = A.arr[i-5][j];
                arr[i-4][j] = A.arr[i-4][j];
                arr[i-3][j] = A.arr[i-3][j];           //add loop unrolling
                arr[i-2][j] = A.arr[i-2][j];
                arr[i-1][j] = A.arr[i-1][j];
                arr[i][j] = A.arr[i][j];
                i += 8;
            }
            i -= 8;
            if ( row < 8 ) {                      //ch                              
                for(int it = 0; it < row; ++it) {
                    arr[it][j] = A.arr[it][j];
                }
            }
            else if ( row % 8 != 0 ) {
                for(int it = i + 1; it < row; ++it) {
                    arr[it][j] = A.arr[it][j];
                }
            }
        }
    }

    Matrix::Matrix(Matrix& A, int aa) {
        row = A.row;
        col = A.col;
        arr = new int*[row];
        for(int i = 0; i < row; ++i) {
            arr[i] = new int[col];
        }
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                arr[i][j] = A.arr[i][j];
            }
        }
    }

    Matrix::~Matrix() {
        for(int i = 0; i < row; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
    }

    void Matrix::sum(linear::Matrix& A, linear::Matrix& B, linear::Matrix& result) {
        bool flag = A.get_row() == row;
        bool falg = A.get_col() == col;
        flag = falg && flag;
        if ( !flag ) {
            std::cout << "Incorrect size in sum" << std::endl;
        }
        for(int i = 0; i < row; ++i ) {
            for(int j = 0; j < col; ++j) {
                result.arr[i][j] = A.arr[i][j] + B.arr[i][j];
            }
        }
    }

    void Matrix::sub(linear::Matrix& A, linear::Matrix& B, linear::Matrix& result) {
        bool flag = B.get_row() == row;
        bool falg = B.get_col() == col;
        flag = falg && flag;
        if ( !flag ) {
            std::cout << "Incorrect size in sub" << std::endl;
        }
        for(int i = 0; i < row; ++i ) {
            for(int j = 0; j < col; ++j) {
                result.arr[i][j] = A.arr[i][j] - B.arr[i][j];
            }
        }
    }

    void Matrix::print() const {
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void Matrix::record(std::string name) const {
        std::ofstream fout(name);
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                fout << arr[i][j] << " ";
            }
            fout << std::endl;
        }
        fout.close();
    }
    
    bool Matrix::mul_intrinsic(const Matrix& right, Matrix& result) {
        if ( col != right.row ) {
            std::cout << "WRONG! Incorrect matrix dimensions are set\n";
            return false;
        }
        int M = result.row;
        int N = result.col;
        int num = 0;
        int num1 = 0;
        int c = 0;
        int block = sizeof(__m128i) / sizeof(int);
        if ( col < block ) {
            this->mul_impr(right, result);
            return true;
        }
        for(int j = 0; j < N; ++j) {
            int Y[col];
            for(int q = 0; q < col; ++q) {
                Y[q] = right.arr[q][num];
            }
            num++;
            __m128i* Yb = (__m128i*) Y;
            c = 0;
            num1 = 0;
            for(int i = 0; i < M; ++i) {
                int X[col];                     
                __m128i* Yb = (__m128i*) Y;
                for(int q = 0; q < col; ++q) {
                    X[q] = arr[num1][q];
                }
                num1++;
                __m128i* Xa = (__m128i*) X;
                __m128i val_c = _mm_setzero_si128();
                for(int k = 0; k < col / block; ++k) {
                    __m128i val_a = _mm_load_si128(Xa);
                    __m128i val_b = _mm_load_si128(Yb);
                    __m128i mul = _mm_mullo_epi32(val_a, val_b);
                    val_c = _mm_add_epi32(val_c, mul);
                    Xa++;
                    Yb++;
                }                                               
                __m128i tmp = _mm_hadd_epi32(val_c, val_c);
                __m128i tmp2 = _mm_hadd_epi32(tmp, tmp);  
                c = _mm_cvtsi128_si32(tmp2);
                int tail = 0;
                for (size_t i = (col / block) * block; i < col; i++) {                  //считаем остаток
                    tail += X[i] * Y[i];
                }
                result.arr[i][j] = c + tail;
            }
        }
        return true;
    }

    bool Matrix::mul_impr(const Matrix& right, Matrix& result) {              // Matrix C = A * B;
        if ( col != right.row ) {
            std::cout << "WRONG! Incorrect matrix dimensions are set\n";
            return false;
        }
        int M = result.row;
        int N = result.col;
        int num = 0;
        int c = 0;
        for(int j = 0; j < N; ++j) {
            int Y[col];           //столбец
            for(int q = 0; q < col; ++q) {
                Y[q] = right.arr[q][num];
            }
            num++;
            for(int i = 0; i < M; ++i) {            //ускорение перестановкой циклов, вынос переменных
                c = 0;
                int k = 7;
                while ( k < col ) {                 //loop unrolling
                    c += arr[i][k-7] * Y[k-7];
                    c += arr[i][k-6] * Y[k-6];
                    c += arr[i][k-5] * Y[k-5];
                    c += arr[i][k-4] * Y[k-4];
                    c += arr[i][k-3] * Y[k-3];
                    c += arr[i][k-2] * Y[k-2];
                    c += arr[i][k-1] * Y[k-1];
                    c += arr[i][k] * Y[k];
                    k += 8;
                }
                k -= 8;
                if ( col < 8 ) {                                              //ch
                    for(int ik = 0; ik < col; ++ik) {
                        c += arr[i][ik] * Y[ik];
                    }
                }
                else if ( col % 8 != 0 ) {
                    for(int ik = k + 1; ik < col; ++ik) {
                        c += arr[i][ik] * Y[ik];
                    }
                }
                result.arr[i][j] = c;
            }
        }
        //result.print();
        return true;
        
    }
    
    void mini_mul(const linear::Matrix& A, const linear::Matrix& B, int m1, int m2, int k1, int k2, int len, linear::Matrix& result) {
        int M = result.get_row();
        int N = result.get_col();
        int num = k1;
        int c = 0;
        for(int j = 0; j < N; ++j) {
            int Y[len];           //столбец
            for(int q = 0; q < len; ++q) {
                Y[q] = B.arr[q][num];
            }
            num++;
            for(int i = 0; i < M; ++i) {            //ускорение перестановкой циклов, вынос переменных
                c = 0;
                int k = 7;
                while ( k < len ) {                 //loop unrolling
                    c += A.arr[m1 + i][k-7] * Y[k-7];
                    c += A.arr[m1 + i][k-6] * Y[k-6];
                    c += A.arr[m1 + i][k-5] * Y[k-5];
                    c += A.arr[m1 + i][k-4] * Y[k-4];
                    c += A.arr[m1 + i][k-3] * Y[k-3];
                    c += A.arr[m1 + i][k-2] * Y[k-2];
                    c += A.arr[m1 + i][k-1] * Y[k-1];
                    c += A.arr[m1 + i][k] * Y[k];
                    k += 8;
                }
                k -= 8;
                if ( len < 8 ) {                                              //ch
                    for(int ik = 0; ik < len; ++ik) {
                        c += A.arr[m1 + i][ik] * Y[ik];
                    }
                }
                else if ( len % 8 != 0 ) {
                    for(int ik = k + 1; ik < len; ++ik) {
                        c += A.arr[m1 + i][ik] * Y[ik];
                    }
                }
                result.arr[i][j] = c;
            }
        }
    }

    void union_matrix(linear::Matrix& result, linear::Matrix& res1, linear::Matrix& res2, linear::Matrix& res3, linear::Matrix& res4) {
        int m1 = res1.get_row();                                                                    //WORK
        int k1 = res1.get_col();
        int m = result.get_row();
        int k = result.get_col();
        int k2 = res2.get_col();
        for(int i = 0; i < m1; ++i) {                               
            for(int j = 0; j < k1; ++j) {
                result.arr[i][j] = res1.arr[i][j];
            }
        }
        for(int i = 0; i < m1; ++i) {
            for(int j = k1; j < k; ++j) {
                result.arr[i][j] = res2.arr[i][j - k1];
            }
        }
        for(int i = m1; i < m; ++i) {
            for(int j = 0; j < k1; ++j) {
                result.arr[i][j] = res3.arr[i - m1][j];
            }
        }
        for(int i = m1; i < m; ++i) {
            for(int j = k1; j < k; ++j) {
                result.arr[i][j] = res4.arr[i - m1][j - k1];
            }
        }
    }
    
    bool Matrix::mul_thread(const Matrix& right, Matrix& result) {
        if ( col != right.row ) {
            std::cout << "WRONG! Incorrect matrix dimensions are set\n";
            return false;
        }
        std::vector<std::thread> threads;
        int m1 = row / 2;
        int m2 = row - m1;
        int k1 = right.get_col() / 2;
        int k2 = right.get_col() - k1;
        int len = right.row;
        linear::Matrix left(row, col, arr);
        linear::Matrix result1(m1, k1);
        linear::Matrix result2(m1, k2);
        linear::Matrix result3(m2, k1);
        linear::Matrix result4(m2, k2);
        threads.push_back(std::thread(mini_mul, std::ref(left), std::ref(right), 0, m1, 0, k1, len, std::ref(result1)));
        threads.push_back(std::thread(mini_mul, std::ref(left), std::ref(right), 0, m1, k1, k1 + k2, len, std::ref(result2)));
        threads.push_back(std::thread(mini_mul, std::ref(left), std::ref(right), m1, 0, 0, k1, len, std::ref(result3)));
        threads.push_back(std::thread(mini_mul, std::ref(left), std::ref(right), m1, m1 + m2, k1, k1 + k2, len, std::ref(result4)));
        for(std::thread& t : threads) {
            t.join();
        }
        union_matrix(result, result1, result2, result3, result4);
        return true;
    }

    void Matrix::complex_sum_strassen(linear::Matrix& A, linear::Matrix& B, linear::Matrix& C, linear::Matrix& D, linear::Matrix& res) {
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                res.arr[i][j] = A.arr[i][j] + B.arr[i][j] + C.arr[i][j] - D.arr[i][j];
            }
        }
    }

    bool Matrix::strassen(linear::Matrix& D_A, linear::Matrix& D1_A, linear::Matrix& D2_A, \
        linear::Matrix& H1_A, linear::Matrix& H2_A, linear::Matrix& V1_A, linear::Matrix& V2_A, \
        linear::Matrix& D_B, linear::Matrix& D1_B, linear::Matrix& D2_B, \
        linear::Matrix& H1_B, linear::Matrix& H2_B, linear::Matrix& V1_B, linear::Matrix& V2_B, \
        linear::Matrix& D, linear::Matrix& D1, linear::Matrix& D2, linear::Matrix& H1, \
        linear::Matrix& H2, linear::Matrix& V1, linear::Matrix& V2, \
        linear::Matrix& result1, linear::Matrix& result2, linear::Matrix& result3, linear::Matrix& result4, linear::Matrix& res) {
            D_A.mul_thread(D_B, D);
            D1_A.mul_thread(D1_B, D1);
            D2_A.mul_thread(D2_B, D2);
            H1_A.mul_thread(H1_B, H1);
            H2_A.mul_thread(H2_B, H2);
            V1_A.mul_thread(V1_B, V1);
            V2_A.mul_thread(V2_B, V2);
            result1.complex_sum_strassen(D, D1, V1, H1, result1);
            result4.complex_sum_strassen(D, D2, V2, H2, result4);
            result2.sum(V2, H1, result2);
            result3.sum(V1, H2, result3);
            union_matrix(res, result1, result2, result3, result4);
            return true;
        }

    bool Matrix::mul(Matrix& right, Matrix& result) {              // Matrix C = A * B;
        if ( col != right.row ) {
            std::cout << "WRONG! Incorrect matrix dimensions are set\n";
            return false;
        }
        for(int i = 0; i < result.row; ++i) {
            for(int j = 0; j < result.col; ++j) {
                for(int k = 0; k < col; ++k) {
                    result.arr[i][j] += (arr[i][k] * right.arr[k][j]);
                }
            }
        }
        return true;
    }
    bool Matrix::compare(const Matrix& B) const {
        if ( ( row == B.get_row() ) & ( col == B.get_col() ) ) {
            for(int i = 0; i < row; ++i) {
                for(int j = 0; j < col; ++j) {
                    if ( arr[i][j] != B.arr[i][j] ) {
                        return false;
                    }
                }
            }
        }
        else {
            return false;
        }
        return true;
    }

    void Matrix::before_calc(linear::Matrix& result, int x, int y) {
        int sz = this->get_row() / 2;
        x = ( x - 1 ) * sz;
        y = ( y - 1 ) * sz;
        for(int i = 0; i < sz; ++i) {
            for(int j = 0; j < sz; ++j) {
                result.arr[i][j] = arr[i + x][j + y];
            }
        }
    }

    void Matrix::before_calc(linear::Matrix& result, int x1, int x2, int y1, int y2, bool operation) {
        int sz = this->get_row() / 2;
        linear::Matrix A(sz, sz);
        linear::Matrix B(sz, sz);
        before_calc(A, x1, x2);
        before_calc(B, y1, y2);
        if ( operation ) {
            result.sum(A, B, result);
            return;
        }
        result.sub(A, B, result);
    }
} //namespace linear
