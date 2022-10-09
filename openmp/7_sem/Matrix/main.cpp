#include "matrix.hpp"

int **init(int **arr, int m, int n)
{
    arr = new int *[m];
    for (int i = 0; i < m; ++i)
    {
        arr[i] = new int[n];
    }
    return arr;
}

void mul(linear::Matrix &A, linear::Matrix &B, linear::Matrix &result)
{
    bool p = A.mul_impr(B, result);
    if (p == 0)
    {
        exit(1);
    }
}

void TEST1(linear::Matrix &A, linear::Matrix &B, linear::Matrix &result)
{
    std::vector<int> Time1;
    for (int i = 0; i < 1; ++i)
    {
        auto begin = std::chrono::steady_clock::now();
        bool p = A.mul(B, result);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        Time1.push_back(elapsed_ms.count());
    }
    int time = 0;
    for (int i = 0; i < Time1.size(); ++i)
    {
        time += Time1[i];
    }
    result.record("OUT_TEST1");
    std::cout << "The first time: " << time / Time1.size() << " ms\n";
}

void TEST2(linear::Matrix &A, linear::Matrix &B, linear::Matrix &result)
{
    std::vector<int> Time1;
    for (int i = 0; i < 1; ++i)
    {
        auto begin = std::chrono::steady_clock::now();
        bool p = A.mul_impr(B, result);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        Time1.push_back(elapsed_ms.count());
    }
    int time = 0;
    for (int i = 0; i < Time1.size(); ++i)
    {
        time += Time1[i];
    }
    result.record("OUT_TEST2");
    std::cout << "The optimization time: " << time / Time1.size() << " ms\n";
}

void TEST3(linear::Matrix &A1, linear::Matrix &B1, linear::Matrix &result1)
{
    std::vector<std::thread> threads;
    std::vector<int> Time;
    int my_row = A1.get_row();
    int my_col = B1.get_col();
    linear::Matrix A2(A1); //Создаем 8 матриц, чтобы запустить их умножение параллельно
    linear::Matrix A3(A1);
    linear::Matrix A4(A1);
    linear::Matrix B2(B1);
    linear::Matrix B3(B1);
    linear::Matrix B4(B1);
    linear::Matrix result2(my_row, my_col);
    linear::Matrix result3(my_row, my_col);
    linear::Matrix result4(my_row, my_col);
    auto begin = std::chrono::steady_clock::now();
    threads.push_back(std::thread(mul, std::ref(A1), std::ref(B1), std::ref(result1)));
    threads.push_back(std::thread(mul, std::ref(A2), std::ref(B2), std::ref(result2)));
    threads.push_back(std::thread(mul, std::ref(A3), std::ref(B3), std::ref(result3)));
    threads.push_back(std::thread(mul, std::ref(A4), std::ref(B4), std::ref(result4)));
    for (std::thread &t : threads)
    {
        t.join();
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        Time.push_back(elapsed_ms.count());
    }

    int max_time = 0;
    for (int i = 0; i < Time.size(); ++i)
    {
        if (Time[i] > max_time)
        {
            max_time = Time[i];
        }
    }
    result1.record("OUT_TEST3");
    std::cout << "The optimization + middle threads time(linear equation): " << max_time / Time.size() << " ms\n";
}

void TEST4(linear::Matrix &A, linear::Matrix &B, linear::Matrix &result)
{
    std::vector<int> Time;
    for (int i = 0; i < 4; ++i)
    {
        auto begin = std::chrono::steady_clock::now();
        bool p = A.mul_thread(B, result);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        Time.push_back(elapsed_ms.count());
    }
    int time = 0;
    for (int i = 0; i < Time.size(); ++i)
    {
        time += Time[i];
    }
    result.record("OUT_TEST4");
    std::cout << "The optimization + mul_thread time: " << time / Time.size() << " ms\n";
}

void TEST5(linear::Matrix &A, linear::Matrix &B, linear::Matrix &result)
{
    std::vector<int> Time;
    for (int i = 0; i < 1; ++i)
    {
        auto begin = std::chrono::steady_clock::now();
        bool p = A.mul_intrinsic(B, result);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        Time.push_back(elapsed_ms.count());
    }
    int time = 0;
    for (int i = 0; i < Time.size(); ++i)
    {
        time += Time[i];
    }
    result.record("OUT_TEST5");
    std::cout << "The optimization intrinsic time: " << time / Time.size() << " ms\n";
}

void TEST6(linear::Matrix &A, linear::Matrix &B, linear::Matrix &result)
{
    bool test_square = A.get_row() == B.get_col();
    test_square &= A.get_col() == B.get_row();
    if (!test_square & (A.get_row() % 2 == 0))
    {
        std::cout << "Size of matrix isn't correct for Strassen" << std::endl;
    }
    int mini_size = A.get_row() / 2;
    linear::Matrix D_A(mini_size, mini_size);
    linear::Matrix D_B(mini_size, mini_size);
    linear::Matrix D1_A(mini_size, mini_size);
    linear::Matrix D1_B(mini_size, mini_size);
    linear::Matrix D2_A(mini_size, mini_size);
    linear::Matrix D2_B(mini_size, mini_size);
    linear::Matrix H1_A(mini_size, mini_size);
    linear::Matrix H1_B(mini_size, mini_size);
    linear::Matrix H2_A(mini_size, mini_size);
    linear::Matrix H2_B(mini_size, mini_size);
    linear::Matrix V1_A(mini_size, mini_size);
    linear::Matrix V1_B(mini_size, mini_size);
    linear::Matrix V2_A(mini_size, mini_size);
    linear::Matrix V2_B(mini_size, mini_size);
    A.before_calc(D_A, 1, 1, 2, 2, true);
    A.before_calc(D1_A, 1, 2, 2, 2, false);
    A.before_calc(D2_A, 2, 1, 1, 1, false);
    A.before_calc(H1_A, 1, 1, 1, 2, true);
    A.before_calc(H2_A, 2, 1, 2, 2, true);
    A.before_calc(V1_A, 2, 2);
    A.before_calc(V2_A, 1, 1);
    B.before_calc(D_B, 1, 1, 2, 2, true);
    B.before_calc(D1_B, 2, 1, 2, 2, true);
    B.before_calc(D2_B, 1, 1, 1, 2, true);
    B.before_calc(H1_B, 2, 2);
    B.before_calc(H2_B, 1, 1);
    B.before_calc(V1_B, 2, 1, 1, 1, false);
    B.before_calc(V2_B, 1, 2, 2, 2, false);

    linear::Matrix D(mini_size, mini_size);
    linear::Matrix D1(mini_size, mini_size);
    linear::Matrix D2(mini_size, mini_size);
    linear::Matrix H1(mini_size, mini_size);
    linear::Matrix H2(mini_size, mini_size);
    linear::Matrix V1(mini_size, mini_size);
    linear::Matrix V2(mini_size, mini_size);
    linear::Matrix result1(mini_size, mini_size);
    linear::Matrix result2(mini_size, mini_size);
    linear::Matrix result3(mini_size, mini_size);
    linear::Matrix result4(mini_size, mini_size);

    std::vector<int> Time;
    for (int i = 0; i < 1; ++i)
    {
        auto begin = std::chrono::steady_clock::now();
        bool p = result.strassen(D_A, D1_A, D2_A, H1_A, H2_A, V1_A, V2_A, \
            D_B, D1_B, D2_B, H1_B, H2_B, V1_B, V2_B, D, D1, D2, H1, H2, V1, V2, \
            result1, result2, result3, result4, result);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        Time.push_back(elapsed_ms.count());
    }
    int time = 0;
    for (int i = 0; i < Time.size(); ++i)
    {
        time += Time[i];
    }
    result.record("OUT_TEST6");
    std::cout << "The optimization Strassen time: " << time / Time.size() << " ms\n";
}

void compare(linear::Matrix &A, linear::Matrix &B, linear::Matrix &C, linear::Matrix &D, linear::Matrix &E, linear::Matrix &F)
{
    if (A.compare(B) == false)
    {
        std::cout << "UNIT TEST1 FAILED\n";
        return;
    }
    else if (A.compare(C) == false)
    {
        std::cout << "UNIT TEST2 FAILED\n";
        return;
    }
    else if (A.compare(D) == false)
    {
        std::cout << "UNIT TEST3 FAILED\n";
        return;
    }
    else if (A.compare(E) == false)
    {
        std::cout << "UNIT TEST4 FAILED\n";
        return;
    }
    else if (A.compare(F) == false)
    {
        std::cout << "UNIT TEST5 FAILED\n";
        return;
    }
    else
    {
        for (int i = 1; i < 6; ++i)
        {
            std::cout << "UNIT TEST " << i << " OK\n";
        }
    }
}

int main()
{
    int col, col2, row, row2;
    std::cin >> row >> col;
    std::cin >> row2 >> col2;
    if ((col < 1) | (col2 < 1) | (row < 1) | (row2 < 1))
    {
        std::cout << "Incorrect size\n";
        return 1;
    }
    srand(static_cast<unsigned int>(time(0)));
    int **arr = nullptr;
    arr = init(arr, row, col);
    int **arr2 = nullptr;
    arr2 = init(arr2, row2, col2);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; j++)
        {
            arr[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < row2; ++i)
    {
        for (int j = 0; j < col2; j++)
        {
            arr2[i][j] = rand() % 10;
        }
    }
    linear::Matrix A(row, col, arr);
    linear::Matrix B(row2, col2, arr2);
    linear::Matrix main_result(row, col2);
    linear::Matrix result2(row, col2);
    linear::Matrix result3(row, col2);
    linear::Matrix result4(row, col2);
    linear::Matrix result5(row, col2);
    linear::Matrix result6(row, col2);
    TEST1(A, B, main_result);
    TEST2(A, B, result2);
    TEST3(A, B, result3);
    TEST4(A, B, result4);
    TEST5(A, B, result5);
    TEST6(A, B, result6);
    compare(main_result, result2, result3, result4, result5, result6);
    for (int i = 0; i < row; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;
    for (int i = 0; i < row2; ++i)
    {
        delete[] arr2[i];
    }
    delete[] arr2;
}
