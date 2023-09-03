#include <lib/common.h>

struct PersistentVector {
    vl data;
    stack<umapll> snapshots;

    PersistentVector(int size)
        : data(size, 0)
    {
        snapshots.push(umapll());
    }

    ll operator[](int idx) { return data[idx]; }

    void set(int idx, ll value)
    {
        auto& ss = snapshots.top();
        if (!ss.count(idx)) {
            ss[idx] = data[idx];
        }

        data[idx] = value;
    }

    void commit() { snapshots.push(umapll()); }

    void revert()
    {
        auto dd = snapshots.top();
        snapshots.pop();

        foreach (k, dd) {
            data[k.first] = k.second;
        }
    }
};

template <typename M, typename K, typename V>
struct PersistentMap {
    M data;
    stack<umap<K, V>> snapshots;
    stack<vector<K>> deletion_list;

    PersistentMap()
    {
        snapshots.push(umap<K, V>());
        deletion_list.push(vector<K>());
    }

    V operator[](K idx) { return data[idx]; }

    void set(K idx, V value)
    {
        auto& ss = snapshots.top();
        auto& dl = deletion_list.top();
        if (!ss.count(idx)) {
            // This is the first time we are
            // setting the index after a commit,
            // so we make sure to save it

            // If we did not have the value before,
            // we make sure to remember that and put
            // that in our deletion list
            if (data.count(idx) == 0) {
                dl.push_back(idx);
            }
            // Otherwise, save the value
            else {
                ss[idx] = data[idx];
            }
        }

        data[idx] = value;
    }

    void erase(K idx)
    {
        auto& ss = snapshots.top();
        if (!ss.count(idx) && data.count(idx) > 0) {
            ss[idx] = data[idx];
        }

        data.erase(idx);
    }

    void commit()
    {
        snapshots.push(umap<K, V>());
        deletion_list.push(vector<K>());
    }

    void revert()
    {
        auto dd = snapshots.top();
        snapshots.pop();

        auto dl = deletion_list.top();
        deletion_list.pop();

        foreach (k, dd) {
            data[k.first] = k.second;
        }
        foreach (k, dl) {
            data.erase(k);
        }
    }
};

template <typename T>
struct PersistentValue {
    T data;
    stack<umap<int, T>> snapshots;

    PersistentValue() { snapshots.push(umap<int, T>()); }

    void set(T value)
    {
        auto& ss = snapshots.top();
        if (!ss.count(0)) {
            ss[0] = data;
        }

        data = value;
    }

    void commit() { snapshots.push(umap<int, T>()); }

    void revert()
    {
        auto dd = snapshots.top();
        snapshots.pop();

        foreach (k, dd) {
            data = k.second;
        }
    }
};