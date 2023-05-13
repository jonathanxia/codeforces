#include <bits/stdc++.h>
#include <sstream>

//  Definition of the macro.
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

using namespace std;

typedef long long ll;

typedef vector<vector<int>> vvi;
typedef vector<int> vi;

typedef vector<vector<ll>> vvl;
typedef vector<ll> vl;
typedef vector<bool> vb;

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

ll mdiv(ll x, ll y) {
    x = mod(x);
    y = mod(y);
    return mod(x * inv(y, M), M);
}


// Looping
#define rep(i, d, u) for(int i = d; i <= u; ++i)
#define dep(i, u, d) for(int i = u; i >= d; --i)

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

// Actual code

vl a(pow(10, 5));
vvl graph(pow(10, 5));

vl best_score(pow(10, 5));
vvl values(pow(10, 5));
vb visited(pow(10, 5));


void dfs(int node) {
    visited[node]  = true;

    // Check if I am leaf
    bool has_children = false;
    for (auto child: graph[node]) {
        if (visited[child]) {
            continue;
        }
        has_children = true;
    }

    if (!has_children) {
        values[node].push_back(a[node]);
        best_score[node] = 0;
        return;
    }


    unordered_map<ll, int> counts;

    int num_child = 0;
    ll child_best_score = 0;
    for (auto child : graph[node]) {
        if (visited[child]) {
            continue;
        }

        dfs(child);
        num_child += 1;
        child_best_score += best_score[child];
        
        for (auto value: values[child]) {
            counts[value] += 1;
        }

        values[child].clear(); // Free up memory
    }

    // We have collected what is possible from our children.
    // We must now state what is possible for us.
    // Get the thing that shows up the most
    ll max_freq = 0;
    for (auto value : counts) {
        max_freq = max(value.second, max_freq);
    }

    best_score[node] = (num_child - max_freq) + child_best_score;
    for (auto value : counts) {
        if (max_freq != value.second) {
            continue;
        }

        ll new_value = value.first ^ a[node];
        
        values[node].push_back(new_value);
    }
}

ll solve(int n) {
    dfs(0);

    return contains(values[0], 0) ? best_score[0] : best_score[0] + 1;
}

int main() {
    int n;
    cin >> n;
    
    rep(i, 0, n - 1) {
        cin >> a[i];
    }

    rep(i, 0, n - 2) {
        int u, v;
        cin >> u >> v;

        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    print(solve(n));
}