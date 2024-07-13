// Link: https://atcoder.jp/contests/abc362/tasks/abc362_f

// Warning: This is a constructive problem, so we sort the output
// in a weird way to get the autograder to pass
#include<lib/tree/dfs_tree.h>
#include<lib/mset.h>
#include<lib/common.h>
#include <lib/vv/sort.h>
#include <lib/tree/centroid.h>

void solve() {
    ll n; cin >> n;
    vvpl graph(n);
    inp::read_tree(graph);
    vi centroids = tree::getCentroids(graph);

    ll centroid = centroids[0];
    DfsTree tree(graph, centroid);

    // Just create sets
    vector<set<ll>> bags;
    set<pl> sizes;
    foreachp(child, weight, graph[centroid]) {
        bags.push_back(set<ll>());
        function<void(ll, ll)> ff = [&](ll node, ll parent) {
            bags.back().insert(node);
            foreachp(c, w, graph[node]) {
                if (c == parent) continue;
                ff(c, node);
            }
        };
        ff(child, centroid);
        sizes.insert({bags.back().size(), len(bags) - 1});
    }
    // Add the centroid to the smallest bag
    if (n % 2 == 0) {
        pl res = mset::min(sizes);
        sizes.erase(res);
        bags[res.second].insert(centroid);
        sizes.insert({res.first + 1, res.second});
    }

    // Now do the pairing algorithm
    vpl output;
    FOR(i, 0, n / 2 - 1) {
        pl res0 = mset::max(sizes);
        sizes.erase(res0);
        pl res1 = mset::max(sizes);
        sizes.erase(res1);
        ll u = mset::popmin(bags[res0.second]);
        ll v = mset::popmin(bags[res1.second]);
        if (u > v) swap(u, v);
        output.push_back({u + 1, v + 1});
        sizes.insert({res0.first - 1, res0.second});
        sizes.insert({res1.first - 1, res1.second});
    }
    vv::rsort(output);
    foreach(p, output) print(p.first, p.second);
}

int main() {
    init();
    solve();
    return 0;
}