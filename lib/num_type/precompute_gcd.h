
#pragma once
#include <lib/nt.h>

namespace nt {

vector<vector<int>> GCD;
void precompute_gcd(int N) {
    GCD = vector<vector<int>>(N+1, vector<int>(N+1, 1));
    for(int d = 2; d <= N; ++d)
        for(int i = d; i <= N; i += d)
            for(int j = d; j <= N; j += d)
                GCD[i][j] = d;
}
}