// #include<lib/common.h>
#include <bits/stdc++.h>
#include <sstream>
#include <functional>
#include <cmath>

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
        for (int i = 0; i < len(indices); ++i) {
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
        return int(ch - '0');
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

    void array(vl& arr, int n) {
        rep(i, 0, n - 1) {
            cin >> arr[i];
        }
    }

    void array(vi& arr, int n) {
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
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; cerr<<string(recur_depth, '\t')<<__func__<<":"<<__LINE__<<"\t"<<#x<<" = "<<x_<<endl;}
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

void solve() {
    ll n, x; cin >> n >> x;

    vl a(n);
    vl b(n);
    vl c(n);
    inp::array(a, n); inp::array(b, n); inp::array(c, n);

    if (x == 0) {
        print("Yes");
        return;
    }

    rep(i, 1, n - 1) {
        a[i] |= a[i - 1];
        b[i] |= b[i - 1];
        c[i] |= c[i - 1];
    }

    // Check for first digit in which we are screwed
    ll ai = 0, bi = 0 , ci = 0;
    while (ai < n && (a[ai] & (~x)) == 0) {
        ai++;
    }
    while (bi < n && (b[bi] & (~x)) == 0) {
        bi++;
    }
    while (ci < n && (c[ci] & (~x)) == 0) {
        ci++;
    }

    auto access = [](vl& arr, ll i) -> ll {
        if (i >= 0) {
            return arr[i];
        }
        else {
            return 0;
        }
    };
    ll final_value = access(a, ai - 1) | access(b, bi - 1) | access(c, ci - 1);

    print(final_value == x ? "Yes" : "No");
}

int main() {
    int t; cin >> t;
    cep(t) {
        solve();
    }
    return 0;
}