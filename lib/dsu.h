// union find
#include "common.h"
struct DSU {
    // Construct DSU, where n is the total number of nodes
    // smart_union determines whether a unite() operation always unites
    // smaller to larger
    DSU(ll n, bool smart_union = true)
        : m_link(n)
        , m_size(n, 1)
        , m_smart { smart_union }
    {
        walk(i, m_link)
        {
            m_link[i] = i;
        }
    }
    // Return representative of x
    ll find(ll x)
    {
        while (x != m_link[x])
            x = m_link[x];
        return x;
    }
    // Return whether a and b are in the same set
    ll same(ll a, ll b)
    {
        return find(a) == find(b);
    }
    // Unites the sets of a and b
    void unite(ll a, ll b)
    {
        a = find(a);
        b = find(b);
        if (a == b) // a and b are already in the same set!
            return;
        if (m_smart && m_size[a] < m_size[b])
            swap(a, b);
        m_size[a] += m_size[b];
        m_link[b] = a;
    }
    // Finds size of the set containing x
    ll get_size(ll x)
    {
        return m_size[find(x)];
    }
    vl m_link;
    vl m_size;
    bool m_smart;
};
