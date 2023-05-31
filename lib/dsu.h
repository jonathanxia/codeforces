#include<lib/common.h>

class PersistantVector {
public:
    vl data;
    stack<umapll> snapshots;

    PersistantVector(int size) : data(size, 0) {
        snapshots.push(umapll());
    }

    const ll operator[](int idx) const {
        return data[idx];
    }

    void set(int idx, ll value) {
        auto& ss = snapshots.top();
        if (!ss.count(idx)) {
            ss[idx] = data[idx];
        }

        data[idx] = value;
    }

    void commit() {
        snapshots.push(umapll());
    }

    void revert() {
        auto dd = snapshots.top();
        snapshots.pop();

        foreach(k, dd) {
            data[k.first] = k.second;
        }
    }
};

class DSU {
public:
    PersistantVector parent;
    PersistantVector rank;
    PersistantVector is_alive;
    ll num_alive;
    stack<ll> num_alive_snaps;

    DSU(int size) : parent(size), rank(size), is_alive(size) {
        for (int i = 0; i < size; ++i) {
            parent.set(i, i);
            is_alive.set(i, true);
            rank.set(i, 0);
        }
        num_alive = size;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent.set(x, find(parent[x])); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent.set(rootX, rootY);
            } else if (rank[rootX] > rank[rootY]) {
                parent.set(rootY, rootX);
            } else {
                parent.set(rootY, rootX);
                rank.set(rootX, rank[rootX] + 1);
            }

            // Are we killing any components? Death is
            // infectious
            bool new_is_alive = is_alive[rootX] && is_alive[rootY];

            num_alive = num_alive - is_alive[rootX] - is_alive[rootY] + new_is_alive;

            is_alive.set(rootX, new_is_alive);
            is_alive.set(rootY, new_is_alive);
        }

        else {
            // Same connected component, if it was alive,
            // it is now dead
            if (is_alive[rootX]) {
                num_alive--;
                is_alive.set(rootX, false);
            }
        }

    }

    void commit() {
        parent.commit();
        rank.commit();
        is_alive.commit();
        num_alive_snaps.push(num_alive);
    }

    void revert() {
        parent.revert();
        rank.revert();
        is_alive.revert();
        num_alive = num_alive_snaps.top();
        num_alive_snaps.pop();
    }
};




int main() {
    PersistantVector pv(7);

    pv.set(3, 2);
    pv.set(5, 6);

    print("pv.data", pv.data);

    pv.commit();

    pv.set(3, 100);
    pv.set(6, 20);

    print("pv.data", pv.data);

    pv.revert();

    print("pv.data", pv.data);
}