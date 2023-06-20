// #include<lib/nt.h>
// #include<lib/sparsetable.h>
// #include<lib/common.h>

const ll MX = 4256233;

void solve() {
    ll n; cin >> n;
    vl a(n);
    inp::array(a, n);

    vl right = vv::arange(0LL, n - 1);

    SparseTable st(a, [](ll x, ll y) -> ll { 
        if (x >= MX || y >= MX) return MX;
        return lcm(x, y);
    });

    map<ll, vl> lefts;
    rep(i, 0, n - 1) {
        lefts[a[i]].pb(i);
    }

    ll x = 1;
    while (true) {
        if (lefts.empty()) {
            print(x);
            return;
        }

        auto it = lefts.begin();
        ll m = it->first;
        if (m != x) {
            print(x);
            return;
        }

        vl& candidates = it->second;
        vv::sort(candidates);

        foreach(c, candidates) {
            ll r = smallest_st(i, st.query(c, i) > m, right[c] + 1, n - 1);
            if (r == n) {
                break;
            }
            ll new_m = st.query(c, r);
            if (new_m >= MX) {
                continue;
            }

            lefts[new_m].pb(c);
            right[c] = r;
        }

        lefts.erase(m);
        x++;
    }
}


int main() {
    init();
    int t; cin >> t;
    cep(t) {
        solve();
    }
    return 0;
}