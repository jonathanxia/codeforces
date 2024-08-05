// Link: https://codeforces.com/contest/1993/problem/F2
#include<lib/common.h>
#include<lib/nt/crt.h>

ll dirx(char ch) {
    if (ch == 'D') return 0;
    if (ch == 'U') return 0;
    if (ch == 'L') return -1;
    if (ch == 'R') return 1;
    return 0;
}

ll diry(char ch) {
    if (ch == 'D') return -1;
    if (ch == 'U') return 1;
    if (ch == 'L') return 0;
    if (ch == 'R') return 0;
    return 0;
}

void solve() {
    ll n, k, w, h; cin >> n >> k >> w >> h;
    string s; cin >> s;
    ll tx = 0; ll ty = 0;
    FOR(i, 0, n - 1) {
        tx += dirx(s[i]);
        ty += diry(s[i]);
        chkmod(tx, 2 * w);
        chkmod(ty, 2 * h);
    }

    ll ans = 0;
    ll x = 0, y = 0;
    FOR(i, 0, n - 1) {
        x += dirx(s[i]);
        y += diry(s[i]);
        chkmod(x, 2 * w);
        chkmod(y, 2 * h);

        // calculate t * tx = -x (mod 2w)
        vector<pl> congs;
        congs.push_back(nt::solve_linear(tx, -x, 2 * w));
        congs.push_back(nt::solve_linear(ty, -y, 2 * h));
        if (exists_st(j, congs[j].second < 0, 0, len(congs) - 1)) {
            continue;
        }

        pl res = nt::crt(congs);
        if (res.second == -1) {
            continue;
        }

        // 0 <= t <= k - 1
        ans += (k - 1 + (res.second - res.first)) / res.second;
    }
    print(ans);
}

int main() {
    init();
    int t; cin >> t;
    cep(t) solve();

    // Add some extra unit tests for crt here
    pl res = nt::crt({{0LL, 6LL}, {2LL, 4LL}});
    assert(res.first == 6 && res.second == 12);

    res = nt::crt({{3, 4}, {2, 12}});
    assert(res == mp(-1, -1));
    return 0;
}