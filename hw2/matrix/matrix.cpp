#include <time.h>
#include "matrix.hpp"
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))


template <class T>
Matrix<T>::Matrix()
{
    nRows = 1;
    nCols = 1;
    nElements = 1;
    matrixData = new T[nElements];
    matrixData[0] = 0.0;
}

template <class T>
Matrix<T>::Matrix(int nRows, int nCols, std::string type)
{   
    if (type == "random") {
        srand( (unsigned)time( NULL ) );
    }
    this->nRows = nRows;
    this->nCols = nCols;
    this->nElements = nRows * nCols;
    matrixData = new T[this->nElements];
    for (int i = 0; i < this->nElements; i++) {
        if (type == "random")
            matrixData[i] = (T) rand()/RAND_MAX;
        else
            matrixData[i] = 0.0;
    }
}

template <class T>
Matrix<T>::Matrix(int nRows, int nCols, const T *inputData)
{
    this->nRows = nRows;
    this->nCols = nCols;
    this->nElements = nRows * nCols;
    matrixData = new T[this->nElements];
    for (int i = 0; i < this->nElements; i++) {
        matrixData[i] = inputData[i];
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& inputMatrix)
{
    this->nRows = inputMatrix.nRows;
    this->nCols = inputMatrix.nCols;
    this->nElements = inputMatrix.nElements;
    matrixData = new T[nElements];
    for (int i = 0; i < this->nElements; i++) {
        matrixData[i] = inputMatrix.matrixData[i];
    }
}

//destructor
template <class T>
Matrix<T>::~Matrix()
{
    if (matrixData != NULL) {
        delete[] matrixData;
    }
}

template <class T>
bool Matrix<T>::resize(int nRows, int nCols)
{
    this->nRows = nRows;
    this->nCols = nCols;
    this->nElements = nRows * nCols;
    delete[] matrixData;
    matrixData = new T[nElements];
    if (matrixData != NULL) {
        for (int i = 0; i < this->nElements; i++) {
            matrixData[i] = 0.0;
        }
        return true;
    }
    else {
        return false;
    }
}

//element methods
template <class T>
T Matrix<T>::getElement(int row, int col) const
{
    int idx = sub2Ind(row, col);
    if (idx >= 0) {
        return matrixData[idx];
    }
    else {
        return 0.0;
    }
}

template <class T>
bool Matrix<T>::setElement(int row, int col, T value)
{
    int idx = sub2Ind(row, col);
    if (idx >= 0) {
        matrixData[idx] = value;
        return true;
    }
    else {
        return false;
    }
}

template <class T>
int Matrix<T>::getNRows() const { return nRows; }

template <class T>
int Matrix<T>::getNCols() const { return nCols; }

template <class T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    assertm((lhs.nRows == rhs.nRows) && (lhs.nCols == rhs.nCols), "Matrixes should be of equal size");

    int nRows = lhs.nRows;
    int nCols = lhs.nCols;
    int nElements = lhs.nElements;
    T *temp = new T[nElements];
    for (int i = 0; i < nElements; i++) {
        temp[i] = lhs.matrixData[i] + rhs.matrixData[i];
    }
    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}

template <class T>
Matrix<T> operator+(const T& lhs, const Matrix<T>& rhs)
{
    int nRows = rhs.nRows;
    int nCols = rhs.nCols;
    int nElements = rhs.nElements;
    T *temp = new T[nElements];
    for (int i = 0; i < nElements; i++) {
        temp[i] = lhs + rhs.matrixData[i];
    }
    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}

template <class T>
Matrix<T> operator+(const Matrix<T>& lhs, const T& rhs)
{
    int nRows = lhs.nRows;
    int nCols = lhs.nCols;
    int nElements = lhs.nElements;
    T *temp = new T[nElements];
    for (int i = 0; i < nElements; i++) {
        temp[i] = lhs.matrixData[i] + rhs;
    }
    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}

template <class T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    assertm((lhs.nRows == rhs.nRows) && (lhs.nCols == rhs.nCols), "Matrixes should be of equal size");

    int nRows = lhs.nRows;
    int nCols = lhs.nCols;
    int nElements = lhs.nElements;
    T *temp = new T[nElements];
    for (int i = 0; i < nElements; i++) {
        temp[i] = lhs.matrixData[i] - rhs.matrixData[i];
    }
    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}

template <class T>
Matrix<T> operator-(const T& lhs, const Matrix<T>& rhs)
{
    int nRows = rhs.nRows;
    int nCols = rhs.nCols;
    int nElements = rhs.nElements;
    T *temp = new T[nElements];
    for (int i = 0; i < nElements; i++) {
        temp[i] = lhs - rhs.matrixData[i];
    }
    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}

template <class T>
Matrix<T> operator-(const Matrix<T>& lhs, const T& rhs)
{
    int nRows = lhs.nRows;
    int nCols = lhs.nCols;
    int nElements = lhs.nElements;
    T *temp = new T[nElements];
    for (int i = 0; i < nElements; i++) {
        temp[i] = lhs.matrixData[i] - rhs;
    }
    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}

template <class T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    assertm((lhs.nCols == rhs.nRows), "Matrixes should be of sizes [i, j] and [j, k]");

    return lhs.dot_kij(rhs);
}

template <class T>
Matrix<T> operator*(const T& lhs, const Matrix<T>& rhs)
{
    int nRows = rhs.nRows;
    int nCols = rhs.nCols;
    int nElements = rhs.nElements;
    T *temp = new T[nElements];
    for (int i = 0; i < nElements; i++) {
        temp[i] = lhs * rhs.matrixData[i];
    }
    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}

template <class T>
Matrix<T> operator*(const Matrix<T>& lhs, const T& rhs)
{
    int nRows = lhs.nRows;
    int nCols = lhs.nCols;
    int nElements = lhs.nElements;
    T *temp = new T[nElements];
    for (int i = 0; i < nElements; i++) {
        temp[i] = lhs.matrixData[i] * rhs;
    }
    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}


//private
template <class T>
int Matrix<T>::sub2Ind(int row, int col) const
{
    if ((row < nRows) && (row >= 0) && (col < nCols) && (col >= 0)) {
        return (row * nCols) + col;
    }
    else {
        return -1;
    }
}

template<class T>
Matrix<T> Matrix<T>::dot_ijk(const Matrix<T>& rhs) const
{
    int nCols = rhs.nCols;
    int nElements = nRows * nCols;

    T *temp = new T[nElements];
    for (int t = 0; t < nElements; t++) {
        temp[t] = 0.0;
    }

    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            for (int k = 0; k < rhs.nRows; k++) {
                temp[i * nCols + j] += matrixData[sub2Ind(i, k)] * rhs.matrixData[k * rhs.nCols + j];
            }
        }
    }

    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}

template<class T>
Matrix<T> Matrix<T>::dot_jik(const Matrix<T>& rhs) const
{
    int nCols = rhs.nCols;
    int nElements = nRows * nCols;

    T *temp = new T[nElements];
    for (int t = 0; t < nElements; t++) {
        temp[t] = 0.0;
    }

    for (int j = 0; j < nCols; j++) {
        for (int i = 0; i < nRows; i++) {
            for (int k = 0; k < rhs.nRows; k++) {
                temp[i * nCols + j] += matrixData[sub2Ind(i, k)] * rhs.matrixData[k * rhs.nCols + j];
            }
        }
    }

    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}

template<class T>
Matrix<T> Matrix<T>::dot_kij(const Matrix<T>& rhs) const
{
    int nCols = rhs.nCols;
    int nElements = nRows * nCols;

    T *temp = new T[nElements];
    for (int t = 0; t < nElements; t++) {
        temp[t] = 0.0;
    }

    for (int k = 0; k < rhs.nRows; k++) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                temp[i * nCols + j] += matrixData[sub2Ind(i, k)] * rhs.matrixData[k * rhs.nCols + j];
            }
        }
    }

    Matrix<T> res(nRows, nCols, temp);
    delete[] temp;
    return res;
}


/*Vector*/
template <class T>
Vector<T>::Vector()
{
    this->nRows = 1;
    this->nCols = 1;
    this->nElements = 1;
    this->matrixData = new T[this->nElements];
    this->matrixData[0] = 0.0;
}

template <class T>
Vector<T>::Vector(int size)
{
    this->nRows = size;
    this->nCols = 1;
    this->nElements = size * 1;
    this->matrixData = new T[this->nElements];
    for (int i = 0; i < this->nElements; i++) {
        this->matrixData[i] = 0.0;
    }
}

template <class T>
Vector<T>::Vector(int size, const T *inputData)
{
    this->nRows = size;
    this->nCols = 1;
    this->nElements = size * 1;
    this->matrixData = new T[this->nElements];
    for (int i = 0; i < this->nElements; i++) {
        this->matrixData[i] = inputData[i];
    }
}

template <class T>
Vector<T>::Vector(const Vector<T>& inputVector)
{
    this->nRows = inputVector.nRows;
    this->nCols = 1;
    this->nElements = inputVector.nElements;
    this->matrixData = new T[this->nElements];
    for (int i = 0; i < this->nElements; i++) {
        this->matrixData[i] = inputVector.matrixData[i];
    }
}

