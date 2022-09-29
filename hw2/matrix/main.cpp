#include <iostream>
#include <chrono>
#include "matrix.hpp"
#include "matrix.cpp"

using namespace std;

template <class T>
void printMatrix(const Matrix<T> matrix)
{
    int nRows = matrix.getNRows();
    int nCols = matrix.getNCols();
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            cout << matrix.getElement(row, col) << " ";
        }
        cout << endl;
    }
}

int main()
{   
    /*
    1. Реализовать классическое перемножение матриц и умножение матрицы
    на вектор на C/C++ с разным порядком циклов (25\%)
    */
    Matrix<double> m(512, 512, "random");
    Matrix<double> m2(512, 512, "random");
    Vector<double> vec(512);

    //Умножение матриц (по умолчанию kij)
    auto m3 = m * m2;
    //умножение матрицы на вектор-столбец
    auto m4 = m * vec;
    //разный порядок циклов
    auto start_ijk = chrono::steady_clock::now();
    auto m5 = m.dot_ijk(m2);
    auto end_ijk = chrono::steady_clock::now();
    cout << "ijk time (512): "
        << chrono::duration_cast<chrono::milliseconds>(end_ijk - start_ijk).count()
        << " ms" << endl;
    
    auto start_jik = chrono::steady_clock::now();
    auto m6 = m.dot_jik(m2);
    auto end_jik = chrono::steady_clock::now();
    cout << "jik time (512): "
        << chrono::duration_cast<chrono::milliseconds>(end_jik - start_jik).count()
        << " ms" << endl;
    
    auto start_kij = chrono::steady_clock::now();
    auto m7 = m.dot_kij(m2);
    auto end_kij = chrono::steady_clock::now();
    cout << "jik time (512): "
        << chrono::duration_cast<chrono::milliseconds>(end_kij - start_kij).count()
        << " ms" << endl;

    Matrix<double> m5001(500, 500, "random");
    Matrix<double> m5002(500, 500, "random");
    auto start_500 = chrono::steady_clock::now();
    auto m5003 = m5001.dot_kij(m5002);
    auto end_500 = chrono::steady_clock::now();
    cout << "kij time (500): "
        << chrono::duration_cast<chrono::milliseconds>(end_500 - start_500).count()
        << " ms" << endl;

    Matrix<double> m10001(1000, 1000, "random");
    Matrix<double> m10002(1000, 1000, "random");
    auto start_1000 = chrono::steady_clock::now();
    auto m10003 = m10001.dot_kij(m10002);
    auto end_1000 = chrono::steady_clock::now();
    cout << "kij time (1000): "
        << chrono::duration_cast<chrono::milliseconds>(end_1000 - start_1000).count()
        << " ms" << endl;

    Matrix<double> m10241(1024, 1024, "random");
    Matrix<double> m10242(1024, 1024, "random");
    auto start_1024 = chrono::steady_clock::now();
    auto m10243 = m10241.dot_kij(m10242);
    auto end_1024 = chrono::steady_clock::now();
    cout << "kij time (1024): "
        << chrono::duration_cast<chrono::milliseconds>(end_1024 - start_1024).count()
        << " ms" << endl;
    
    Matrix<double> m20001(2000, 2000, "random");
    Matrix<double> m20002(2000, 2000, "random");
    auto start_2000 = chrono::steady_clock::now();
    auto m20003 = m20001.dot_kij(m20002);
    auto end_2000 = chrono::steady_clock::now();
    cout << "kij time (2000): "
        << chrono::duration_cast<chrono::milliseconds>(end_2000 - start_2000).count()
        << " ms" << endl;

    Matrix<double> m20481(2048, 2048, "random");
    Matrix<double> m20482(2048, 2048, "random");
    auto start_2048 = chrono::steady_clock::now();
    auto m20483 = m20481.dot_kij(m20482);
    auto end_2048 = chrono::steady_clock::now();
    cout << "kij time (2048): "
        << chrono::duration_cast<chrono::milliseconds>(end_2048 - start_2048).count()
        << " ms" << endl;

    //2.Разбейте на модули, со статической линковкой скомпилируйте текст, подготовьте Makefile, проверьте флаги -g,  -O3
    //Сделано, флаги можно проверить с помощью IMPR, отчет по ним по п.3 в README

    return 0;
}