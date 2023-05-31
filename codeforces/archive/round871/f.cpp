#include <bits/stdc++.h>
#include <sstream>

//  Definition of the macro.
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define ass(a, b, x, y) (tie(a, b) = make_tuple(x, y));
#define ordered(x, y, z) ((x) <= (y) && (y) <= (z))

using namespace std;

typedef long long ll;

typedef vector<vector<int>> vvi;
typedef vector<int> vi;

typedef vector<vector<ll>> vvl;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef string str;

// Number Theory
ll mod(ll a, ll p) {
    return (a % p + p) % p;
}

ll M = pow(10, 9) + 7;
ll mod(ll a) {
    return mod(a, M);
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

ll gcd(ll a, ll b) {
    if (a > b) {
        ass(a, b, b, a);
    }
    while (a > 0) {
        ass(a, b, b % a, a);
    }
    return b;
}

ll mdiv(ll x, ll y) {
    x = mod(x);
    y = mod(y);
    return mod(x * inv(y, M), M);
}

ll v_p(ll x, ll p) {
    ll res = 0;
    while (x % p == 0) {
        ++res;
        x /= p;
    }
    return res;
}

bool is_pow_of_2(ll n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}


// Looping
#define rep(i, d, u) for(int i = d; i <= u; ++i)
#define dep(i, u, d) for(int i = u; i >= d; --i)
#define foreach(i, c) for(auto i : c)

// Input
long long read_binary() {
    string s;
    cin >> s;
    long long res = 0;
    for (char c : s) {
        res <<= 1;
        if (c == '1') res |= 1;
    }
    return res;
}

// Printing

template<typename T>
void print(const T& t) {
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void print(const T& t, const Args&... args) {
    std::cout << t << " ";
    print(args...);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        os << *it;
        if (it != vec.end() - 1) {
            os << ", ";
        }
    }
    os << "]";
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

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << "{" << p.first << ": " << p.second << "} ";
    }
    os << "}";
    return os;
}

// List manipulation
template<typename T>
vector<T> vslice(const vector<T>& v, int start=0, int end=-1) {
    int n = v.size();
    if (end == -1) {
        end = n;
    }
    int len = end - start;
    vector<T> result(len);
    for (int i = 0; i < len; i++) {
        result[i] = v[start + i];
    }
    return result;
}

template<typename T>
vector<T> vslice2d(const vector<T>& v, int start=0, int end=-1, int start2=0, int end2=-1) {
    int n = v.size();
    int m = v[0].size();
    if (end == -1) {
        end = n;
    }
    if (end2 == -1) {
        end2 = m;
    }
    int len = end - start;
    vector<T> result(len);
    for (int i = 0; i < len; i++) {
        result[i] = vslice(v[start + i], start2, end2);
    }
    return result;
}

template<typename Container, typename T>
bool contains(const Container& c, const T& value) {
    return std::find(c.begin(), c.end(), value) != c.end();
}

bool all(std::vector<bool> v) {
    return std::all_of(v.begin(), v.end(), [](bool b){ return b; });
}

bool any(std::vector<bool> v) {
    return std::any_of(v.begin(), v.end(), [](bool b){ return b; });
}

template <typename T, typename F>
void sort_vec(vector<T>& v, F key) {
    sort(v.begin(), v.end(), [&](const T& a, const T& b) {
        return key(a) < key(b);
    });
}

void reset_graph(vvi& g) {
    rep(i, 0, g.size() - 1)
    {
        g[i].clear();
    }
}


// Maps
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


typedef unordered_map<long long, int, custom_hash> umapli;
typedef unordered_map<ll, ll, custom_hash> umapll;
typedef unordered_set<ll, custom_hash> uset;


int di[4] = {1, 0, -1, 0};
int dj[4] = {0, 1, 0, -1};

// Graphs
void display_tree(int node, int parent, vector<vector<ll>>& adj_list,
                  vector<ll>& labels, int depth = 0) {
    cout << string(depth, ' ') << "Node " << node << " (" << labels[node] << ")" << endl;
    for (int child : adj_list[node]) {
        if (child != parent) {
            display_tree(child, node, adj_list, labels, depth + 1);
        }
    }
}

// Binary Search
#define bisect_left(mid, cond, lo, hi) ({ \
    ll l = (lo), r = (hi), ans = (hi); \
    ll mid; \
    while (l <= r) { \
        mid = (l + r) / 2; \
        if ((cond)) { \
            ans = mid; \
            l = mid + 1; \
        } else { \
            r = mid - 1; \
        } \
    } \
    mid = ans; \
    if (!((cond))) { \
        ans = -1; \
    } \
    ans; \
})

#define bisect_right(mid, cond, lo, hi) ({ \
    ll l = (lo), r = (hi), ans = (hi); \
    ll mid; \
    while (l <= r) { \
        mid = (l + r) / 2; \
        if ((cond)) { \
            ans = mid; \
            r = mid - 1; \
        } else { \
            l = mid + 1; \
        } \
    } \
    mid = ans; \
    if (!((cond))) { \
        ans = hi + 1; \
    } \
    ans; \
})



int main() {
    int a[] = {4, 4, 5, 5, 6, 6};
    // print(bisect_left(i, i * i <= 600, 0, 10));
    // print(bisect_right(i, i * i > 9, 0, 10));
    return 0;
}