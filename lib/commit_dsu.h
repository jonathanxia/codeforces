#include <lib/common.h>
#include <lib/persistent.h>

struct DSU
{
    PersistentVector parent;
    PersistentVector rank;
    PersistentVector largest;
    PersistentVector smallest;
    PersistentVector sz;

    DSU(int size) : parent(size), rank(size), largest(size), smallest(size), sz(size)
    {
        for (int i = 0; i < size; ++i)
        {
            parent.set(i, i);
            rank.set(i, 0);
            largest.set(i, i);
            smallest.set(i, i);
            sz.set(i, 1);
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent.set(x, find(parent[x])); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
            {
                parent.set(rootX, rootY);

                largest.set(rootY, max(largest[rootY], largest[rootX]));
                smallest.set(rootY, min(smallest[rootY], smallest[rootX]));
                sz.set(rootY, sz[rootY] + sz[rootX]);
            }
            else if (rank[rootX] > rank[rootY])
            {
                parent.set(rootY, rootX);

                largest.set(rootX, max(largest[rootX], largest[rootY]));
                smallest.set(rootX, min(smallest[rootX], smallest[rootY]));
                sz.set(rootX, sz[rootX] + sz[rootY]);
            }
            else
            {
                parent.set(rootY, rootX);
                rank.set(rootX, rank[rootX] + 1);

                largest.set(rootX, max(largest[rootX], largest[rootY]));
                smallest.set(rootX, min(smallest[rootX], smallest[rootY]));
                sz.set(rootX, sz[rootX] + sz[rootY]);
            }
        }
    }

    void commit()
    {
        parent.commit();
        rank.commit();
    }

    void revert()
    {
        parent.revert();
        rank.revert();
    }
};