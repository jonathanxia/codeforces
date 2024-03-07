#pragma once
#include <lib/common.h>

/**
 * The legendary suffix automaton that solves all string problems.
 *
 * One can think of this as a trie of all substrings of a given
 * string s. That is what the to[node][char] -> next node is for.
 *
 * The automaton is also endowed with suffix links, in link[]. See
 * cp-algorithms for why these are useful.
 *
 * Usage: https://cses.fi/problemset/result/8658481/
*/
struct SuffixAutomaton
{
    /**
     * Core instance fields, the fields that are truly the automaton
    */
    // The trie edges
    // If invalid, it will point to 0 by default
	vector<map<char, int>> to;

    // Length of the substring
	vector<int> length;

    // The suffix link
    vector<int> link;

    // n = number of nodes in automaton
    // last = the node referring to the full string
	int last;

	void add_letter(char c)
	{
        finalized = false;
		int p = last, cl, q;

        // This check is only used if we are making a
        // generalized automaton (i.e., over multiple strings).
        // If in the simple single-string use case, this can be
        // ignored.
		if(to[p].count(c))
		{
  			q = to[p][c];
			if(length[q] == length[p] + 1)
			{
				last = q;
				return;
			}

			// Allocate new array elements
            cl = len(length);
            length.pb(length[p] + 1);
            to.pb(to[q]);
            link.pb(link[q]);
            link[q] = cl;
            last = cl;


            // Run up the suffix tree and redirect
            // any flow into the clone
			for(; to[p][c] == q; p = link[p])
				to[p][c] = cl;

			return;
		}

        // Construct a new node
        last = len(length);
        length.pb(length[p] + 1);
        link.pb(-1);
        to.emplace_back();

		for(; to[p][c] == 0; p = link[p])
			to[p][c] = last;

		if(to[p][c] == last)
		{
			link[last] = p;
			return;
		}

		q = to[p][c];
		if(length[q] == length[p] + 1)
		{
			link[last] = q;
			return;
		}

        // Time to clone, make a new state
        cl = len(length);
        length.pb(length[p] + 1);
        to.pb(to[q]);
        link.pb(link[q]);

        link[q] = cl;
        link[last] = cl;

		for(; to[p][c] == q; p = link[p])
			to[p][c] = cl;
	}

    // Destroys everything
	void clear()
	{
        finalized = false;
        // Include only the root node and reset all
        // points
        length.resize(1);
        link.resize(1);
        to.resize(1);

        length[0] = 0;
        link[0] = 0;
        to[0].clear();

		last = 0;
	}

	void init(const string& s)
	{
		clear();
		for(int i = 0; i < (int)s.size(); i++)
			add_letter(s[i]);
	}

    /**
     * For generalized automaton -- use this to add a string.
     * This will preserve previous automaton structure but
     * reset the last variable
    */
    void add_str(const string& s) {
        finalized = false;
        last = 0;
        for (int i = 0; i < len(s); i++) {
            add_letter(s[i]);
        }
    }

	SuffixAutomaton() {
        clear();
    }

    SuffixAutomaton(const string& s, bool finalize_=true) {
        init(s);
        if (finalize_)
            finalize(s);
    }

    // ---------------------------------------------------------
    /**
     * Finalized derived fields. These can be derived from the core fields,
     * but are here for convenience. Any call to init(), add_letter() or
     * add_str() will invalidate these statistics.
     *
     * These will only be valid after a call to finalize()
    */
    bool finalized = false;

    // Main path of the SA is the path corresponding to the
    // full string
    vb is_main_path;
    vi main_path_idx;

    // The reverse of the suffix link so we can actually do
    // suffix tree traversal
    vvi inv_link;
    // Size of the endpos set. Each node has an endpos set
    vi endpos_size;
    vb _eps_visited;

    // The finalize method. Needs to be called manually for
    // generalised setting, since the finalization of
    // main path depends on which string s you query for.
    void finalize(const string& s) {
        finalized = true;

        ll n = len(length);

        // First establish the main path
        is_main_path.resize(len(length));
        main_path_idx.resize(len(length), -1);
        endpos_size.resize(len(length), 0);

        ll p = 0;
        is_main_path[p] = true;
        walk(i, s) {
            p = to[p][s[i]];
            is_main_path[p] = true;
            main_path_idx[p] = i;
            endpos_size[p] = 1;
        }

        inv_link.resize(len(length));
        // Setup the inverse links
        FOR(i, 0, n - 1) inv_link[link[i]].pb(i);

        // Calculate endpos size properly, by performing dfs
        _eps_visited.resize(n, false);
        _endpos_size_dfs(0);
    }

    void _endpos_size_dfs(ll node) {
        _eps_visited[node] = true;
        foreach(child, inv_link[node]) {
            if (!_eps_visited[child])
                _endpos_size_dfs(child);
            endpos_size[node] += endpos_size[child];
        }
    }


    // Non core derived methods. These
    // are here for convenience

    ll longest_prefix_present(const string& s) {
        // Computes the longest prefix that is in the automaton
        ll ans = 0;
        ll p = 0;
        while (ans < len(s)) {
            if (to[p].count(s[ans]) == 0) return ans;

            p = to[p][s[ans]];
            ans++;
        }
        return ans;
    }

    bool check_string(const string& s) {
        return longest_prefix_present(s) == len(s);
    }

    // Returns -1 if string s is not present
    ll find_node(const string& s) {
        // Finds the node corresponding to string s
        ll node = 0;
        walk(i, s) {
            if (to[node].count(s[i]) == 0) {
                return -1;
            }
            node = to[node][s[i]];
        }
        return node;
    }

    // How many times s occurs
    ll num_occurrences(const string& s) {
        ll node = find_node(s);
        if (node == -1) return 0;

        assert(finalized);
        return endpos_size[node];
    }
};

