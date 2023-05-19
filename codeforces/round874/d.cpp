#include <bits/stdc++.h>
#include <sstream>
#include <functional>
#include <cmath>

//  Definition of the macro.
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

template <typename T>
struct Identity {
    constexpr const T& operator()(const T& value) const {
        return value;
    }
};

// Number Theory

int sum_digits(int n, int b) {
    int sum = 0;
    while (n > 0) {
        sum += n % b;
        n /= b;
    }
    return sum;
}

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
    a = abs(a);
    b = abs(b);
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
#define rep(i, d, u) for(ll i = d; i <= u; ++i)
#define dep(i, u, d) for(ll i = u; i >= d; --i)
#define cep(t) while(t--)
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

void init() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
}

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

template <typename T>
std::vector<T> arange(T start, T end, T step = 1) {
    std::vector<T> result;
    for (T value = start; value < end; value += step) {
        result.push_back(value);
    }
    return result;
}

// List manipulation
typedef priority_queue<ll, vl, greater<ll>> minheap;
typedef priority_queue<ll, vl, less<ll>> maxheap;

template <typename T>
int index(const vector<T>& vec, const T& element) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == element) {
            return i;
        }
    }
    throw out_of_range("Element not found in vector");
}

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

#define RC(typ, expr, x, lo, hi) ({ \
    typ lcret; \
    rep(x, lo, hi) {\
        lcret.push_back(expr); \
    } \
    lcret; \
})


template <typename T, typename KeyFunc = Identity<T>>
void sort_vec(vector<T>& vec, size_t start, size_t end, KeyFunc keyFunc = Identity<T>{}) {
    if (start >= end || end >= vec.size()) {
        return;  // Invalid indices or empty range
    }

    sort(vec.begin() + start, vec.begin() + end + 1,
              [&keyFunc](const T& a, const T& b) {
                  return keyFunc(a) < keyFunc(b);
              });
}

template <typename T>
vector<int> argsort(const vector<T>& array) {
    // Initialize original index positions
    vector<int> indices(array.size());
    for (int i = 0; i < indices.size(); ++i) {
        indices[i] = i;
    }

    // Sort the indices based on comparing array values
    sort(indices.begin(), indices.end(), [&array](int i1, int i2) {
        return array[i1] < array[i2];
    });

    return indices;
}

void reset_graph(vvi& g) {
    rep(i, 0, g.size() - 1)
    {
        g[i].clear();
    }
}

void cumsum(vl& arr) {
    rep(i, 1, arr.size() - 1) {
        arr[i] += arr[i - 1];
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
string str_lower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string str_upper(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Numpy

template<typename T>
class ndarray {
public:
    int n_rows; // number of rows
    int n_cols; // number of columns
    std::vector<T> data; // vector to store the data

    // Constructor to initialize the 2D array with given shape
    ndarray(int n_rows_, int n_cols_) : n_rows(n_rows_), n_cols(n_cols_) {
        data = std::vector<T>(n_rows * n_cols);
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
    std::vector<T> get_data() const {
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
    
    // Fill the array with a particular value
    void fill(const T& value) {
        std::fill(data.begin(), data.end(), value);
    }

    void fill(const T& value, int istart, int iend, int jstart, int jend) {
        for (int i = istart; i < iend; i++)
        {
            for (int j = jstart; j < jend; j++)
            {
                (*this)(i, j) = value;
            }
        }

    }

    ndarray<T> slice(int istart, int iend, int jstart, int jend) {
        ndarray<T> subarray(iend - istart, jend - jstart);
        for (int i = istart; i < iend; i++)
        {
            for (int j = jstart; j < jend; j++)
            {
                subarray(i - istart, j - jstart) = (*this)(i, j);
            }
        }
        return subarray;
    }
};

// Overload the << operator to print the elements of the 2D array
template<typename T>
std::ostream& operator<<(std::ostream& os, const ndarray<T>& arr) {
    for (int i = 0; i < arr.get_n_rows(); i++) {
        for (int j = 0; j < arr.get_n_cols(); j++) {
            os << arr(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

template <typename T>
string str_join(const vector<T>& elements, const string& delimiter) {
    ostringstream oss;
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i != 0) {
            oss << delimiter;
        }
        oss << elements[i];
    }
    return oss.str();
}

typedef ndarray<ll> llarray;
typedef ndarray<int> intarray;


str solve() {
    ll n;
    cin >> n;

    vl p(n);
    rep(i, 0, n - 1) {
        cin >> p[i];
    }

    if (n == 1) {
        return to_string(n);
    }


    // Check for the index of max element
    int m_idx = index(p, n);

    // Main case
    if (1 <= m_idx && m_idx <= n - 2) {
        int lidx = m_idx - 2;
        while (lidx >= 0 && p[lidx] > p[0]) {
            lidx--;
        }
        lidx++;

        vl output;
        rep(i, m_idx, n - 1) {
            output.push_back(p[i]);
        }
        dep(i, m_idx - 1, lidx) {
            output.push_back(p[i]);
        }
        rep(i, 0, lidx - 1) {
            output.push_back(p[i]);
        }
        return str_join(output, " ");
    }

    if (m_idx == n - 1) {
        // Put the n at the start, and reverse sort it let's go
        int lidx = m_idx - 1;
        while (lidx >= 0 && p[lidx] > p[0]) {
            lidx--;
        }
        lidx++;
        vl output;
        rep(i, m_idx, n - 1) {
            output.push_back(p[i]);
        }
        dep(i, m_idx - 1, lidx) {
            output.push_back(p[i]);
        }
        rep(i, 0, lidx - 1) {
            output.push_back(p[i]);
        }
        return str_join(output, " ");
    }

    int mm_idx = index(p, n - 1);

    if (mm_idx == n - 1) {
        // Just reverse the whole thing
        vl output;
        output.push_back(n - 1);
        rep(i, 0, n - 2) {
            output.push_back(p[i]);
        }

        return str_join(output, " ");
    }
    else {
        vl output;
        rep(i, mm_idx, n - 1) {
            output.push_back(p[i]);
        }

        output.push_back(p[mm_idx - 1]);

        rep(i, 0, mm_idx - 2) {
            output.push_back(p[i]);
        }

        return str_join(output, " ");
    }
}

int main () {
    init();
    ll t;
    cin >> t;
    string s;
    cep(t) {
        print(solve());
    }
}