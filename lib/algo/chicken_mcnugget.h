#include <lib/graph/dijkstra.h>

struct Chicken_McNugget {
    vl dists;
    Chicken_McNugget(const vl& sizes)
        : dists(sizes[0])
    {
        vvpl residues(sizes[0]);
        ll n = len(sizes);
        rep(i, 1, n)
        {
            rep(j, 0, sizes[0])
            {
                ll target = (j + sizes[i]) % sizes[0];
                residues[j].pb({ target, sizes[i] });
            }
        }
        graph::dijkstra(residues, dists, 0);
    }

    // returns whether the desired size is possible using sizes
    bool query(ll desired_size) const
    {
        return desired_size >= dists[desired_size % len(dists)];
    }
};
