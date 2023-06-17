// #include<lib/common.h>
// #include<lib/nt.h>
#include <bits/stdc++.h>
#include <sstream>
#include <functional>
#include <cmath>

using namespace std;

//  Definition of the macro.
#define ass(a, b, x, y) (tie(a, b) = make_tuple(x, y));
#define ordered(x, y, z) ((x) <= (y) && (y) <= (z))

template <typename T>
void chkmin(T& lhs, T rhs) {
	lhs = min(lhs, rhs);
}
template <typename T>
void chkmax(T& lhs, T rhs) {
	lhs = max(lhs, rhs);
}

// Because unsigned sizes are absolutely stupid
// Got burned on 1841C
template <typename T>
inline int len(const T& v) {
    return int(v.size());
}

#define to_str to_string
#define pb push_back

typedef long long ll;

// Looping
#define rep(i, d, u) for(ll i = (d); i <= (u); ++i)
#define dep(i, u, d) for(ll i = (u); i >= (d); --i)
#define irep(i, d, u) for(i = (d); i <= (u); ++i)
#define idep(i, u, d) for(i = (u); i >= (d); --i)
#define srep(i, d, u, s) for(ll i = (d); i <= (u); i += s)
#define cep(t) while(t--)
#define foreach(i, c) for(auto& i : c)
#define foreachp(k, v, c) for (auto& [k, v] : c)

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t do_hash(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(uint64_t x) const {
        return do_hash(x);
    }

    template <typename T1, typename T2, typename T3, typename T4>
    size_t operator()(const std::pair<std::pair<T1, T2>, std::pair<T3, T4>>& key) const {
        auto h1 = (*this)(key.first.first);
        auto h2 = (*this)(key.first.second);
        auto h3 = (*this)(key.second.first);
        auto h4 = (*this)(key.second.second);
        return splitmix64(h1 ^ h2 ^ h3 ^ h4);
    }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng)

template <typename T>
struct Identity {
    constexpr const T& operator()(const T& value) const {
        return value;
    }
};

// Personal vectors
namespace vv {
    template <typename T>
    bool contains(const vector<T>& vec, const T& value) {
        auto it = std::find(vec.begin(), vec.end(), value);
        return (it != vec.end());
    }

    template <typename S, typename T>
    int indexof(const vector<T>& a, const S& element) {
        for (int i = 0; i < len(a); ++i) {
            if (a[i] == element) {
                return i;
            }
        }
        return -1;
    }

    template <typename T>
    static vector<T> arange(T start, T end, T step = 1) {
        vector<T> result;
        for (T value = start; value <= end; value += step) {
            result.pb(value);
        }
        return result;
    }

    template <typename T>
    unordered_map<T, ll, custom_hash> counter(const vector<T>& a, ll start=0, ll end=-1) {
        if (end == -1) {
            end = len(a) - 1;
        }
        unordered_map<T, ll, custom_hash> result;
        rep(i, start, end) {
            result[a[i]]++;
        }

        return result;
    }

    template <typename T>
    vector<T> slice(const vector<T>& a, int start=0, int end=-1) {
        int n = len(a);
        if (end == -1) {
            end = n - 1;
        }
        int length = end - start + 1;
        vector<T> result(length);
        for (int i = 0; i < length; i++) {
            result[i] = a[start + i];
        }
        return result;
    }

    template <typename T, typename S>
    vector<T> slice(const vector<T>& a, const vector<S> idx) {
        int n = len(a);
        int ll = len(idx);
        vector<T> result(ll);
        for (int i = 0; i < ll; i++) {
            result[i] = a[idx[i]];
        }
        return result;
    }

    template <typename T>
    bool all(const vector<T>& a) {
        return std::all_of(a.begin(), a.end(), [](bool b){ return b; });
    }

    template <typename T>
    bool any(const vector<T>& a) {
        return std::any_of(a.begin(), a.end(), [](bool b){ return b; });
    }

    template <typename T>
    T sum(const vector<T>& a, int start=0, int end=-1) {
        if (end < 0) {
            end = len(a) + end;
        }
        return std::accumulate(a.begin(), a.begin() + end + 1, T(0));
    }

    template <typename T>
    T prod(const vector<T>& a, int start=0, int end=-1, ll mm = -1) {
        if (end < 0) {
            end = len(a) + end;
        }
        T p(1);
        rep(i, start, end) {
            p = p * a[i];
            if (mm > 0) {
                p %= mm;
            }
        }
        return p;
    }

    template <typename T>
    T min(const vector<T>& a, int start=0, int end=-1) {
        if (end == -1) {
            end = len(a) - 1;
        }

        T ans = a[start];
        rep(i, start + 1, end) {
            ans = std::min(ans, a[i]);
        }
        return ans;
    }

    template <typename T>
    T max(const vector<T>& a, int start=0, int end=-1) {
        if (end == -1) {
            end = len(a) - 1;
        }

        T ans = a[start];
        rep(i, start + 1, end) {
            ans = std::max(ans, a[i]);
        }
        return ans;
    }

    template <typename T, typename KeyFunc = Identity<T>>
    void sort(vector<T>& a, int start = 0, int end = -1, KeyFunc keyFunc = Identity<T>{}) {
        if (end == -1) {
            end = len(a) - 1;
        }
        if (start >= end || end >= len(a)) {
            return;  // Invalid indices or empty range
        }

        std::sort(a.begin() + start, a.begin() + end + 1,
                [&keyFunc](const T& x, const T& y) {
                    return keyFunc(x) < keyFunc(y);
                });
    }

    template <typename T>
    vector<int> argsort(const vector<T>& a) {
        // Initialize original index positions
        vector<int> indices(a.size());
        for (int i = 0; i < indices.size(); ++i) {
            indices[i] = i;
        }

        // Sort the indices based on comparing array values
        sort(indices.begin(), indices.end(), [&](int i1, int i2) {
            return a[i1] < a[i2];
        });

        return indices;
    }

    template <typename T>
    int argmax(const vector<T>& a, ll start=0, ll end=-1) {
        if (end == -1) {
            end = len(a) - 1;
        }
        T best = a[start];
        int best_idx = start;
        rep(i, start, end) {
            if (a[i] > best) {
                best_idx = i;
                best = a[i];
            }
        }
        return best_idx;
    }

    template <typename T>
    int argmin(const vector<T>& a, ll start=0, ll end=-1) {
        T best = a[start];
        int best_idx = start;
        if (end == -1) {
            end = len(a) - 1;
        }
        rep(i, start, end) {
            if (a[i] < best) {
                best_idx = i;
                best = a[i];
            }
        }
        return best_idx;
    }

    template <typename S, typename T>
    void fill(vector<T>& a, S elem) {
        rep(i, 0, len(a) - 1) {
            a[i] = elem;
        }
    }

    template <typename T>
    vector<T> cumsum(const vector<T>& a) {
        vector<T> ret(a);
        rep(i, 1, len(a) - 1) {
            ret[i] += ret[i - 1];
        }
        return ret;
    }

    template <typename T>
    vector<T> cummax(const vector<T>& a, bool reverse=false) {
        vector<T> ret(a);
        ll n = len(a);
        if (reverse) {
            dep(i, n - 2, 0) {
                ret[i] = std::max(ret[i + 1], ret[i]);
            }
        }
        else {
            rep(i, 1, n - 1)
            {
                ret[i] = std::max(ret[i], ret[i - 1]);
            }
        }
        return ret;
    }

    template <typename T>
    vector<T> cummin(const vector<T>& a, bool reverse=false) {
        vector<T> ret(a);
        ll n = len(a);
        if (reverse) {
            dep(i, n - 2, 0) {
                ret[i] = std::min(ret[i + 1], ret[i]);
            }
        }
        else {
            rep(i, 1, n - 1)
            {
                ret[i] = std::min(ret[i], ret[i - 1]);
            }
        }
        return ret;
    }

    template <typename T>
    bool is_lex_less(const vector<T>& a, const vector<T>& perm) {
        // Compare the permutations lexicographically
        return std::lexicographical_compare(a.begin(), a.end(), perm.begin(), perm.end());
    }
};

typedef vector<vector<int>> vvi;
typedef vector<int> vi;

typedef vector<vector<ll>> vvl;
typedef vector<vector<string>> vvs;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef pair<ll, ll> pl;
typedef vector<vector<pl>> vvpl;

// Maps
typedef unordered_map<ll, ll, custom_hash> umapll;
typedef unordered_map<ll, vl, custom_hash> umaplvl;
typedef unordered_map<string, ll, custom_hash> umapstrl;
typedef unordered_map<ll, string, custom_hash> umaplstr;

template <typename K, typename V>
using umap = unordered_map<K, V, custom_hash>;

typedef unordered_set<ll, custom_hash> usetl;
template <typename K>
using uset = unordered_set<K, custom_hash>;

umapll operator+(const umapll& lhs, const umapll& rhs) {
    umapll result = lhs;

    for (const auto& pair : rhs) {
        result[pair.first] += pair.second;
    }

    return result;
}

template <typename Key, typename Value>
Value mget(const std::unordered_map<Key, Value, custom_hash>& map, const Key& key) {
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    return Value{}; // Default-constructed value
}

template <typename K, typename V>
void initmap(umap<K, V>& counts) {
    counts.reserve(250000);
    counts.max_load_factor(0.25);
}

// List manipulation
typedef priority_queue<ll, vl, greater<ll>> minheap;
typedef priority_queue<ll, vl, less<ll>> maxheap;


#define RC(typ, expr, x, lo, hi) ({ \
    typ lcret; \
    rep(x, lo, hi) {\
        lcret.push_back(expr); \
    } \
    lcret; \
})

#define RCC(typ, expr, x, lo, hi, cond) ({ \
    typ lcret; \
    rep(x, lo, hi) {\
        if (cond) \
        lcret.push_back(expr); \
    } \
    lcret; \
})

#define LC(typ, expr, x, arr) ({ \
    typ lcret; \
    foreach(x, arr) {\
        lcret.push_back(expr); \
    } \
    lcret; \
})



int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

// Binary Search
#define largest_st(bbbmid, cond, lo, hi) ({ \
    ll bbbl = (lo), bbbr = (hi), bbbans = (hi); \
    ll bbbmid; \
    while (bbbl <= bbbr) { \
        bbbmid = (bbbl + bbbr) / 2; \
        if ((cond)) { \
            bbbans = bbbmid; \
            bbbl = bbbmid + 1; \
        } else { \
            bbbr = bbbmid - 1; \
        } \
    } \
    bbbmid = bbbans; \
    if (!((cond))) { \
        bbbans = (lo)-1; \
    } \
    bbbans; \
})

#define smallest_st(mid, cond, lo, hi) ({ \
    ll bbbl = (lo), bbbr = (hi), bbbans = (hi); \
    ll mid; \
    while (bbbl <= bbbr) { \
        mid = (bbbl + bbbr) / 2; \
        if ((cond)) { \
            bbbans = mid; \
            bbbr = mid - 1; \
        } else { \
            bbbl = mid + 1; \
        } \
    } \
    mid = bbbans; \
    if (!((cond))) { \
        bbbans = (hi) + 1; \
    } \
    bbbans; \
})

// Strings
namespace str {
    string lower(const string& s) {
        string result = s;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    string upper(const string& s) {
        string result = s;
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    template <typename T>
    string join(const vector<T>& elements, const string& delimiter) {
        ostringstream oss;
        for (size_t i = 0; i < elements.size(); ++i) {
            if (i != 0) {
                oss << delimiter;
            }
            oss << elements[i];
        }
        return oss.str();
    }

    int stoi(char ch) {
        string mystr(1, ch);
        int num = stoi(mystr);
        return num;
    }

    string slice(const string& s, int start, int end) {
        return s.substr(start, end - start);
    }

    vector<string> split(const string& s, char delimiter) {
        vector<string> result;
        stringstream ss(s);
        string token;

        while (getline(ss, token, delimiter)) {
            result.push_back(token);
        }

        return result;
    }
}

namespace mset {
    template <typename S, typename T>
    void mset_del(S& ss, T x) {
        ss.erase(ss.find(x));
    }

    template <typename S, typename T>
    void mset_move(S& ss1, S& ss2, T x) {
        auto ptr = ss1.find(x);
        if (ptr != ss1.end()) {
            ss1.erase(ptr);
            ss2.insert(x);
        }
        else {
            throw std::out_of_range("element not found");
        }
    }

    template <typename T>
    T min(multiset<T>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set min");
        }
        return *(ss.begin());
    }

    template <typename T>
    T max(multiset<T>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set max");
        }
        return *(ss.rbegin());
    }

    template <typename T>
    T min(set<T>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set min");
        }
        return *(ss.begin());
    }

    template <typename T>
    T max(set<T>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set max");
        }
        return *(ss.rbegin());
    }
}


typedef multiset<ll> msetl;



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
};

typedef ndarray<ll> llarray;
typedef ndarray<int> intarray;


// Input
namespace inp {
    long long binary() {
        string s;
        cin >> s;
        long long res = 0;
        for (char c : s) {
            res <<= 1;
            if (c == '1') res |= 1;
        }
        return res;
    }

    void array(vl& arr, int n) {
        rep(i, 0, n - 1) {
            cin >> arr[i];
        }
    }

    void array1(vl& arr, int n) {
        rep(i, 1, n) {
            cin >> arr[i];
        }
    }

}

// Printing

void init() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
}

template<typename T>
void print(const T& t) {
    #ifdef INTERACTIVE
    std::cout << t << std::endl;
    #else
    std::cout << t << "\n";
    #endif
}

template<typename T, typename... Args>
void print(const T& t, const Args&... args) {
    std::cout << t << " ";
    print(args...);
}

template<typename T>
void dprint(const T& t) {
    #ifndef ONLINE_JUDGE
    std::cout << t << std::endl;
    #endif
}

template<typename T, typename... Args>
void dprint(const T& t, const Args&... args) {
    #ifndef ONLINE_JUDGE
    std::cout << t << " ";
    print(args...);
    #endif
}

// Fancy variable debugging, stolen from:
// https://codeforces.com/blog/entry/79024
#ifndef ONLINE_JUDGE
int recur_depth = 0;
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":"<<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}
#else
#define dbg(x)
#endif

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const unordered_map<K, V, custom_hash>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const map<K, V>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << *it;
        if (it != v.end() - 1) {
            os << " ";
        }
    }
    return os;
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T, custom_hash>& s) {
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

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

namespace nt {
    vl primes;
    vl isnotprime;
    bool sieve_done = false;

    void do_sieve(ll max_prime) {
        isnotprime.resize(max_prime + 1);
        rep(d, 2, max_prime) {
            if (!isnotprime[d]) {
                primes.push_back(d);

                int x = 2 * d;
                while (x <= max_prime) {
                    isnotprime[x] = true;
                    x += d;
                }
            }
        }
        sieve_done = true;
    }

    bool is_prime(ll n) {
        // Checks if n is prime
        if (n <= 1) {
            return false;
        }

        ll p = *prev(primes.end());
        if (p * p < n) {
            throw out_of_range("Generate more primes please");
        }

        ll i = 0;
        while (primes[i] * primes[i] <= n) {
            if (n % primes[i] == 0) {
                return false;
            }
            i++;
        }
        return true;
    }

    ll sum_digits(ll n, ll b) {
        int sum = 0;
        while (n > 0) {
            sum += n % b;
            n /= b;
        }
        return sum;
    }

    vl get_digits(ll n, ll b) {
        vl ans;
        while (n > 0) {
            ans.push_back(n % b);
            n /= b;
        }

        return ans;
    }

    ll digits_to_num(vl& digs, ll b) {
        ll s = 0;
        dep(i, digs.size() - 1, 0) {
            s *= b;
            s += digs[i];
        }
        return s;
    }

    ll mod(ll a, ll p) {
        if (p > 0) {
            return (a % p + p) % p;
        }
        return a;
    }

    // ll M = std::pow(10, 9) + 7;
    ll MOD = 998244353LL;
    ll mod(ll a) {
        return mod(a, MOD);
    }

    // Function to calculate (base^exponent) % modulus using repeated squaring
    ll pow(ll base, ll exponent, ll modulus=MOD) {
        ll result = 1;

        while (exponent > 0) {
            // If the exponent is odd, multiply the result by base
            if (exponent & 1) {
                if (modulus > 0) {
                    result = (result * base) % modulus;
                }
                else {
                    result = result * base;
                }
            }

            // Square the base and reduce the exponent by half
            if (modulus > 0) {
                base = (base * base) % modulus;
            }
            else {
                base = base * base;
            }
            exponent >>= 1;
        }

        return result;
    }

    ll inv(ll x, ll y) {
        ll p = y;

        ll ax = 1;
        ll ay = 0;
        while (x > 0) {
            ll q = y / x;
            tie(ax, ay) = make_tuple(ay - q * ax, ax);
            tie(x, y) = make_tuple(y % x, x);
        }

        return mod(ay, p);
    }

    ll mdiv(ll x, ll y, ll m=MOD) {
        if (m <= 0) {
            return x / y;
        }
        x = mod(x);
        y = mod(y);
        return mod(x * inv(y, m), m);
    }

    ll v_p(ll x, ll p) {
        ll res = 0;
        while (x % p == 0) {
            ++res;
            x /= p;
        }
        return res;
    }

    ll factorial(ll x) {
        ll p = 1;
        rep(i, 1, x) {
            p *= i;
            p = mod(p);
        }
        return p;
    }

    bool is_pow_of_2(ll n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    }

    ll phi(ll n) {
        ll result = n;
        if (!sieve_done) {
            throw out_of_range("Sieve not done, please run do_sieve");
        }

        for (ll prime : primes) {
            if (prime * prime > n)
                break;
            if (n % prime == 0) {
                while (n % prime == 0) {
                    n /= prime;
                }
                result -= result / prime;
            }
        }

        if (n > 1) {
            result -= result / n;
        }

        return result;
    }

    vl divisors(ll n) {
        vl out;
        ll i = 1;
        while (i * i <= n) {
            if (n % i == 0) {
                out.pb(i);
                if (i * i != n) {
                    out.pb(n / i);
                }
            }
            i++;
        }
        vv::sort(out);

        return out;
    }

    ll num_divisors(ll n) {
        ll divisors = 1;

        for (ll prime : primes) {
            if (prime * prime > n)
                break;

            ll count = 0;
            while (n % prime == 0) {
                n /= prime;
                count++;
            }

            divisors *= (count + 1);
        }

        if (n > 1) {
            divisors *= 2;
        }

        return divisors;
    }

    ll sum_divisors(ll n) {
        ll sum = 1;

        for (ll prime : primes) {
            if (prime * prime > n)
                break;

            if (n % prime == 0) {
                ll factorSum = 1;
                ll power = 1;
                while (n % prime == 0) {
                    n /= prime;
                    power *= prime;
                    factorSum += power;
                }
                sum *= factorSum;
            }
        }

        if (n > 1) {
            sum *= (n + 1);
        }

        return sum;
    }

    umapll primeFactorization(ll n) {
        umapll factors;

        for (ll prime : primes) {
            if (prime * prime > n)
                break;

            ll exponent = 0;
            while (n % prime == 0) {
                n /= prime;
                exponent++;
            }

            if (exponent > 0) {
                factors[prime] = exponent;
            }
        }

        if (n > 1) {
            factors[n] = 1;
        }

        return factors;
    }
}

namespace combo {
    ll choose(ll n, ll k, ll m=-1) {
        ll p = 1;
        rep(i, 1, k) {
            p = p * (n - k + i) / i;
            if (m > 0) {
                p = nt::mod(p, m);
            }
        }
        return p;
    }

    vl precompute_choose(ll n1, ll n2, ll k, ll m=-1) {
        vl result(n2 - n1 + 1);
        ll idx = max(k - n1, 0LL);
        if (idx > n2 - n1) {
            return result;
        }
        if (n1 + idx == k) {
            result[idx] = 1;
        }
        else {
            result[idx] = choose(n1 + idx, k, m);
        }
        rep(i, idx + 1, n2 - n1) {
            result[i] = result[i - 1] * (n1 + i) / (n1 + i - k);
            if (m > 0) {
                result[i] %= m;
            }
        }
        return result;
    }

    vl precompute_choose2(ll n, ll k1, ll k2, ll m = -1) {
        vl result(k2 - k1 + 1);
        result[0] = choose(n, k1, m=m);
        rep(i, k1 + 1, k2) {
            if (m > 0) {
                result[i] = nt::mdiv(
                    result[i - 1] * (n - i + 1), i, m);
            }
            else {
                result[i] = result[i - 1] * (n - i + 1) / i;
            }
        }
        return result;
    }

    using namespace nt;
    vl precompute_catalan(ll n, ll m = MOD) {
        vl result(n + 1);
        result[0] = 1;
        rep(i, 1, n) {
            result[i] = nt::mod(result[i - 1] * 2 * i, m);
            result[i] = nt::mod(result[i] * (2 * i - 1), m);
            result[i] = nt::mdiv(result[i], i + 1, m);
            result[i] = nt::mdiv(result[i], i, m);
        }
        return result;
    }
}

void solve() {
    ll a, b, c, d; cin >> a >> b >> c >> d;

    ll x, y;

    auto works = [&](ll m, ll n) -> bool {
        return ordered(a + 1, m, c) && ordered(b + 1, n , d);
    };

    // Check for dumb solutions like multiples
    x = 2 * a;
    y = 2 * b;
    if (works(x, y)) {
        print(x, y);
        return;
    }

    // Try multiple of b for x and multiple of a for y
    x = (a / b + 1) * b;
    y = (b / a + 1) * a;
    if (works(x, y)) {
        print(x, y);
        return;
    }

    // Do the dumb thing of iterating over divisors
    vl da = nt::divisors(a);
    vl db = nt::divisors(b);

    foreach(a1, da) {
        ll a2 = a / a1;

        ll l1 = a2 + 1;
        ll r1 = c / a1;

        ll l2 = b / a2 + 1;
        ll r2 = d / a2;

        // Street math, see if we get lucky with one of them
        int idx1 = largest_st(z, db[z] <= r1 - l1 + 1, 0, len(db) - 1);
        int idx2 = largest_st(z, db[z] <= r2 - l2 + 1, 0, len(db) - 1);
        
        if (idx1 >= 0 && idx2 >= 0 && db[idx1] * db[idx2] >= b) {
            ll b1 = db[idx1];
            ll b2 = b / b1;
            ll x0 = a1 * b1;
            ll y0 = a2 * b2;
            print((c / x0) * x0, (d / y0) * y0);
            return;
        }

        if (r1 - l1 < r2 - l2) {
            rep(zz, l1, r1) {
                foreach(b1, db) {
                    if (zz % b1 == 0) {
                        ll b2 = b / b1;
                        if (ordered(l2, b2, r2)) {
                            ll x0 = a1 * b1;
                            ll y0 = a2 * b2;
                            print((c / x0) * x0, (d / y0) * y0);
                        }
                    }
                }
            }
        }

        (r1 - l1 < r2 - l2) {
            rep(zz, l1, r1) {
                foreach(b1, db) {
                    if (zz % b1 == 0) {
                        ll b2 = b / b1;
                        if (ordered(l2, b2, r2)) {
                            ll x0 = a1 * b1;
                            ll y0 = a2 * b2;
                            print((c / x0) * x0, (d / y0) * y0);
                        }
                    }
                }
            }
        }

        // foreach(b1, db) {
        //     ll a2 = a / a1;
        //     ll b2 = b / b1;

        //     ll x0 = a1 * b1;
        //     ll y0 = a2 * b2;

        //     if (a / x0 < c / x0 && b / y0 < d / y0) {
        //         print((c / x0) * x0, (d / y0) * y0);
        //         return;
        //     }
        // }
    }

    print(-1, -1);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) {
        solve();
    }
    return 0;
}