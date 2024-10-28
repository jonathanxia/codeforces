// Link: https://open.kattis.com/problems/braaaains

#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/graph/dijkstra.h>
#include<lib/algo/chicken_mcnugget.h>

void solve()
{
    ll n;
    cin >> n;
    ll m;
    cin >> m;
    vl s(n);
    cin >> s;
    vl b(m);
    cin >> b;
    sort(ALL(s));

    Chicken_McNugget cmn(s);

    vl ans;
    foreach (query, b) {
        ans.pb(cmn.query(query));
    }
    print(ans);
}

int main()
{
    init();
    solve();
    return 0;
}