#ifndef MATRIX_HPP
#define MATRIX_HPP


template <class T>
class Matrix
{
    public:
        //constructors
        Matrix();
        Matrix(int nRows, int nCols);
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
    
    private:
        int sub2Ind(int row, int col);

    private:
        T *matrixData;
        int nRows, nCols, nElements;
};

#endif
