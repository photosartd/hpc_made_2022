#include <iostream>
#include "matrix.hpp"

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
    double data[4] = {1.0, 2.0, 3.0, 4.0};
    Matrix<double> m(2, 2, data);

    /*double data2[2] = {1.0, 2.0};
    Matrix<double> m2(2, 1, data2);

    Matrix<double> res = m * m2;
    printMatrix(res);*/
    printMatrix(m);

    return 0;
}