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

