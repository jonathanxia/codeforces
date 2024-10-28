// Link: https://open.kattis.com/problems/villagertrading

#include<lib/macros.h>
#include<lib/print.h>
#include<lib/inp.h>
#include<lib/common.h>
#include<lib/graph/bellman_ford.h>

void solve()
{
    ll n;
    cin >> n;
    umap<string, ll> name_to_node;
    name_to_node["Emerald"] = 0;
    ll node_num = 1;
    auto get_num = [&](string item_name) {
        if (!name_to_node.count(item_name)) {
            name_to_node[item_name] = node_num;
            node_num++;
        }
        return name_to_node[item_name];
    };
    vector<vector<pair<ll, long double>>> adj(10000);
    cepeat(n)
    {
        ll num_trades;
        cin >> num_trades;
        cepeat(num_trades)
        {
            ll u, v;
            string item1, item2;
            cin >> u >> item1 >> v >> item2;
            adj[get_num(item2)].pb({ get_num(item1), logl(u) - logl(v) });
        }
    }
    BellmanFord bf(adj, 0);
    if (bf.has_negative_cycle) {
        print("yes");
    } else {
        print("no");
    }
}

int main()
{
    init();
    solve();
    return 0;
}