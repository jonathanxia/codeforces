#pragma once
#include <lib/common.h>

template <typename Container, typename T>
struct MergeSortTree {
	Container f(Container& c, const Container& a, const Container& b) {
        foreach(k, a) {
            c.insert(k);
        }
        foreach(k, b) {
            c.insert(k);
        }
        return c;
    } // (any associative fn)

    bool query_func(const Container& a, T L, T R) {
        auto it = a.lower_bound(L);
        if (it == a.end()) {
            return false;
        }
        return *it <= R;
    } // Replace with anything, but here you can just query if something exists
    // in the range L to R inclusive

    int n;
    vector<Container> s;

	MergeSortTree(const vector<T>& a) : n(len(a)), s(2*n) {
        // OK, this merge sort tree does not support updates yet
        // because that seems annoying
        FOR(i, n, 2 * n - 1) {
            s[i].insert(a[i - n]);
        }
        DOR(i, n - 1, 1) {
            f(s[i], s[2 * i], s[2 * i + 1]);
        }
    }

    // Checks whether any number from L to R inclusive
    // is in the array from index b to e, inclusive
	bool query(int b, int e, T L, T R) { // query [b, e]
        e++; // make this exclusive just to avoid bugs
		bool ra = false, rb = false;

		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = ra || query_func(s[b++], L, R);
			if (e % 2) rb = rb || query_func(s[--e], L, R);
		}

		return ra || rb;
	}
};

/**
 * A merge sort tree specialization that uses basic sorted vector
 * However, it allows you to store an auxillary cumsum object (or some other thing)
 * that allows for efficient queries on the sorted vector
 * 
 * For example, you can do MergeSortTreeWithPrefixSum<ll, cum::sum<ll>>
*/
template <typename T, typename CumsumType>
struct MergeSortTreeWithPrefixSum {
	void f(vector<T>& c, const vector<T>& a, const vector<T>& b) {
        // Invariant is that a and b are both sorted
        ll i1 = 0;
        ll i2 = 0;
        while (i1 < len(a) && i2 < len(b)) {
            if (a[i1] < b[i2]) {
                c.push_back(a[i1]);
                i1++;
            }
            else {
                c.push_back(b[i2]); i2++;
            }
        }
        while (i1 < len(a)) {
            c.pb(a[i1]); i1++;
        }
        while (i2 < len(b)) {
            c.pb(b[i2]); i2++;
        }
    } // (any associative fn)

    ll query_func(const vector<T>& a, const CumsumType& ca, T R) {
        ll idx = largest_st(i, a[i] <= R, 0, len(a) - 1);
        return ca.query(0, idx);
    } // Replace with anything, but here you can just query if something exists
    // in the range L to R inclusive

    int n;
    vector<vector<T>> s;
    vector<CumsumType> cs;

	MergeSortTreeWithPrefixSum(const vector<T>& a) : n(len(a)), s(2*n), cs(2 * n) {
        // OK, this merge sort tree does not support updates yet
        // because that seems annoying
        FOR(i, n, 2 * n - 1) {
            s[i].pb(a[i - n]);
        }
        DOR(i, n - 1, 1) {
            f(s[i], s[2 * i], s[2 * i + 1]);
        }

        FOR(i, 1, 2 * n - 1) {
            cs[i] = CumsumType(s[i]);
        }
    }

    // Checks whether any number from L to R inclusive
    // is in the array from index b to e, inclusive
	ll query(int b, int e, T R) { // query [b, e]
        e++; // make this exclusive just to avoid bugs
		ll ra = 0, rb = 0;

		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) {
                ra = ra + query_func(s[b], cs[b], R);
                b++;
            }
			if (e % 2) {
                e--;
                rb = rb + query_func(s[e], cs[e], R);
            }
		}

		return ra + rb;
	}
};

