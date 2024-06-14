#pragma once
#include <lib/common.h>

/**
 * arbitrarily high dimension array
 * by default will return a default_value on OOB access
 *
 * Example usage:
 *
 * ndarray<ll> arr({3, 5, 2}, 27);
 * arr(2, 2, 0) = 8;
 * arr(-1, -1, -1) // Gives 27
*/
template<typename T, int num_dimensions, typename K=int>
struct ndarray {
    T m_default_value;
    // Suppose dimensions is d1 x d2 x d3 x d4
    // Then multiplier will be
    // {d2*d3*d4, d3*d4, d4, 1}
    array<int, num_dimensions> multiplier;
    array<int, num_dimensions> dimensions;
    vector<T> data;

    ndarray(array<K, num_dimensions> _dimensions, T default_value=0) : m_default_value(default_value) {
        FOR(i, 0, num_dimensions - 1) dimensions[i] = _dimensions[i];
        int rolling_mult = 1;
        DOR(i, num_dimensions-1, 0) {
           multiplier[i] = rolling_mult;
           rolling_mult *= dimensions[i];
        }
        data = vector<T>(rolling_mult, default_value);
    }

    template <typename... Indices>
    T& operator() (Indices... args) {
        array<int, num_dimensions> indices = {static_cast<int>(args)...};
        int flatIndex = 0;
        FOR(i, 0, num_dimensions-1) if(indices[i] < 0 or indices[i] >= dimensions[i]) return m_default_value;
        FOR(i, 0, num_dimensions-1) flatIndex += indices[i] * multiplier[i];
        return data[flatIndex];
    }

    T sum() {
        T tot(0);
        FOR(i, 0, len(data) - 1) tot += data[i];
        return tot;
    }

    friend std::istream& operator>>(std::istream& os, ndarray& arr) {
        FOR(i, 0, len(arr.data) - 1) os >> arr.data[i];
        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const ndarray& arr) {
        // For a 1D array, just print the array
        if (num_dimensions == 1) {
            FOR(i, 0, len(arr.data) - 1) {
                os << arr.data[i];
                if (i < len(arr.data) - 1) os << " ";
            }
            return os;
        }
        // Unfold the last dimension of the array but key everything else
        FOR(i, 0, len(arr.data) - 1) {
            int last_dim_size = arr.multiplier[len(arr.multiplier) - 2];
            if (i % last_dim_size == 0) {
                // Print the index of this row
                ll idx = i;
                FOR(j, 0, num_dimensions - 2) {
                    os << idx / arr.multiplier[j] << " ";
                    idx = idx % arr.multiplier[j];
                }
                os << ": ";
            }
            // Print out the item itself
            os << arr.data[i] << " ";
            if (i % last_dim_size == last_dim_size - 1)
                os << "\n";
        }
        return os;
    }
};
