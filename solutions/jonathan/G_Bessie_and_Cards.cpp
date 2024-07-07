// Link: https://codeforces.com/contest/1942/problem/G
#include <lib/constants/mod998244353.h>
#include<lib/mod_int.h>
#include<lib/nt.h>

void solve() {
    ll a, b, c; cin >> a >> b >> c;
    a += 5;
    ll n = a + c;
    // Let T be the stopping time of when the random walk hits -5
    // n_good - n_bad = -5
    // n_good + n_bad = T
    // n_bad = (T + 5) / 2 so T is odd
    // (n_bad choose 5) / (a choose 5)
    // So we calculate the probability that T > t
    vMI distro(n + 3);
    using combo::choose;
    MI denom = combo::choose(n, a);
    DOR(t, n, 5) {
        // prob that you get to -5 at t moves
        // and stay above -4 the whole time before that
        if (t % 2 != 1) continue;
        ll n_good = (t - 5) / 2;
        ll n_bad = (t + 5) / 2;
        if (n_good > c) continue;
        if (n_bad > a) continue;
        MI num_after = combo::choose(n - t, a - n_bad);
        MI num_before = MI(choose(t, n_bad)) - 2 * MI(choose(t - 1, n_bad));

        distro[t] = num_before * num_after / denom;
    }
    // dbg(LC(f.as_frac(), f, distro));
    MI ans = 0;
    FOR(t, 5, n) if (t % 2 == 1) {
        ll n_bad = (t + 5) / 2;
        ans += distro[t] * choose(n_bad, 5) / choose(a, 5);
    }
    // Alright now we deal with the possibility of n
    // if t = n this means that we go to the end but we cannot go below -5
    if (c - a <= -5)
    {
        print(ans);
        // dprint("Expected", MI(903173463).as_frac(), "Got:", ans.as_frac());
        return;
    }
    // Now we know that the c - a > -5
    ans += (1 - MI(choose(n, c + 5)) / choose(n, c));
    print(ans);

}

int main() {
    init();
    combo::precompute_fac(1000000);
    int t; cin >> t;
    cep(t) solve();
    return 0;
}