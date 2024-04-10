#pragma once
#include <lib/common.h>

template <class T>
struct CumSum2d {
    vector<vector<T>> data;

    T access(int i, int j) {
        if (ordered(0, i, len(data) - 1) && ordered(0, j, len(data[0]) - 1)) {
            return data[i][j];
        }
        return T(0);
    }
    CumSum2d(int H, int W) : data(H, vector<T>(W, 0)) {}
    CumSum2d() {}
    CumSum2d(const vector<vector<T>>& d) : data(d) {
        ll h = len(data);
        ll w = len(data[0]);
        FOR(i, 0, h - 1) FOR(j, 0, w - 1) {
            data[i][j] += access(i, j - 1) + access(i - 1, j) - access(i - 1, j - 1);
        }
    }

    T query(int sx, int gx, int sy, int gy) {
        // Clip all inputs to be in the right range
        if (sx < 0) sx = 0;
        if (sy < 0) sy = 0;
        if (gx < sx) return 0;
        if (gy < sy) return 0;
        if (gx >= len(data)) gx = len(data) - 1;
        if (gy >= len(data[0])) gy = len(data[0]) - 1;
        return access(gx, gy) - access(sx - 1, gy) - access(gx, sy - 1) + access(sx - 1, sy - 1);
    }
};

