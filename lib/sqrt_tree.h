#pragma once
#include <lib/common.h>

/*
Supports ranges updates and point queries

Stores n elements of type S (data) and ~sqrt(n) elements of type B (block_data).
The idea is that each element in 'block_data' corresponds to O(sqrt(n)) elements in 'data'.
Then if we do some large update we only need to update O(sqrt(n)) S/B entries.
Think: [ ][ ][][      ][      ][      ][ ][ ]
           l----------------------------r
Notice that unlike a lazy seg tree we never merge our 'block_data' into 'data'.

You need to override:
    merge_small - merge update (of type M) into S element
    merge_big - merge update (of type M) into B element
    get_answer - query an index given the relevant S and B elements

runtimes:
    update - O(sqrt(n) * O(merge_small + merge_large))
    query - O(get_answer)
*/
template<typename S, typename B, typename M, typename O>
struct SqrtTree {
    SqrtTree(int n, function<void(S&, M)> _merge_small, function<void(B&, M)> _merge_big, function<O(S&, B&)> _get_answer) {
        bsz = max((int)sqrt(n), 1);
        int num_blocks = ceildiv(n, bsz);
        data.resize(n);
        block_data.resize(num_blocks);
        merge_small = _merge_small;
        merge_big = _merge_big;
        get_answer = _get_answer;
    }

    O query(int i) {
        int bidx = floordiv(i, bsz);
        return get_answer(data[i], block_data[bidx]);
    }

    void update(int l, int r, M x) { // inclusive
        assert(r < len(data));
        int i = l;
        while (i <= r) {
            if (i % bsz == 0 and i + bsz - 1 <= r) {
                int bidx = floordiv(i, bsz);
                merge_big(block_data[bidx], x);
                i += bsz;
            } else {
                merge_small(data[i], x);
                i += 1;
            }
        }
    }

    void _debug() {
        print("Small blocks:");
        FOR(i, 0, len(data)-1) print("  i: ", i, "ele:", data[i]);
        print("Big blocks:");
        FOR(i, 0, len(block_data)-1) print("  i: ", i, "ele:", block_data[i]);
    }

    int bsz;
    vector<S> data;
    vector<B> block_data;
    function<void(S&, M)> merge_small;
    function<void(B&, M)> merge_big;
    function<O(S&, B&)> get_answer;
};