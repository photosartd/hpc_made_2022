#ifndef MATRIX_HPP
#define MATRIX_HPP
#include<string>


template <class T>
class Matrix
{
    public:
        //constructors
        Matrix();
        Matrix(int nRows, int nCols, std::string type);
        Matrix(int nRows, int nCols, const T *inputData);
        Matrix(const Matrix<T>& inputMatrix);

        //destructor
        ~Matrix();

        //element access
        T getElement(int row, int col) const;
        bool setElement(int row, int col, T value);
        int getNRows() const;
        int getNCols() const;

        //resize
        bool resize(int nRows, int nCols);

        //overloading

        bool operator==(const Matrix<T>& rhs);
        template <class U> friend Matrix<U> operator+(const Matrix<U>& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator+(const U& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator+(const Matrix<U>& lhs, U& rhs);

        template <class U> friend Matrix<U> operator-(const Matrix<U>& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator-(const U& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator-(const Matrix<U>& lhs, U& rhs);

        template <class U> friend Matrix<U> operator*(const Matrix<U>& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator*(const U& lhs, const Matrix<U>& rhs);
        template <class U> friend Matrix<U> operator*(const Matrix<U>& lhs, U& rhs);

        //dot
        Matrix<T> dot_ijk(const Matrix<T>& rhs) const;
        Matrix<T> dot_jik(const Matrix<T>& rhs) const;
        Matrix<T> dot_kij(const Matrix<T>& rhs) const;
    
    private:
        int sub2Ind(int row, int col) const;

    protected:
        T *matrixData;
        int nRows, nCols, nElements;
};

template <class T>
class Vector: public Matrix<T>
{
    //vector is always vector-column (M x 1)
    public:
        Vector();
        Vector(int size);
        Vector(int size, const T *inputData);
        Vector(const Vector<T>& inputVector);

};

#endif
