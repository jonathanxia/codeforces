#pragma once
#include <lib/common.h>
#include <lib/bitster.h>

/**
 * A set S that supports adding a number x and all of its
 * submasks to S.
 * 
 * S.insert_submasks(x) // Inserts all submasks of x
 * S.count(x) // 1 if it exists
 * 
 * The worst case for a single insertion is O(2^num_bits)
 * However, amortized, the total runtime is capped at 2^num_bits
 * due to caching
 */
struct SubmaskSet {
    ll m_num_bits;
    vector<bool> m_is_present;

    SubmaskSet(int num_bits) : m_num_bits(num_bits), m_is_present(1 << m_num_bits) {}

    // Inserts all submasks of x into the set
    void insert_submasks(ll x) {
        assert(x >= 0);
        assert(x < len(m_is_present));
        deque<ll> q;
        q.push_back(x);
        while (q.size() > 0) {
            ll value = q.front();
            q.pop_front();            
            if (m_is_present[value]) continue;
            m_is_present[value] = true;
            // Push all submasks
            FOR(b, 0, m_num_bits - 1) if (bitster::get_bit(value, b)) {
                q.push_back(value ^ (1LL << b));
            }
        }
    }

    int count(ll x) {
        if (x >= len(m_is_present)) return 0;
        if (x < 0) return 0;
        return m_is_present[x];
    }
};