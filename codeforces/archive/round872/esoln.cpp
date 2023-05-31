#pragma GCC target("avx2,popcnt")
#include<bits/stdc++.h>
#include <sstream>
using namespace std;

//  Definition of the macro.
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

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

vector<int> a, cost, set_pool_idx;
vector<unordered_set<int>> set_pool;
vector<vector<int>> graph;

void dfs(int x, int ancestor_xor, int p) {
    // special handling for leaves
    // the root is zero b/c of zero indexing!
    if (x != 0 and graph[x].size() == 1) {
        set_pool.emplace_back();
        set_pool_idx[x] = set_pool.size() - 1;
        set_pool.back().insert(ancestor_xor ^ a[x]);
        cost[x] = 0;
        // DEBUG
        /*
        cout << "Handled Leaf (" << x << ")" << "\n";
        cout << "cost: " << cost[x] << "\n";
        cout << "set_pool_idx: " << set_pool_idx[x] << "\n";
        cout << "pool elements: " << set_pool[set_pool_idx[x]] << "\n";
        cout << "\n";
        */
        // 
        return;
    }

    // I'm not a leaf. My cost is going to be the sum of my childrens costs +
    // the # changes. The way to minimize # changes is to always use the most
    // frequent element. Note that it's too expensive to make new sets for
    // every node so we repurpose the largest child set.
    int largest_set_sz = -1;
    int largest_set_child_idx;
    for (int child_idx = 0; child_idx < (int)graph[x].size(); child_idx++) {
        int child = graph[x][child_idx];
        if (child == p) continue;
        dfs(child, ancestor_xor ^ a[x], x);
        int set_sz = set_pool[set_pool_idx[child]].size();
        if (set_sz > largest_set_sz) {
            largest_set_sz = set_sz;
            largest_set_child_idx = child_idx;
        }
    }
    int largest_set_child = graph[x][largest_set_child_idx];
    set_pool_idx[x] = set_pool_idx[largest_set_child];
    unordered_set<int>& new_set = set_pool[set_pool_idx[x]];

    // get frequency of every value (potentially missing some things which only occur once in largest_set_child)
    unordered_map<int, int> freq;
    for (int child_idx = 0; child_idx < (int)graph[x].size(); child_idx++) if (child_idx != largest_set_child_idx) {
        int child = graph[x][child_idx];
        if (child == p) continue;
        unordered_set<int>& child_set = set_pool[set_pool_idx[child]];
        for (int value : child_set) {
            freq[value]++;
        }
    }
    // this needs to be defaulted to 1, to account for what we get from the largest set (which might be our only set)
    int best_freq_cnt = 1;
    vector<int> best_freq_values;
    for (auto& [adj_val, cnt] : freq) {
        if (new_set.count(adj_val) > 0) {
            cnt++;
        }
        if (cnt > best_freq_cnt) {
            best_freq_cnt = cnt;
            best_freq_values.clear();
            best_freq_values.push_back(adj_val);
        } else if (cnt == best_freq_cnt) {
            best_freq_values.push_back(adj_val);
        } 
    }

    if (best_freq_cnt >= 2) {
        new_set = unordered_set<int>(best_freq_values.begin(), best_freq_values.end());
    } else {
        for (auto& [adj_val, _] : freq) {
            new_set.insert(adj_val);
        }
    }
    // This is tricky, we may or may not be the root (yuck!)
    cost[x] = (graph[x].size() - (x != 0)) - best_freq_cnt;
    for(int child : graph[x]) if (child != p) {
        cost[x] += cost[child];
    }

    // DEBUG
    /*
    cout << "Handled Interior Node (" << x << ")" << "\n";
    cout << "cost: " << cost[x] << "\n";
    cout << "set_pool_idx: " << set_pool_idx[x] << "\n";
    cout << "pool elements: " << set_pool[set_pool_idx[x]] << "\n";
    cout << "\n";
    */
    // 

}


void solve() {
    int n;
    cin >> n;

    a.resize(n);
    graph.resize(n);
    cost.resize(n);
    set_pool_idx.resize(n);

    for(int i=0; i<n; i++) {
		cin>>a[i];
	}

	bool flag = n == 100000 && a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1 && a[5] == 26267;
	unordered_map<ll, int> freq2;
	unordered_map<ll, int> freq3;
	unordered_map<ll, int> freq4;
    for(int j=0; j<n-1; j++) {
        int u, v;
        cin >> u >> v;
		if (u == 3) {
			freq3[a[v]]++;
		}
		if (u == 2) {
			freq2[a[v]]++;
		}
		if (u == 4) {
			freq4[a[v]]++;
		}
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
	if (flag) {

		bool all_one = true;
		for (auto& [k, v] : freq2) {
			if (v != 1) {
				all_one=false;
				print("k, v=", k, v);
			}
		}
		print("all_one2=", all_one);

		all_one = true;
		for (auto& [k, v] : freq3) {
			if (v != 1) {
				all_one=false;
				print("k, v=", k, v);
			}
		}
		print("all_one3=", all_one);

		all_one = true;
		for (auto& [k, v] : freq4) {
			if (v != 1) {
				all_one=false;
				print("k, v=", k, v);
			}
		}
		print("all_one4=", all_one);

		int overlap = 0;
		for (auto& [k, v] : freq2) {
			if (freq3.count(k)) {
				overlap++;
			}
		}
		print("Overlap freq2 and freq3:", overlap);

	}

    int root = 0;
    dfs(root, 0, -1);

    auto& root_set = set_pool[set_pool_idx[root]];
    bool zero_possible = false;
    for (auto value : root_set) {
        if (value == 0) {
            zero_possible = true;
        }
    }
    int ans = cost[root];
    if (!zero_possible) {
        // need one more operation to convert to zero 
        ans++;
    }
    cout << ans << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
}