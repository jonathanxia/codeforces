#pragma once
#include <lib/common.h>

namespace graph {
bool TOPO_SORT_THROWAWAY_BOOL;
usetl TOPO_SORT_THROWAWAY_USETL;
// Returns a topological sort order of a dag
// If dag is not actually a dag, this will return a vl that is shorter than dag
inline vl topo_sort(const vvl& dag, bool& has_cycle = TOPO_SORT_THROWAWAY_BOOL, const usetl& exclude = TOPO_SORT_THROWAWAY_USETL)
{
    vl indeg(len(dag)), ret;
    for (int i = 0; i < len(dag); i++) {
        if (exclude.count(i))
            continue;
        auto& li = dag[i];
        for (int x : li)
            if (!exclude.count(x))
                indeg[x]++;
    }
    queue<int> q; // use priority_queue for lexic. largest ans.
    rep(i, 0, len(dag)) if (!exclude.count(i) && indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int i = q.front(); // top() for priority queue
        ret.push_back(i);
        q.pop();
        for (int x : dag[i])
            if (!exclude.count(x) && --indeg[x] == 0)
                q.push(x);
    }
    has_cycle = len(ret) < len(dag) - len(exclude);
    return ret;
}
} // namespace graph