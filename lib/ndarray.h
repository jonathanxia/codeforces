#include <lib/common.h>

// Numpy

template<typename T>
class ndarray {
public:
    int n_rows; // number of rows
    int n_cols; // number of columns
    vector<T> data; // vector to store the data

    // Constructor to initialize the 2D array with given shape
    ndarray(int n_rows_, int n_cols_) : n_rows(n_rows_), n_cols(n_cols_) {
        data = vector<T>(n_rows * n_cols);
    }

    // Accessor function to get the number of rows
    int get_n_rows() const {
        return n_rows;
    }

    // Accessor function to get the number of columns
    int get_n_cols() const {
        return n_cols;
    }

    // Accessor function to get the data of the 2D array
    vector<T> get_data() const {
        return data;
    }

    // Overload the () operator to access elements of the 2D array
    T& operator()(int i, int j) {
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
            throw std::out_of_range("Index out of range");
        }
        return data[i * n_cols + j];
    }

    // Overload the () operator to access elements of the 2D array (const version)
    const T& operator()(int i, int j) const {
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
            throw std::out_of_range("Index out of range");
        }
        return data[i * n_cols + j];
    }

    void resize(int rows, int cols) {
        data.resize(rows * cols);
        n_rows = rows;
        n_cols = cols;
    }

    // Fill the array with a particular value
    void fill(const T& value) {
        std::fill(data.begin(), data.end(), value);
    }

    void fill(const T& value, int istart, int iend, int jstart, int jend) {
        for (int i = istart; i <= iend; i++)
        {
            for (int j = jstart; j <= jend; j++)
            {
                (*this)(i, j) = value;
            }
        }
    }

    void set_row(int row, const vector<T>& ret, int cstart=0, int cend=-1) {
        if (cend == -1) {
            cend = n_cols;
        }
        rep(i, cstart, cend - 1) {
            (*this)(row, i) = ret[i - cstart];
        }
    }

    void set_row(int row, const T& ret, int cstart=0, int cend=-1) {
        if (cend == -1) {
            cend = n_cols;
        }
        rep(i, cstart, cend - 1) {
            (*this)(row, i) = ret;
        }
    }

    vector<T> get_row(int row, int cstart=0, int cend=-1) {
        if (cend == -1) {
            cend = n_cols - 1;
        }
        vector<T> ret(cend - cstart + 1);
        rep(i, cstart, cend) {
            ret[i - cstart] = (*this)(row, i);
        }
        return ret;
    }

    vector<T> get_col(int col, int rstart=0, int rend=-1) {
        if (rend == -1) {
            rend = n_rows - 1;
        }
        vector<T> ret(rend - rstart + 1);
        rep(i, rstart, rend) {
            ret[i - rstart] = (*this)(i, col);
        }
        return ret;
    }

    void set_col(int col, const T& ret, int rstart=0, int rend=-1) {
        if (rend == -1) {
            rend = n_rows;
        }
        rep(i, rstart, rend - 1) {
            (*this)(i, col) = ret;
        }
    }



    ndarray<T> slice(int istart, int iend, int jstart, int jend) {
        ndarray<T> subarray(iend - istart, jend - jstart);
        for (int i = istart; i <= iend; i++)
        {
            for (int j = jstart; j <= jend; j++)
            {
                subarray(i - istart, j - jstart) = (*this)(i, j);
            }
        }
        return subarray;
    }

    ndarray<T> transpose() {
        ndarray<T> output(n_cols, n_rows);

        rep(i, 0, n_rows - 1) {
            rep(j, 0, n_cols - 1) {
                output(j, i) = (*this)(i, j);
            }
        }
        return output;
    }

    T sum() {
        T tot(0);
        rep(i, 0, n_rows - 1) {
            rep(j, 0, n_cols - 1) {
                tot += (*this)(i, j);
            }
        }
        return tot;
    }

    ndarray<T> operator-(const ndarray<T> other) {
        ndarray<T> output(n_rows, n_cols);
        rep(i, 0, n_rows - 1) {
            rep(j, 0, n_cols - 1) {
                output(i, j) = (*this)(i, j) - other(i, j);
            }
        }
        return output;
    }
};

typedef ndarray<ll> llarray;
typedef ndarray<int> intarray;

// Overload the << operator to print the elements of the 2D array
template<typename T>
std::ostream& operator<<(std::ostream& os, const ndarray<T>& arr) {
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

template<typename T>
istream& operator>>(istream& input, ndarray<T>& arr) {
    for (int i = 0; i < arr.get_n_rows(); i++) {
        for (int j = 0; j < arr.get_n_cols(); j++) {
            input >> arr(i, j);
        }
    }
    return input;
}