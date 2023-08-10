#include <bits/stdc++.h>
using namespace std;
//  Definition of the macro.
// ass (a, b, x, y) is equivalent to a = x; b = y;
#define ass(a, b, x, y) (tie(a, b) = make_tuple(x, y));
// if x, y, z are ordered non-descendingly
#define ordered(x, y, z) ((x) <= (y) && (y) <= (z))
// updates lhs to be the minimum of lhs and rhs
template <typename T, typename S>
void chkmin(T& lhs, S rhs)
{
    lhs = min(lhs, T(rhs));
}
// updates lhs to be the maximum of lhs and rhs
template <typename T, typename S>
void chkmax(T& lhs, S rhs)
{
    lhs = max(lhs, T(rhs));
}
// returns a signed value for the size of a container
template <typename T>
inline int len(const T& v)
{
    return int(v.size());
}
#define to_str to_string
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()
typedef long long ll;
// Looping
#define rep(i, d, u) for (ll i = (d); i < (u); ++i)
#define repi(i, d, u) for (ll i = (d); i <= (u); ++i)
#define dep(i, u, d) for (ll i = (u); i >= (d); --i)
#define irep(i, d, u) for (i = (d); i < (u); ++i)
#define idep(i, u, d) for (i = (u); i >= (d); --i)
#define srep(i, d, u, s) for (ll i = (d); i < (u); i += s)
#define cep(t) while (t--)
#define cepsolve        \
    int main()          \
    {                   \
        init();         \
        ll t;           \
        cin >> t;       \
        cep(t) solve(); \
    }
#define CEPEAT_CAT_(a, b) a##b
#define CEPEAT_CAT(a, b) CEPEAT_CAT_(a, b)
#define cepeat(t) rep(CEPEAT_CAT(CEPEAT_COPY, __COUNTER__), 0, t)
#define foreach(i, c) for (auto& i : c)
#define foreachp(k, v, c) for (auto& [k, v] : c)
// Looping through a container
#define walk(i, container) for (ll i = 0; i < len(container); ++i)
#define reverse_walk(i, container) for (ll i = len(container) - 1; i >= 0; --i)
#define iter_walk(i, container) for (auto i = container.begin(); i != container.end(); i++)
struct custom_hash {
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t do_hash(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(uint64_t x) const
    {
        return do_hash(x);
    }
    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2>& key) const
    {
        return (*this)(((*this)(key.first) * 37) ^ (*this)(key.second));
    }
    size_t operator()(string s) const
    {
        uint64_t out = 0;
        for (int i = 0; i < len(s); i++) {
            out = out * 37 + s[i];
        }
        return do_hash(out);
    }
};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng)
template <typename T>
struct Identity {
    constexpr const T& operator()(const T& value) const
    {
        return value;
    }
};
typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef vector<vector<ll>> vvl;
typedef vector<string> vstr;
typedef vector<vector<string>> vvstr;
typedef vector<char> vc;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef pair<ll, ll> pl;
typedef vector<vector<pl>> vvpl;
typedef vector<pl> vpl;
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
umapll operator+(const umapll& lhs, const umapll& rhs)
{
    umapll result = lhs;
    for (const auto& pair : rhs) {
        result[pair.first] += pair.second;
    }
    return result;
}
template <typename Key, typename Value>
Value mget(const std::unordered_map<Key, Value, custom_hash>& map, const Key& key)
{
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    return Value {}; // Default-constructed value
}
template <typename K, typename V>
void initmap(umap<K, V>& counts)
{
    counts.reserve(250000);
    counts.max_load_factor(0.25);
}
// List manipulation
typedef priority_queue<ll, vl, greater<ll>> minheap;
typedef priority_queue<ll, vl, less<ll>> maxheap;
#define RC(expr, x, lo, hi) ({                                \
    ll x;                                                     \
    using RC_t = std::remove_reference<decltype(expr)>::type; \
    vector<RC_t> lcret;                                       \
    irep(x, lo, hi)                                           \
    {                                                         \
        lcret.push_back(expr);                                \
    }                                                         \
    lcret;                                                    \
})
#define LC(expr, x, arr) ({                                               \
    using LCx_t = std::remove_reference<decltype(arr)>::type::value_type; \
    LCx_t x;                                                              \
    using LCexpr_t = std::remove_reference<decltype(expr)>::type;         \
    vector<LCexpr_t> lcret;                                               \
    foreach (LC_i, arr) {                                                 \
        x = LC_i; /*Using LC_i and then x = LC_i pacifies -Wshadow*/      \
        lcret.push_back(expr);                                            \
    }                                                                     \
    lcret;                                                                \
})
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
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
// Printing
void init()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
}
template <typename T>
void print(const T& t)
{
#ifdef INTERACTIVE
    std::cout << t << std::endl;
#else
    std::cout << t << "\n";
#endif
}
template <typename T, typename... Args>
void print(const T& t, const Args&... args)
{
    std::cout << t << " ";
    print(args...);
}
template <typename T>
void dprint(const T& t)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    std::cout << t << std::endl;
#endif
#endif
}
template <typename T, typename... Args>
void dprint(const T& t, const Args&... args)
{
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
int recur_depth = 0;
#define dbg(x)                                                                                                 \
    {                                                                                                          \
        ++recur_depth;                                                                                         \
        auto x_ = x;                                                                                           \
        --recur_depth;                                                                                         \
        cout << string(recur_depth, '\t') << __func__ << ":" << __LINE__ << "\t" << #x << " = " << x_ << endl; \
    }
#else
#define dbg(x)
#endif
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const unordered_map<K, V, custom_hash>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const map<K, V>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << *it;
        if (it != v.end() - 1) {
            os << " ";
        }
    }
    return os;
}
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
{
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s)
{
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T, custom_hash>& s)
{
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& mp)
{
    os << "{ ";
    for (const auto& p : mp) {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}
template <typename T>
istream& operator>>(istream& input, vector<T>& vec)
{
    for (auto& element : vec) {
        input >> element;
    }
    return input;
}
template <typename S, typename T>
istream& operator>>(istream& input, pair<S, T>& p)
{
    input >> p.first >> p.second;
    return input;
}

namespace graph {
// Specify target to stop Dijkstra once target is processed (does not process
// target's neighbors)
void dijkstra(const vvpl& graph, vl& dist, ll start, ll target = -1LL)
{
    rep(i, 0, len(dist))
    {
        dist[i] = LONG_LONG_MAX;
    }
    set<pl> pq;

    pq.insert({ 0, start });
    dist[start] = 0;
    while (!pq.empty()) {
        auto [distance, node] = *(pq.begin());
        pq.erase({ distance, node });

        if (node == target) {
            break;
        }

        foreachp(child, edge, graph[node])
        {
            if (distance + edge < dist[child]) {
                pq.erase({ dist[child], child });
                pq.insert({ distance + edge, child });
                dist[child] = distance + edge;
            }
        }
    }
}
// Returns weight of minimum/maximum spanning tree, and stores the tree in edges
// Use seed to specify a starting point from which to run Prim's.

ll prim(const vvpl& graph, vpl& edges, bool minimum = true, ll seed = 0LL)
{
    set<tuple<ll, ll, ll>> heap;
    auto heap_top = [&]() {
        if (minimum)
            return *(heap.begin());
        else
            return *(heap.rbegin());
    };
    auto heap_pop = [&]() {
        if (minimum)
            heap.erase(*(heap.begin()));
        else
            heap.erase(*(heap.rbegin()));
    };
    ll n = len(graph);
    vb in_tree(n, false);
    ll total_weight = 0;

    // initialize the tree
    in_tree[seed] = true;
    foreachp(neighbor, weight, graph[seed])
    {
        heap.insert({ weight, seed, neighbor });
    }

    while (!heap.empty()) {
        // ignore top of the heap if the endpoint is already included
        if (in_tree[get<2>(heap_top())]) {
            heap_pop();
            continue;
        }
        auto edge = heap_top();
        // add endpoint to tree
        in_tree[get<2>(edge)] = true;
        total_weight += get<0>(edge);
        edges.pb({ get<1>(edge), get<0>(edge) });

        // look through neighbors of endpoint and add them to the heap
        foreachp(neighbor, weight, graph[get<2>(edge)])
        {
            if (!in_tree[neighbor])
                heap.insert({ weight, get<2>(edge), neighbor });
        }
    }
    return total_weight;
}

// Returns a topological sort order of a dag
// If dag is not actually a dag, this will return a vl that is shorter than dag
vl topo_sort(const vvl& dag)
{
    ll n = len(dag);
    vl order;
    vb DFS_processed(n, false);
    vb DFS_processing(n, false);
    bool found_cycle = false;
    function<void(ll)> DFS = [&](ll node) -> void {
        if (found_cycle)
            return;
        if (DFS_processed[node])
            return;
        DFS_processing[node] = true;
        foreach (child, dag[node]) {
            if (DFS_processing[child]) {
                // found cycle!
                dprint("Potential error: topo_sort found a cycle in graph");
                found_cycle = true;
                return;
            }
            if (!DFS_processed[child]) {
                DFS(child);
            }
        }
        DFS_processed[node] = true;
        DFS_processing[node] = false;
        order.pb(node);
    };
    rep(i, 0, n)
    {
        DFS(i);
    }
    reverse(order.begin(), order.end());
    return order;
}
}

class Solution {
public:
    vi findOrder(int numCourses, vvi& prerequisites)
    {
        vvl adj(numCourses);
        foreach (req, prerequisites) {
            adj[req[1]].pb(req[0]);
        }
        auto g = graph::topo_sort(adj);
        if (len(g) < len(adj))
            return {};
        else
            return LC(int(x), x, g);
    }
};

int main()
{
    vvi prereqs = { { 1, 0 }, { 2, 1 }, { 0, 2 } };
    int n = len(prereqs);
    Solution sol;
    print(sol.findOrder(n, prereqs));
}