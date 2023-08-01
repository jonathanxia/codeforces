// #include<lib/common.h>
// #include<lib/vv.h>
// #include<lib/nt.h>
// #include<lib/ndarray.h>
#include <bits/stdc++.h>

using namespace std;

//  Definition of the macro.
#define ass(a, b, x, y) (tie(a, b) = make_tuple(x, y));
#define ordered(x, y, z) ((x) <= (y) && (y) <= (z))

template <typename T, typename S>
void chkmin(T& lhs, S rhs) {
	lhs = min(lhs, T(rhs));
}
template <typename T, typename S>
void chkmax(T& lhs, S rhs) {
	lhs = max(lhs, T(rhs));
}

// Because unsigned sizes are absolutely stupid
// Got burned on 1841C
template <typename T>
inline int len(const T& v) {
    return int(v.size());
}

#define to_str to_string
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()

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

    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2>& key) const {
        return (*this)(((*this)(key.first) * 37) ^ (*this)(key.second));
    }

    size_t operator()(string s) const {
        uint64_t out = 0;
        for (int i = 0; i < (int) (s.size()); i++) {
            out = out * 37 + s[i];
        }
        return do_hash(out);
    }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng)

typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef vector<string> vs;

typedef vector<vector<ll>> vvl;
typedef vector<vector<string>> vvs;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef pair<ll, ll> pl;
typedef vector<vector<pl>> vvpl;
typedef vector<pl> vpl;

// Maps
typedef unordered_map<ll, ll, custom_hash> umapll;
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

#define RC(typ, expr, x, lo, hi) ({ \
    typ lcret; \
    rep(x, lo, hi) {\
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
// NOTE: lo and hi are inclusive;
// Eg. largest_st(x, a[x] < 5, 0, 10) will search for x between [0, 10]
#define largest_st(mid, cond, lo, hi) ({                          \
    ll BISEARCH_l = (lo), BISEARCH_r = (hi), BISEARCH_ans = (hi); \
    ll mid;                                                       \
    while (BISEARCH_l <= BISEARCH_r) {                            \
        mid = (BISEARCH_l + BISEARCH_r) / 2;                      \
        if ((cond)) {                                             \
            BISEARCH_ans = (mid);                                 \
            BISEARCH_l = (mid) + 1;                               \
        } else {                                                  \
            BISEARCH_r = (mid)-1;                                 \
        }                                                         \
    }                                                             \
    mid = BISEARCH_ans;                                           \
    if (!((cond))) {                                              \
        BISEARCH_ans = (lo)-1;                                    \
    }                                                             \
    BISEARCH_ans;                                                 \
})

#define smallest_st(mid, cond, lo, hi) ({                         \
    ll BISEARCH_l = (lo), BISEARCH_r = (hi), BISEARCH_ans = (hi); \
    ll mid;                                                       \
    while (BISEARCH_l <= BISEARCH_r) {                            \
        mid = (BISEARCH_l + BISEARCH_r) / 2;                      \
        if ((cond)) {                                             \
            BISEARCH_ans = (mid);                                 \
            BISEARCH_r = (mid)-1;                                 \
        } else {                                                  \
            BISEARCH_l = (mid) + 1;                               \
        }                                                         \
    }                                                             \
    mid = BISEARCH_ans;                                           \
    if (!((cond))) {                                              \
        BISEARCH_ans = (hi) + 1;                                  \
    }                                                             \
    BISEARCH_ans;                                                 \
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
        return int(ch - '0');
    }

    string slc(const string& s, int start, int end) {
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

    string fill(const string& s, int num) {
        string ret = "";
        for (int i = 0; i < num; i++) {
            ret += s;
        }
        return ret;
    }
}

namespace mset {
    template <typename S, typename T>
    void mset_del(S& ss, T x) {
        auto it = ss.find(x);
        if (it == ss.end()) {
            throw std::out_of_range("element not found");
        }
        ss.erase(it);
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

    template <typename T, typename V>
    T min(map<T, V>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set min");
        }
        return (ss.begin())->first;
    }

    template <typename T, typename V>
    T max(map<T, V>& ss) {
        if (ss.empty()) {
            throw out_of_range("Empty set max");
        }
        return (ss.rbegin())->first;
    }
}


typedef multiset<ll> msetl;

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
    #ifdef DEBUG
    std::cout << t << std::endl;
    #endif
    #endif
}

template<typename T, typename... Args>
void dprint(const T& t, const Args&... args) {
    #ifndef ONLINE_JUDGE
    #ifdef DEBUG
    std::cout << t << " ";
    print(args...);
    #endif
    #endif
}

// Fancy variable debugging, stolen from:
// https://codeforces.com/blog/entry/79024
#ifndef ONLINE_JUDGE
    #ifdef DEBUG
    int recur_depth = 0;
    #define dbg(x) {++recur_depth; auto x_=x; --recur_depth; cout<<string(recur_depth, '\t')<<__func__<<":"<<__LINE__<<"\t"<<#x<<" = "<<x_<<endl;}
    #else
    #define dbg(x)
    #endif
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

template<typename T>
istream& operator>>(istream& input, vector<T>& vec) {
    for (auto& element : vec) {
        input >> element;
    }
    return input;
}

template<typename S, typename T>
istream& operator>>(istream& input, pair<S, T>& p) {
    input >> p.first >> p.second;
    return input;
}

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
    inline vector<T> arange(T start, T end, T step = 1) {
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
    vector<T> slc(const vector<T>& a, int start=0, int end=-1) {
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
    vector<T> slc(const vector<T>& a, const vector<S> idx) {
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

        std::stable_sort(a.begin() + start, a.begin() + end + 1,
                [&keyFunc](const T& x, const T& y) {
                    return keyFunc(x) < keyFunc(y);
                });
    }

    template <typename T>
    vector<int> argsort(const vector<T>& a) {
        // Initialize original index positions
        vector<int> indices(a.size());
        for (int i = 0; i < len(indices); ++i) {
            indices[i] = i;
        }

        // Sort the indices based on comparing array values
        std::stable_sort(indices.begin(), indices.end(), [&](int i1, int i2)
                         { return a[i1] < a[i2]; });

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

    vl get_digits(ll n, ll b, ll pad=-1) {
        vl ans;
        while (n > 0) {
            ans.push_back(n % b);
            n /= b;
        }
        while (len(ans) < pad) {
            ans.pb(0);
        }
        return ans;
    }

    ll digits_to_num(const vl& digs, ll b) {
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

    // ll MOD = 998244353LL;
    ll MOD = 1000000007LL;
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
            exponent >>= 1;
            if (exponent == 0) {
                break;
            }

            // Square the base and reduce the exponent by half
            if (modulus > 0) {
                base = (base * base) % modulus;
            }
            else {
                base = base * base;
            }
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

    vl precompute_fac(ll n, ll m = MOD) {
        vl result(n + 1);
        result[0] = 1;
        rep(i, 1, n) {
            result[i] = mod(result[i - 1] * i, m);
        }
        return result;
    }
}

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


using namespace vv;
using namespace nt;

vl facs;

void solve() {
    ll n, m; cin >> n >> m;
    vl s(n); cin >> s;

    // Precompute the distribution
    // probability of guy in front starting at y
    // and you starting at x, what's the probability
    // that you make it to 1
    llarray probs(m + 4, m + 4);
    probs.set_col(0, 1);
    probs.set_row(0, 1);


    rep(i, 0, m + 3) {
        rep(j, 0, m + 3) {
            if (i < j) {
                probs(i, j) = 0;
            }
            if (i == j) {
                if (i >= 1) probs(i, j) = 0;
            }
        }
    }


    rep(i, 1, m + 3) {
        rep(j, 1, i - 1) {
            probs(i, j) = mdiv(probs(i, j - 1) + probs(i - 1, j), 2);
        }
    }

    ll ans = m + 1 - s[n - 1];

    rep(idx, 0, n - 2) {
        rep(y, s[idx] + 1, m + 1) {
            // What's the probability that I make it to index y?
            ll dist_to_travel = y - s[idx];
            ll other_guy = y - s[idx + 1];
            if (other_guy < 0) {
                ans += 1;
                continue;
            }

            ans += probs(dist_to_travel, other_guy);
            ans = mod(ans);
        }
    }

    print(ans);
}


int main() {
    init();
    int t = 1;
    facs = combo::precompute_fac(502);
    cep(t) solve();
    return 0;
}