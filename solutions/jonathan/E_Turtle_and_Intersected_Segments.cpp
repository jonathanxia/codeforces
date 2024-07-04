// Link: https://codeforces.com/contest/1981/problem/E
#include<lib/common.h>
#include<lib/graph/prim.h>
#include<lib/inp.h>
#include<lib/macros.h>
#include<lib/print.h>
#include<lib/persistent.h>
#include<lib/commit_dsu.h>
#include <lib/vv/sort.h>

void solve() {
    ll n; cin >> n;
    vector<array3> intervals(n);
    FOR(i, 0, n - 1) cin >> intervals[i][1] >> intervals[i][2] >> intervals[i][0];

    vv::sort(intervals);

    DSU dsu(n);
    set<array4> viewing; // L R a idx
    viewing.insert({intervals[0][1], intervals[0][2], intervals[0][0], 0LL});

    // dbg(viewing);
    vvpl graph(n);

    FOR(i, 1, n - 1) {
        auto [a, L, R] = intervals[i];
        // Find all the intervals that will die
        const ll INF = ll(1e18);
        auto it = viewing.lower_bound({L, INF, INF, INF});
        if (it != viewing.begin()) {
            it--;
            if ((*it)[1] < L) it++;
        }
        vector<array4> to_process;

        while (it != viewing.end() && (*it)[0] <= R) {
            auto data = *it;
            if (data[0] < L) {
                viewing.insert({data[0], L - 1, data[2], data[3]});
            }
            if (data[1] > R) {
                viewing.insert({R + 1, data[1], data[2], data[3]});
            }
            to_process.push_back(data);
            it = viewing.find(data);
            it++;
        }
        // Now sort on a value
        vv::sort(to_process, 0, -1, [](array4 k) { return -k[2]; });
        foreach(data, to_process) {
            viewing.erase(data);
            graph[data[3]].push_back({i, abs(data[2] - a)});
            graph[i].push_back({data[3], abs(data[2] - a)});
            dsu.unite(i, data[3]);
        }

        viewing.insert({L, R, a, i});
        // dprint("Inserted", L, R, a, i);
        // dbg(viewing);
        // dbg(ans);
        // dprint("");
    }
    if (dsu.num_components.value() != 1) {
        print(-1); return;
    }
    vpl edges;
    ll ans = graph::prim(graph, edges);
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}