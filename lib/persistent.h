#include <lib/common.h>

template <typename T=ll>
struct PersistentVector {
    vector<T> data;
    vector<pair<int, T>> snapshots;
    vector<int> checkpoints;

    bool persist;

    PersistentVector(int size, bool persist_=true)
        : data(size, 0), persist(persist_)
    {
    }

    T operator[](int idx) { return data[idx]; }

    void set(int idx, T value)
    {
        if (!persist) {
            data[idx] = value; return;
        }
        snapshots.push_back(mp(idx, data[idx]));
        data[idx] = value;
    }

    void commit() {
        if (persist) {
            checkpoints.pb(len(snapshots));
        }
    }

    void revert()
    {
        if (!persist) return;
        ll snap_len = checkpoints.back();
        while (len(snapshots) > snap_len) {
            auto p = snapshots.back();
            data[p.first] = p.second;
            snapshots.pop_back();
        }
        checkpoints.pop_back();
    }
};

template <typename M, typename K, typename V>
struct PersistentMap {
    M data;
    V dflt_value;

    vector<pair<K, V>> snapshots;
    vector<int> checkpoints;

    PersistentMap(V dflt_value_) : dflt_value(dflt_value_)
    {
    }

    V operator[](K idx) { return data[idx]; }

    void set(K idx, V value)
    {
        if (data.count(idx)) {
            snapshots.push_back(mp(idx, data[idx]));
        }
        else {
            snapshots.push_back(mp(idx, dflt_value));
        }
        data[idx] = value;
    }

   void commit()
    {
        checkpoints.pb(len(snapshots));
    }

    void revert()
    {
        ll snap_len = checkpoints.back();
        while (len(snapshots) > snap_len) {
            pair<K, V> snap = snapshots.back();
            snapshots.pop_back();

            data[snap.first] = snap.second;
        }

        checkpoints.pop_back();
    }
};

// Trivially implement this as a 1-element array
template <typename T>
struct PersistentValue
{
    PersistentVector<T> v;
    PersistentValue() : v(1) {

    }

    T value() {
        return v[0];
    }

    void set(T val) {
        v.set(0, val);
    }

    void commit() { v.commit(); }
    void revert() { v.revert(); }
};

