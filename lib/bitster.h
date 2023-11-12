#include <lib/common.h>

namespace bitster {
template<size_t N>
ll lsb(const bitset<N>& b) {
    return first_st(i, b[i], 0, int(N) - 1);
}
template<size_t N>
ll msb(const bitset<N>& b) {
    return last_st(i, b[i], int(N) - 1, 0);
}

ll lsb(ll n) {
    return first_st(i, (1LL << i) & n, 0, 62);
}
ll msb(ll n) {
    return last_st(i, (1LL << i) & n, 62, 0);
}

template <size_t N>
string to_string(const bitset<N>& b, int n, bool reverse=false) {
    string s;
    if (reverse)
        DOR(i, n - 1, 0) {
            s += b[i] ? "1" : "0";
        }
    else
        FOR(i, 0, n - 1) {
            s += b[i] ? "1" : "0";
        }
    return s;
}

// Bit shifts, but handles negatives
template <typename T>
T bitshift_left(T x, ll k) {
    if (k > 0) return x << k;
    else if (k == 0) return x;
    else return x >> (-k);
}

template <typename T>
T bitshift_right(T x, ll k) {
    if (k > 0) return x >> k;
    else if (k == 0) return x;
    else return x << (-k);
}

template <size_t N>
void fill(bitset<N>& b, int start, int end) {
    FOR(i, start, end) {
        b[i] = true;
    }
}

} // namespace bitster
