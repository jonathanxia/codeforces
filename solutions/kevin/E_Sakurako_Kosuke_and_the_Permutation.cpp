// Link: https://codeforces.com/contest/2033/problem/E

#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/graph/functional_graph.h>

void solve()
{
    ll n;
    cin >> n;
    vl p(n);
    cin >> p;
    // foreach (p_, p)
    //     p_--;
    vb in_cycle(n);
    vb in_chain(n);
    auto cycles = graph::cycles(p, in_cycle, in_chain, true);
    ll sum = 0;
    foreach (cycle, cycles) {
        sum += (len(cycle) - 1) / 2;
    }
    print(sum);
}

int main()
{
    init();
    int t;
    cin >> t;
    cep(t) solve();
    return 0;
}