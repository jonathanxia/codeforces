#pragma once
#include <lib/common.h>
// Numpy

template <typename T>
struct matrix {
    int n_rows; // number of rows
    int n_cols; // number of columns
    vector<T> data; // vector to store the data

    // Constructor to initialize the 2D array with given shape
    matrix(int n_rows_, int n_cols_)
        : n_rows(n_rows_)
        , n_cols(n_cols_)
        , data(n_rows_ * n_cols_)
    {
    }

    // Fill constructor
    matrix(int n_rows_, int n_cols_, T value_)
        : matrix(n_rows_, n_cols_)
    {
        fill(value_);
    }

    // Member list constructor
    matrix(int n_rows_, int n_cols_, initializer_list<T> values_)
        : n_rows(n_rows_)
        , n_cols(n_cols_)
        , data(values_)
    {
        data.resize(n_rows * n_cols);
    }

    // Vector constructor 
    matrix(int n_rows_, int n_cols_, vector<T> values_)
        : n_rows(n_rows_)
        , n_cols(n_cols_)
        , data(values_)
    {
        data.resize(n_rows * n_cols);
    }

    // Accessor function to get the number of rows
    int get_n_rows() const
    {
        return n_rows;
    }

    // Accessor function to get the number of columns
    int get_n_cols() const
    {
        return n_cols;
    }

    // Accessor function to get the data of the 2D array
    vector<T> get_data() const
    {
        return data;
    }

    // Overload the () operator to access elements of the 2D array
    T& operator()(int i, int j)
    {
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
            throw std::out_of_range("Index out of range");
        }
        return data[i * n_cols + j];
    }

    // Overload the () operator to access elements of the 2D array (const version)
    const T& operator()(int i, int j) const
    {
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
            throw std::out_of_range("Index out of range");
        }
        return data[i * n_cols + j];
    }

    void resize(int rows, int cols)
    {
        data.resize(rows * cols);
        n_rows = rows;
        n_cols = cols;
    }

    // Fill the array with a particular value
    void fill(const T& value)
    {
        std::fill(data.begin(), data.end(), value);
    }

    void fill(const T& value, int istart, int iend, int jstart, int jend)
    {
        FOR(i, istart, iend)
        {
            FOR(j, jstart, jend)
            {
                (*this)(i, j) = value;
            }
        }
    }

    void set_row(int row, const vector<T>& ret, int cstart = 0, int cend = -1)
    {
        if (cend == -1) {
            cend = n_cols - 1;
        }
        FOR(i, cstart, cend)
        {
            (*this)(row, i) = ret[i - cstart];
        }
    }

    void set_col(int col, const vector<T>& ret, int rstart = 0, int rend = -1)
    {
        if (rend == -1) {
            rend = n_cols - 1;
        }
        FOR(i, rstart, rend)
        {
            (*this)(i, col) = ret[i - rstart];
        }
    }

    void fill_row(int row, const T& ret, int cstart = 0, int cend = -1)
    {
        if (cend == -1) {
            cend = n_cols - 1;
        }
        FOR(i, cstart, cend)
        {
            (*this)(row, i) = ret;
        }
    }

    void fill_col(int col, const T& ret, int rstart = 0, int rend = -1)
    {
        if (rend == -1) {
            rend = n_rows - 1;
        }
        FOR(i, rstart, rend)
        {
            (*this)(i, col) = ret;
        }
    }

    vector<T> get_row(int row, int cstart = 0, int cend = -1)
    {
        if (cend == -1) {
            cend = n_cols - 1;
        }
        vector<T> ret(cend - cstart + 1);
        FOR(i, cstart, cend)
        {
            ret[i - cstart] = (*this)(row, i);
        }
        return ret;
    }

    vector<T> get_col(int col, int rstart = 0, int rend = -1)
    {
        if (rend == -1) {
            rend = n_rows - 1;
        }
        vector<T> ret(rend - rstart + 1);
        FOR(i, rstart, rend)
        {
            ret[i - rstart] = (*this)(i, col);
        }
        return ret;
    }

    matrix<T> slice(int istart, int iend, int jstart, int jend)
    {
        matrix<T> subarray(iend - istart + 1, jend - jstart + 1);
        FOR(i, istart, iend)
        {
            FOR(j, jstart, jend)
            {
                subarray(i - istart, j - jstart) = (*this)(i, j);
            }
        }
        return subarray;
    }

    matrix<T> transpose()
    {
        matrix<T> output(n_cols, n_rows);

        rep(i, 0, n_rows)
        {
            rep(j, 0, n_cols)
            {
                output(j, i) = (*this)(i, j);
            }
        }
        return output;
    }
};
namespace linalg {
template <typename T>
T sum(const matrix<T>& arr)
{
    int n_rows = arr.get_n_rows();
    int n_cols = arr.get_n_cols();
    T tot(0);
    rep(i, 0, n_rows)
    {
        rep(j, 0, n_cols)
        {
            tot += arr(i, j);
        }
    }
    return tot;
}
template <typename T>
matrix<T> mult(const matrix<T>& left, const matrix<T>& right)
{
    if (left.get_n_cols() != right.get_n_rows())
        throw std::out_of_range("mult: Matrices have mismatching dimensions");

    matrix<T> result(left.get_n_rows(), right.get_n_cols(), T(0));

    int i_max = left.get_n_rows();
    int j_max = right.get_n_cols();
    int k_max = left.get_n_cols();

    rep(k, 0, k_max)
    {
        rep(i, 0, i_max)
        {
            T r = left(i, k);
            rep(j, 0, j_max)
            {
                result(i, j) += r * right(k, j);
            }
        }
    }
    return result;
}
template <typename T>
matrix<T> identity(ll size)
{
    matrix<T> I(size, size, T(0));
    rep(i, 0, size)
    {
        I(i, i) = T(1);
    }
    return I;
}
// given cos and sin of some theta, returns rotation matrix for rotating
// counter-clockwise
template <typename T>
matrix<T> rotation(T cos, T sin)
{
    return matrix<T>(2, 2, { cos, -sin, sin, cos });
}
template <typename T>
matrix<T> pow(matrix<T> base, ll exp)
{
    if (base.get_n_cols() != base.get_n_rows())
        throw std::out_of_range("pow: Matrix is not square");
    if (exp == 0)
        return identity<T>(base.get_n_rows());
    if (exp == 1)
        return base;
    matrix<T> result = pow(base, exp / 2);
    result = mult(result, result);
    if (exp % 2)
        result = mult(result, base);
    return result;
}
}
typedef matrix<ll> llarray;
typedef matrix<int> intarray;

// Overload the << operator to print the elements of the 2D array
template <typename T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& arr)
{
    for (int i = 0; i < arr.get_n_rows(); i++) {
        for (int j = 0; j < arr.get_n_cols(); j++) {
            os << arr(i, j) << " ";
        }
        if (i != arr.get_n_rows() - 1) {
            os << std::endl;
        }
    }
    return os;
}

template <typename T>
matrix<T> operator*(const matrix<T>& mat1, const matrix<T>& mat2) {
    return linalg::mult(mat1, mat2);
}

template <typename T>
matrix<T> operator+(const matrix<T>& mat1, const matrix<T>& mat2) {
    if (mat1.get_n_cols() != mat2.get_n_cols() || mat1.get_n_rows() != mat2.get_n_rows())
        throw std::out_of_range("add: Matrices have mismatching dimensions");

    matrix<T> result(mat1.get_n_rows(), mat1.get_n_cols(), T(0));
    FOR(i, 0, mat1.get_n_rows() - 1) {
        FOR(j, 0, mat1.get_n_cols() - 1) {
            result(i, j) = mat1(i, j) + mat2(i, j);
        }
    }
    return result;
}
