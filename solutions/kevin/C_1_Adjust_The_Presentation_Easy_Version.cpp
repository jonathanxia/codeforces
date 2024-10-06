// Link: https://codeforces.com/contest/2021/problem/C1

#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/vv/unique.h>

void solve()
{
    ll n, m, q;
    cin >> n >> m >> q;
    vl a(n);
    vl b(m);
    cin >> a >> b;
    usetl nums;
    vl b_dedupe = vv::stable_unique(b);

    walk(i, b_dedupe)
    {
        if (b_dedupe[i] != a[i]) {
            print("TIDAK");
            return;
        }
    }
    print("YA");
}

int main()
{
    init();
    int t;
    cin >> t;
    cep(t) solve();
    return 0;
}