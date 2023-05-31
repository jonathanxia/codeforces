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


// Begin actual code --------------------


vvi graph(pow(10, 5) * 2);
vi depth(pow(10, 5) * 2);
vi parent(pow(10, 5) * 2);
vb visited(pow(10, 5) * 2);

void dfs(int node) {
    visited[node] = true;
    depth[node] = 1;
    for (auto child : graph[node]) {
        if (!visited[child]) {
            parent[child] = node;
            dfs(child);
            depth[node] += depth[child];
        }
    }
}

vl choosek(pow(10, 5) * 2 + 1);

ll solve(ll k, ll n) {
    if (k % 2 == 1) {
        return 1;
    }

    k = k / 2;

    // Collect depths and parents
    dfs(0);

    // Calculate combinations
    rep(i, 0, k - 1) {
        choosek[i] = 0;
    }
    choosek[k] = 1;
    rep(i, k + 1, n + 2) {
        choosek[i] = mdiv(choosek[i - 1] * i, i - k);
    }

    ll choose2k = 1;
    rep(i, 0, 2 * k - 1) {
        choose2k = mdiv(choose2k * (n - i), 2 * k - i);
    }

    // Calculate expected values
    ll exp = 0;

    // print(vslice(depth, 0, n));
    // Iterate over edges now
    rep(u, 0, n - 1) {
        for (auto v : graph[u]) {
            if (v > u) {
                continue;
            }
            // Now we know that u < v

            int left, right;
            if (parent[v] == u) {
                left = depth[v];
                right = n - depth[v];
            }
            else {
                left = depth[u];
                right = n - depth[u];
            }

            // print("u, v =", u, v, left, right);
            exp += choosek[left] * choosek[right];
            exp = mod(exp);
        }
    }

    // print(vslice(graph, 0, n));

    return mod(1 + mdiv(exp, choose2k));
}


int main() {
    ll k, n;

    cin >> n >> k;
    rep(i, 0, n - 2) {
        ll u, v;
        cin >> u >> v;

        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    cout << solve(k, n) << endl;

    return 0;
}