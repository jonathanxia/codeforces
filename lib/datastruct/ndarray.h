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
template<typename T, int num_dimensions>
struct ndarray {
    ndarray(array<int, num_dimensions> _dimensions, T default_value=0) {
        dimensions = _dimensions;
        int rolling_mult = 1;
        DOR(i, num_dimensions-1, 0) {
           multiplier[i] = rolling_mult;
           rolling_mult *= dimensions[i];
        }
        data = vector<T>(rolling_mult + 1, default_value);
    }

    template <typename... Indices>
    T& operator() (Indices... args) {
        array<int, num_dimensions> indices = {static_cast<int>(args)...};
        int flatIndex = 0;
        FOR(i, 0, num_dimensions-1) if(indices[i] < 0 or indices[i] >= dimensions[i]) return data.back();
        FOR(i, 0, num_dimensions-1) flatIndex += indices[i] * multiplier[i];
        return data[flatIndex];
    }

    array<int, num_dimensions> multiplier;
    array<int, num_dimensions> dimensions;
    vector<T> data;
};