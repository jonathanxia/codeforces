// Link: https://codeforces.com/contest/2044/problem/H
#include<lib/common.h>
#include<lib/cum2d.h>

void solve() {
    ll n, q; cin >> n >> q;

    vvl data(n, vl(n)); cin >> data;
    CumSum2d<ll> cs_0(data);
    vvl datai(n, vl(n));
    vvl dataj(n, vl(n));
    FOR(i, 0, n - 1) FOR(j, 0, n - 1) datai[i][j] = data[i][j] * i;
    FOR(i, 0, n - 1) FOR(j, 0, n - 1) dataj[i][j] = data[i][j] * j;

    CumSum2d<ll> cs_i(datai);
    CumSum2d<ll> cs_j(dataj);

    vl output;
    cepeat(q) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        ll L = y2 - y1 + 1;
        /*
        We want to compute
        sum a[i][j] * ( (i - x1) * L + j - y1  + 1)
        = a[i][j] * i * L + a[i][j] * j - a[i][j] * (x1 * L + y1 - 1)
        */
       ll ans = cs_i.query(x1, x2, y1, y2) * L;
       ans += cs_j.query(x1, x2, y1, y2);
       ans -= cs_0.query(x1, x2, y1, y2) * (x1 * L + y1 - 1);
       output.pb(ans);
    }
    print(output);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();
    return 0;
}