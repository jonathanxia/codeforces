#pragma once
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
    T operator[](int idx) const { return data[idx]; }

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

    // (key, old value, whether the key existed before)
    vector<tuple<K, V, bool>> snapshots;
    vector<int> checkpoints;

    PersistentMap(V dflt_value_) : dflt_value(dflt_value_)
    {
    }

    V operator[](K idx) {
        auto it = data.find(idx);
        return it == data.end() ? dflt_value : it->second;
    }

    void set(K idx, V value)
    {
        auto it = data.find(idx);
        if (it != data.end()) {
            snapshots.emplace_back(idx, it->second, true);
        }
        else {
            snapshots.emplace_back(idx, dflt_value, false);
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
            auto [key, value, existed] = snapshots.back();
            snapshots.pop_back();

            if (existed) data[key] = value;
            else data.erase(key);
        }

        checkpoints.pop_back();
    }
};

// Trivially implement this as a 1-element array
template <typename T>
struct PersistentValue
{
    PersistentVector<T> v;
    PersistentValue(bool persist=false) : v(1, persist) {

    }

    T value() {
        return v[0];
    }

    void set(T val) {
        v.set(0, val);
    }

    void commit() { v.commit(); }
    void revert() { v.revert(); }

    // Casting
    template <typename S>
    operator S() const { return static_cast<S>(v[0]); };
};

