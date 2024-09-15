// Link: https://codeforces.com/contest/2005/problem/E2
#include<lib/common.h>
#include<lib/ndarray.h>
#include<lib/algo/pareto_front.h>


map<ll, vpl> compress(const map<ll, vpl>& d) {
    map<ll, vpl> data;
    for (auto& p : d) {
        data[p.first] = pareto_front(p.second);
    }
    return data;
}

void solve() {
    ll l, n, m; cin >> l >> n >> m;
    vl a(l); cin >> a;
    // if (l == 1500 && n == 1500 && m == 1500 && a[0] == 11496 && a[1] == 610579 && a[2] == 884393) {
    //     SHOULD_PRINT = true;
    // }
    ndarray<ll, 2> b({n, m}, -1); cin >> b;

    set<ll> a_set(ALL(a));
    map<ll, vpl> value_to_locs;
    // 3 million constructions = 300 constant factor
    FOR(i, 0, n - 1) FOR(j, 0, m - 1) if (a_set.count(b(i, j))) value_to_locs[b(i, j)].push_back({i, j});
    value_to_locs = compress(value_to_locs);

    vpl pareto = {{n + 1, -1}};
    auto is_winning = [&](ll x, ll y) {
        ll j = smallest_st(idx, pareto[idx].first >= x, 0, len(pareto) - 1);
        if (y <= pareto[j].second) return true;
        return false;
    };

    // Setup the pareto front
    DOR(idx, l - 1, 0) {
        vpl new_pareto = {{n + 1, -1}};

        // value_to_locs[a[idx]] -> <= n things
        // runtime n * l
        foreach(p, value_to_locs[a[idx]]) if (!is_winning(p.first + 1, p.second + 1)) {
            new_pareto.push_back(p);
        }
        pareto = pareto_front(new_pareto);
    }

    if (is_winning(0, 0)) {
        print("T");
    }
    else {
        print("N");
    }
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}