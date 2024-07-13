#pragma once
#include <lib/common.h>

template<int ALPHABET_SIZE=26, int ALPHABET_OFFSET='a'>
struct Trie {
    int cnt = 0;
    Trie * data[ALPHABET_SIZE];

    ~Trie() {
        rep(i,0,ALPHABET_SIZE-1) delete data[i];
    }

    template<typename Indexable>
    void insert(Indexable& w, int idx=0) {
        cnt++;
        if (idx == (int)w.size()) return;

        int c = w[idx] - ALPHABET_OFFSET;
        if (data[c] == NULL) data[c] = new Trie{};
        data[c]->insert(w, idx+1);
    }
};