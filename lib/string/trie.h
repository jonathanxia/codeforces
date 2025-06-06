#pragma once
#include <lib/common.h>

template <size_t NUM_FREQ=1>
struct Trie {
    // N is number of possible characters in a string
    const static int N = 26;

    // baseChar defines the base character for possible characters
    // like '0' for '0','1','2'... as possible characters in string
    const static char baseChar = 'a';

    struct TrieNode {
        int next[N];
        // if isEnd is set to true , a string ended here
        bool isEnd;
        // freq is how many times this prefix occurs
        array<int, NUM_FREQ> freq;
        // length of the prefix at this node
        int length;
        TrieNode()
        {
            for (int i = 0; i < N; i++)
                next[i] = -1;
            isEnd = false;
            FOR(i, 0, NUM_FREQ - 1)
                freq[i] = 0;
            length = 0;
        }
        TrieNode(int _length)
            : TrieNode()
        {
            length = _length;
        }
    };

    // the implementation is via vector and each position in this vector
    // is similar as new pointer in pointer type implementation
    vector<TrieNode> tree;

    // Base Constructor
    Trie()
    {
        // This might be necessary in memory constrained environment
        // tree.reserve(2000099);
        tree.push_back(TrieNode());
    }

    // inserting a string in trie
    void insert(const string& s, int typ=0)
    {
        int p = 0;
        tree[p].freq[typ]++;
        for (int i = 0; i < (ll)s.size(); i++) {
            if (tree[p].next[s[i] - baseChar] == -1) {
                tree.push_back(TrieNode());
                tree[p].next[s[i] - baseChar] = tree.size() - 1;
            }

            p = tree[p].next[s[i] - baseChar];
            tree[p].freq[typ]++;
        }
        tree[p].isEnd = true;
    }

    // returns number of times the prefix s appears in the trie
    ll check_prefix(const string& s, int typ=0)
    {
        int p = 0;
        for (int i = 0; i < (ll)s.size(); i++) {
            if (tree[p].next[s[i] - baseChar] == -1)
                return 0;

            p = tree[p].next[s[i] - baseChar];
        }
        return tree[p].freq[typ];
    }

    // check if string s exists
    bool check_string(const string& s)
    {
        int p = 0;
        for (int i = 0; i < (ll)s.size(); i++) {
            if (tree[p].next[s[i] - baseChar] == -1)
                return false;

            p = tree[p].next[s[i] - baseChar];
        }

        return tree[p].isEnd;
    }

    // persistent insert
    // returns location of new head
    int persistent_insert(int head, const string& s, int typ=0)
    {
        int old = head;

        tree.push_back(TrieNode());
        int now = tree.size() - 1;
        int newHead = now;

        int i, j;

        for (i = 0; i < (ll)s.size(); i++) {
            if (old == -1) {
                tree.push_back(TrieNode());
                tree[now].next[s[i] - baseChar] = tree.size() - 1;
                tree[now].freq[typ]++;
                now = tree[now].next[s[i] - baseChar];
                continue;
            }
            for (j = 0; j < N; j++)
                tree[now].next[j] = tree[old].next[j];
            tree[now].freq = tree[old].freq;
            tree[now].isEnd = tree[old].isEnd;

            tree[now].freq[typ]++;

            tree.push_back(TrieNode());
            tree[now].next[s[i] - baseChar] = tree.size() - 1;

            old = tree[old].next[s[i] - baseChar];
            now = tree[now].next[s[i] - baseChar];
        }

        tree[now].freq[typ]++;
        tree[now].isEnd = true;

        return newHead;
    }

    // persistent check prefix
    ll persistent_check_prefix(int head, const string& s, int typ=0)
    {
        int p = head;
        for (int i = 0; i < (ll)s.size(); i++) {
            if (tree[p].next[s[i] - baseChar] == -1)
                return 0;

            p = tree[p].next[s[i] - baseChar];
        }
        return tree[p].freq[typ];
    }

    // persistent check string
    bool persistent_check_string(int head, const string& s)
    {
        int p = head;
        for (int i = 0; i < (ll)s.size(); i++) {
            if (tree[p].next[s[i] - baseChar] == -1)
                return false;

            p = tree[p].next[s[i] - baseChar];
        }
        return tree[p].isEnd;
    }
};
