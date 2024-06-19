#pragma once
#include <lib/macros.h>

template <typename S, typename T>
istream &operator>>(istream &input, pair<S, T> &p)
{
    input >> p.first >> p.second;
    return input;
}

template <typename T>
istream &operator>>(istream &input, vector<T> &vec)
{
    for (auto &element : vec)
    {
        input >> element;
    }
    return input;
}

template<typename T>
istream& operator>>(istream& input, deque<T>& vec) {
    for (auto& element : vec) {
        input >> element;
    }
    return input;
}

template <typename T, size_t N>
istream& operator>>(istream& input, array<T, N>& arr) {
    for (size_t i = 0; i < N; i++) {
        input >> arr[i];
    }
    return input;
}

// Input
namespace inp
{
    long long binary()
    {
        string s;
        cin >> s;
        long long res = 0;
        for (char c : s)
        {
            res <<= 1;
            if (c == '1')
                res |= 1;
        }
        return res;
    }

    template <typename T>
    void read1(vector<T>& v) {
        FOR(i, 1, len(v) - 1) {
            cin >> v[i];
        }
    }

    // forward means the input is parsed as
    // b[0], b[1], ..., b[n - 1]
    // backwards means the input is parsed as
    // b[n - 1], b[n - 2], ..., b[0]
    template <size_t N>
    void read_bitset(bitset<N>& b, int n, bool reverse=false) {
        char ch;
        if (!reverse) {
            FOR(i, 0, n - 1) {
                cin >> ch;
                b[i] = ch == '1';
            }
        }
        else {
            DOR(i, n - 1, 0) {
                cin >> ch;
                b[i] = ch == '1';
            }
        }
    }

    void read_tree(vvpl& graph) {
        ll n = len(graph);
        FOR(i, 0, n - 2) {
            ll u, v; cin >> u >> v;
            u--; v--;
            graph[u].pb({v, 1});
            graph[v].pb({u, 1});
        }
    }

    template<typename T>
    void read(T& t) {
        cin >> t;
    }

    template<typename T, typename... Args>
    void read(T& t, Args&... args) {
        cin >> t;
        read(args...);
    }
}