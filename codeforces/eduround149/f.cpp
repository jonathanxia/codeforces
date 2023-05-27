#include <bits/stdc++.h>
#include <sstream>
#include <functional>
#include <cmath>

//  Definition of the macro.
#define ass(a, b, x, y) (tie(a, b) = make_tuple(x, y));
#define ordered(x, y, z) ((x) <= (y) && (y) <= (z))

#define to_str to_string
#define pb push_back

using namespace std;

typedef long long ll;

// Looping
#define rep(i, d, u) for(ll i = d; i <= u; ++i)
#define dep(i, u, d) for(ll i = u; i >= d; --i)
#define irep(i, d, u) for(i = d; i <= u; ++i)
#define idep(i, u, d) for(i = u; i >= d; --i)
#define srep(i, d, u, s) for(ll i = d; i <= u; i += s)
#define cep(t) while(t--)
#define foreach(i, c) for(auto i : c)

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

template <typename T>
struct Identity {
    constexpr const T& operator()(const T& value) const {
        return value;
    }
};

// Personal vectors
template<typename T>
class vec : public vector<T> {
public:
    using std::vector<T>::vector;  // Inherit base class constructors

    bool contains(const T& value) const {
        auto it = std::find(this->begin(), this->end(), value);
        return (it != this->end());
    }

    int indexof(const T& element) {
        for (int i = 0; i < this->size(); ++i) {
            if ((*this)[i] == element) {
                return i;
            }
        }
        return -1;
    }

    static vec<T> arange(T start, T end, T step = 1) {
        vec<T> result;
        for (T value = start; value < end; value += step) {
            result.push_back(value);
        }
        return result;
    }

    unordered_map<T, ll, custom_hash> counter(ll start=0, ll end=-1) {
        if (end == -1) {
            end = this->size() - 1;
        }
        unordered_map<T, ll, custom_hash> result;
        rep(i, start, end) {
            result[(*this)[i]]++;
        }

        return result;
    }

    vec<T> slice(int start=0, int end=-1) {
        int n = this->size();
        if (end == -1) {
            end = n;
        }
        int len = end - start;
        vec<T> result(len);
        for (int i = 0; i < len; i++) {
            result[i] = (*this)[start + i];
        }
        return result;
    }

    bool all() {
        return std::all_of(this->begin(), this->end(), [](bool b){ return b; });
    }

    bool any() {
        return std::any_of(this->begin(), this->end(), [](bool b){ return b; });
    }

    T sum() {
        return std::accumulate(this->begin(), this->end(), T(0));
    }

    T min(int start=0, int end=-1) {
        if (end == -1) {
            end = this->size();
        }

        T ans = (*this)[start];
        rep(i, start + 1, end - 1) {
            ans = std::min(ans, (*this)[i]);
        }
        return ans;
    }

    T max(int start=0, int end=-1) {
        if (end == -1) {
            end = this->size();
        }

        T ans = (*this)[start];
        rep(i, start + 1, end - 1) {
            ans = std::max(ans, (*this)[i]);
        }
        return ans;
    }

    template <typename KeyFunc = Identity<T>>
    void sort(int start = 0, int end = -1, KeyFunc keyFunc = Identity<T>{}) {
        if (end == -1) {
            end = this->size() - 1;
        }
        if (start >= end || end >= this->size()) {
            return;  // Invalid indices or empty range
        }

        std::sort(this->begin() + start, this->begin() + end + 1,
                [&keyFunc](const T& a, const T& b) {
                    return keyFunc(a) < keyFunc(b);
                });
    }

    vec<int> argsort() {
        // Initialize original index positions
        vec<int> indices(this->size());
        for (int i = 0; i < indices.size(); ++i) {
            indices[i] = i;
        }

        // Sort the indices based on comparing array values
        sort(indices.begin(), indices.end(), [&](int i1, int i2) {
            return (*this)[i1] < (*this)[i2];
        });

        return indices;
    }

    int argmax() {
        T best = (*this)[0];
        int best_idx = 0;
        rep(i, 0, this->size() - 1) {
            if ((*this)[i] > best) {
                best_idx = i;
                best = (*this)[i];
            }
        }
        return best_idx;
    }

    int argmin() {
        T best = (*this)[0];
        int best_idx = 0;
        rep(i, 0, this->size() - 1) {
            if ((*this)[i] < best) {
                best_idx = i;
                best = (*this)[i];
            }
        }
        return best_idx;
    }

    template <typename S>
    void fill(S elem) {
        rep(i, 0, this->size() - 1) {
            (*this)[i] = elem;
        }
    }

    vec<T> cumsum() {
        vec<T> ret(*this);
        rep(i, 1, this->size() - 1) {
            ret[i] += ret[i - 1];
        }
        return ret;
    }

    vec<T> cummax(bool reverse=false) {
        vec<T> ret(*this);
        if (reverse) {
            dep(i, this->size() - 2, 0) {
                ret[i] = std::max(ret[i + 1], ret[i]);
            }
        }
        else {
            rep(i, 1, this->size() - 1)
            {
                ret[i] = std::max(ret[i], ret[i - 1]);
            }
        }
        return ret;
    }

    vec<T> cummin(bool reverse=false) {
        vec<T> ret(*this);
        if (reverse) {
            dep(i, this->size() - 2, 0) {
                ret[i] = std::min(ret[i + 1], ret[i]);
            }
        }
        else {
            rep(i, 1, this->size() - 1)
            {
                ret[i] = std::min(ret[i], ret[i - 1]);
            }
        }
        return ret;
    }

    bool is_lex_less(const vec<T>& perm) {
        // Compare the permutations lexicographically
        return std::lexicographical_compare(this->begin(), this->end(), perm.begin(), perm.end());
    }
};

typedef vec<vec<int>> vvi;
typedef vec<int> vi;

typedef vec<vec<ll>> vvl;
typedef vec<ll> vl;
typedef vec<bool> vb;
typedef pair<ll, ll> pl;
typedef vec<vec<pl>> vvpl;

typedef string str;

// Maps

typedef unordered_map<long long, int, custom_hash> umapli;
typedef unordered_map<ll, ll, custom_hash> umapll;
typedef unordered_map<ll, vl, custom_hash> umaplvl;
typedef unordered_map<str, ll, custom_hash> umapstrl;

typedef unordered_set<ll, custom_hash> uset;

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

void read_array(vl& arr, int n) {
    rep(i, 0, n - 1) {
        cin >> arr[i];
    }
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vec<T>& v) {
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

int stoi(char ch) {
    str mystr(1, ch);
    int num = stoi(mystr);
    return num;
}

string str_slice(const str& s, int start, int end) {
    return s.substr(start, end - start);
}


// Numpy

template<typename T>
class ndarray {
public:
    int n_rows; // number of rows
    int n_cols; // number of columns
    vec<T> data; // vector to store the data

    // Constructor to initialize the 2D array with given shape
    ndarray(int n_rows_, int n_cols_) : n_rows(n_rows_), n_cols(n_cols_) {
        data = vec<T>(n_rows * n_cols);
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
    vec<T> get_data() const {
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
        for (int i = istart; i < iend; i++)
        {
            for (int j = jstart; j < jend; j++)
            {
                (*this)(i, j) = value;
            }
        }
    }

    vec<T> get_row(int row, int cstart=0, int cend=-1) {
        if (cend == -1) {
            cend = n_cols;
        }
        vec<T> ret(cend - cstart);
        rep(i, cstart, cend - 1) {
            ret[i - cstart] = (*this)(row, i);
        }
        return ret;
    }

    vec<T> get_col(int col, int rstart=0, int rend=-1) {
        if (rend == -1) {
            rend = n_rows;
        }
        vec<T> ret(rend - rstart);
        rep(i, rstart, rend - 1) {
            ret[i - rstart] = (*this)(i, col);
        }
        return ret;
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
        if (i != arr.get_n_rows() - 1) {
            os << std::endl;
        }
    }
    return os;
}

template <typename T>
void mset_del(multiset<T>& ss, T x) {
    ss.erase(ss.find(x));
}

template <typename T>
void mset_move(multiset<T>& ss1, multiset<T>& ss2, T x) {
    auto ptr = ss1.find(x);
    ss1.erase(ptr);
    ss2.insert(x);
}

template <typename T>
T min(multiset<T>& ss) {
    return *(ss.begin());
}

template <typename T>
T max(multiset<T>& ss) {
    return *(ss.rbegin());
}

typedef ndarray<ll> llarray;
typedef ndarray<int> intarray;
typedef multiset<ll> msetl;

void solve() {
    ll n, k; cin >> n >> k;
    vl a(n);
    read_array(a, n);

    msetl left_in, left_out;    

    vl b(a);
    b.sort();
    msetl right_in(b.begin(), b.begin() + k);
    msetl right_out(b.begin() + k, b.end());

    ll left_sum = 0;
    ll right_sum = b.slice(0, k).sum();

    ll best = right_sum;

    dprint("i=", -1, "best", best, "partition", left_in.size(), right_in.size());
    rep(i, 0, n - 1) {
        // Move a[i] from the right to the left
        if (!right_out.count(a[i])) {
            mset_move(right_in, left_out, a[i]);

            ll smallest_left = min(left_out);
            mset_move(left_out, left_in, smallest_left);
            left_sum += smallest_left;
            right_sum -= a[i];

            ll local_score = max(right_sum, left_sum);

            if (right_out.size()) {
                ll largest_left = max(left_in);
                ll smallest_right_out = min(right_out);
                if (local_score > max(right_sum + smallest_right_out, left_sum - largest_left)) {
                    local_score = max(right_sum + smallest_right_out, left_sum - largest_left);
                    mset_move(left_in, left_out, largest_left);
                    mset_move(right_out, right_in, smallest_right_out);
                    left_sum -= largest_left;
                    right_sum += smallest_right_out;
                }
            }
            dprint("left_in", left_in, "right_in", right_in);

            best = min(best, local_score);
        }
        else {
            mset_del(right_out, a[i]);
            left_out.insert(a[i]);

            if (left_in.size() && *left_out.begin() < *left_in.rbegin()) {
                ll x1, x2;
                x1 = min(left_out);
                x2 = max(left_in);

                mset_move(left_out, left_in, x1);
                mset_move(left_in, left_out, x2);
                left_sum = left_sum - x2 + x1;
            }

            ll local_score = max(left_sum, right_sum);

            // Is it worth doing x + 1?
            if (right_in.size()) {
                ll largest_right = *right_in.rbegin();
                ll smallest_left = *left_out.begin();

                if (local_score > max(left_sum + smallest_left, right_sum - largest_right)) {
                    local_score = max(left_sum + smallest_left, right_sum - largest_right);

                    mset_del(right_in, largest_right);
                    right_out.insert(largest_right);
                    mset_del(left_out, smallest_left);
                    left_in.insert(smallest_left);

                    left_sum += smallest_left;
                    right_sum -= largest_right;
                }
            }

            best = min(best, local_score);
        }

        dprint("i=", i, "best", best, "partition", left_in.size(), right_in.size());
    }

    print(best);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) {
        solve();
    }
    return 0;
}