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
    vl largest;
    vl smallest;

    DSU(int size) : parent(size), rank(size), largest(size), smallest(size) {
        for (int i = 0; i < size; ++i) {
            parent.set(i, i);
            rank.set(i, 0);
            largest[i] = i;
            smallest[i] = i;
        }
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
                chkmax(largest[rootY], largest[rootX]);
                chkmin(smallest[rootY], smallest[rootX]);
            } else if (rank[rootX] > rank[rootY]) {
                parent.set(rootY, rootX);
                chkmax(largest[rootX], largest[rootY]);
                chkmin(smallest[rootX], smallest[rootY]);
            } else {
                parent.set(rootY, rootX);
                rank.set(rootX, rank[rootX] + 1);
                chkmax(largest[rootX], largest[rootY]);
                chkmin(smallest[rootX], smallest[rootY]);
            }
        }
    }

    void commit() {
        parent.commit();
        rank.commit();
    }

    void revert() {
        parent.revert();
        rank.revert();
    }
};



// int main() {
//     PersistantVector pv(7);

//     pv.set(3, 2);
//     pv.set(5, 6);

//     print("pv.data", pv.data);

//     pv.commit();

//     pv.set(3, 100);
//     pv.set(6, 20);

//     print("pv.data", pv.data);

//     pv.revert();

//     print("pv.data", pv.data);
// }