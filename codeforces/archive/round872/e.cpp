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

// Actual code

vl a(pow(10, 5) + 5);
vvl graph(pow(10, 5) + 5);

vl best_score(pow(10, 5) + 5);
set<ll> achieved[100055];

// Map from node to achieve idx
int node_to_achieve_idx[100055];
int ptr = 0;

vb visited(pow(10, 5) + 5);


void dfs(int node, ll prefix_sum) {
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
        // allocate
        node_to_achieve_idx[node] = ptr++;
        achieved[node_to_achieve_idx[node]].insert(prefix_sum ^ a[node]);
        best_score[node] = 0;
        return;
    }


    unordered_map<ll, int> counts;

    int num_child = 0;
    ll child_best_score = 0;

    vi children;
    for (auto child : graph[node]) {
        if (visited[child]) {
            continue;
        }

        dfs(child, prefix_sum ^ a[node]);
        num_child += 1;
        child_best_score += best_score[child];
        children.push_back(child);

        // achieved[child].clear(); // Free up memory
    }

    // Check for a collision against the largest subtree
    sort_vec(children, [](int c) { return -achieved[node_to_achieve_idx[c]].size(); });

    vi tmpchild;
    for (auto child: children) {
        tmpchild.push_back(child);
    }
    // print("Exploring node", node, "children", tmpchild);
    // for (auto child : children) {
    //     print("\t", child, ":", achieved[node_to_achieve_idx[child]], "best_score:", best_score[child]);
    // }

    bool collision = false;
    set<ll>& s0 = achieved[node_to_achieve_idx[children[0]]];
    rep(i, 1, children.size() - 1) {
        set<ll>& s = achieved[node_to_achieve_idx[children[i]]];
        for (ll value : vl(s.begin(), s.end())) {
            if (s0.count(value)) {
                collision = true;
                // GET OUT GET OUT DO NOT MERGE!!!
                break;
            }
            // Just insert directly
            s0.insert(value);
            // print("Erasing", value, "from set", s);
            s.erase(value);
        }

        if (collision) {
            // GET OUT! DO NOT MERGE!!!
            break;
        }
    }

    if (!collision) {
        // Already merged, just go
        // Make a "copy" by moving the pointer
        node_to_achieve_idx[node] = node_to_achieve_idx[children[0]];
        best_score[node] = num_child - 1 + child_best_score;
        return;
    }

    // What to do if there is a collision.
    for (auto child : children) {
        for (auto value: achieved[node_to_achieve_idx[child]]) {
            counts[value] += 1;
        }
    }

    // We have collected what is possible from our children.
    // We must now state what is possible for us.
    // Get the thing that shows up the most
    ll max_freq = 0;
    for (auto value : counts) {
        max_freq = max(value.second, max_freq);
    }

    best_score[node] = (num_child - max_freq) + child_best_score;
    // print("counts=", counts);
    // print("best_score[", node, "]", best_score[node]);

    // Allocate a new set for me
    node_to_achieve_idx[node] = ptr++;

    for (auto value : counts) {
        if (max_freq != value.second) {
            continue;
        }

        ll new_value = value.first;
        
        achieved[node_to_achieve_idx[node]].insert(new_value);
    }
}

ll solve(int n) {
    dfs(0, 0);

    return contains(achieved[node_to_achieve_idx[0]], 0) ? best_score[0] : best_score[0] + 1;
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

    // auto g = vslice(graph, 0, n);
    // auto atmp = vslice(a, 0, n);
    // display_tree(0, -1, g, atmp);

    print(solve(n));

    // if (n == 100000) {
    //     int i = 0;
    //     print(i, achieved[node_to_achieve_idx[i]], best_score[i]);
    //     for (int i : graph[0]) {
    //         print(i, achieved[node_to_achieve_idx[i]], best_score[i]);
    //     }
    // }
}