#pragma once
#include <lib/common.h>
#include <lib/persistent.h>

struct DSU {
    PersistentVector<ll> parent;
    PersistentVector<ll> rank;
    PersistentVector<ll> largest;
    PersistentVector<ll> smallest;
    PersistentVector<ll> sz;
    PersistentValue<ll> num_components;

    DSU(int size, bool persist=false)
        : parent(size, persist)
        , rank(size, persist)
        , largest(size, persist)
        , smallest(size, persist)
        , sz(size, persist)
        , num_components(persist)
    {
        for (int i = 0; i < size; ++i) {
            parent.set(i, i);
            rank.set(i, 0);
            largest.set(i, i);
            smallest.set(i, i);
            sz.set(i, 1);
        }
        num_components.set(size);
    }

    int find(int x)
    {
        if (parent[x] != x) {
            parent.set(x, find(parent[x])); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            num_components.set(num_components.value() - 1);
            if (rank[rootX] < rank[rootY]) {
                parent.set(rootX, rootY);

                largest.set(rootY, max(largest[rootY], largest[rootX]));
                smallest.set(rootY, min(smallest[rootY], smallest[rootX]));
                sz.set(rootY, sz[rootY] + sz[rootX]);
            } else if (rank[rootX] > rank[rootY]) {
                parent.set(rootY, rootX);

                largest.set(rootX, max(largest[rootX], largest[rootY]));
                smallest.set(rootX, min(smallest[rootX], smallest[rootY]));
                sz.set(rootX, sz[rootX] + sz[rootY]);
            } else {
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
        largest.commit();
        smallest.commit();
        sz.commit();
        num_components.commit();
    }

    void revert()
    {
        parent.revert();
        rank.revert();
        largest.revert();
        smallest.revert();
        sz.revert();
        num_components.revert();
    }
};