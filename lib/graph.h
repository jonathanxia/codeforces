#include <lib/vv.h>

namespace graph
{
    // Specify target to stop Dijkstra once target is processed (does not process
    // target's neighbors)
    void dijkstra(const vvpl &graph, vl &dist, const vl& starts, ll target = -1LL)
    {
        repe(i, 0, len(dist))
        {
            dist[i] = LONG_LONG_MAX;
        }
        set<pl> pq;

        foreach(start, starts) {
            pq.insert({0, start});
            dist[start] = 0;
        }
        while (!pq.empty())
        {
            auto [distance, node] = *(pq.begin());
            pq.erase({distance, node});

            if (node == target)
            {
                break;
            }

            foreachp(child, edge, graph[node])
            {
                if (distance + edge < dist[child])
                {
                    pq.erase({dist[child], child});
                    pq.insert({distance + edge, child});
                    dist[child] = distance + edge;
                }
            }
        }
    }

    void dijkstra(const vvpl& graph, vl& dist, ll start, ll target=-1LL) {
        dijkstra(graph, dist, vl({start}), target);
    }

    // Runs bfs on a graph and stores the distances in dist
    // Starts need to be passed in, can have multiple start points
    vl bfs(const vvl& graph, const vl& starts, ll default_dist = LONG_LONG_MAX) {
        ll n = len(graph);
        vl dist(n);
        FOR(i, 0, n - 1) dist[i] = -1;

        deque<ll> pq;
        foreach(s, starts) {
            pq.push_back(s);
            dist[s] = 0;
        }

        while(len(pq)) {
            ll node = pq.front();
            pq.pop_front();

            // Process the node by adding its children
            foreach(child, graph[node]) {
                if (dist[child] >= 0) continue;

                dist[child] = dist[node] + 1;
                pq.push_back(child);
            }
        }
        return LC(x < 0 ? default_dist : x, x, dist);
    }

    // Runs bfs on a grid problem
    // Starts need to be passed in, can have multiple start points
    // allowed should be set to true if you just want to run BFS on the whole grid
    void grid_bfs(const vector<vb>& allowed, const vpl& starts, vvl& dist, ll default_dist = LONG_LONG_MAX, bool allow_diag = false) {
        ll n = len(allowed);
        ll m = len(allowed[0]);

        FOR(i, 0, n - 1) FOR(j, 0, m - 1) dist[i][j] = -1;

        deque<pl> pq;
        foreach(s, starts) {
            if (!allowed[s.first][s.second]) continue;
            pq.push_back(s);
            dist[s.first][s.second] = 0;
        }

        while(len(pq)) {
            pl node = pq.front();
            pq.pop_front();

            // Process the node by adding its children
            FOR(dir, 0, 3 + 4 * allow_diag) {
                pl child = {node.first + dx[dir], node.second + dy[dir]};
                // Check if you step out of bounds
                if (!(ordered(0, child.first, n - 1) && ordered(0, child.second, m - 1))) continue;
                // Check if the child is allowed
                if (!allowed[child.first][child.second]) continue;
                if (dist[child.first][child.second] >= 0) continue;

                dist[child.first][child.second] = dist[node.first][node.second] + 1;
                pq.push_back(child);
            }
        }

        FOR(i, 0, n - 1) FOR(j, 0, m - 1) {
            dist[i][j] = dist[i][j] < 0 ? default_dist : dist[i][j];
        }
    }

    vvl grid_bfs(const vector<vb>& allowed, const vpl& starts, ll default_dist = LONG_LONG_MAX, bool allow_diag = false) {
        ll n = len(allowed);
        ll m = len(allowed[0]);
        vvl dist(n, vl(m, -1));
        grid_bfs(allowed, starts, dist, default_dist, allow_diag);
        return dist;
    }

    // Returns weight of minimum/maximum spanning tree, and stores the tree in edges
    // Use seed to specify a starting point from which to run Prim's.

    ll prim(const vvpl &graph, vpl &edges, bool minimum = true, ll seed = 0LL)
    {
        set<tuple<ll, ll, ll>> heap;
        auto heap_top = [&]()
        {
            if (minimum)
                return *(heap.begin());
            else
                return *(heap.rbegin());
        };
        auto heap_pop = [&]()
        {
            if (minimum)
                heap.erase(*(heap.begin()));
            else
                heap.erase(*(heap.rbegin()));
        };
        ll n = len(graph);
        vb in_tree(n, false);
        ll total_weight = 0;

        // initialize the tree
        in_tree[seed] = true;
        foreachp(neighbor, weight, graph[seed])
        {
            heap.insert({weight, seed, neighbor});
        }

        while (!heap.empty())
        {
            // ignore top of the heap if the endpoint is already included
            if (in_tree[get<2>(heap_top())])
            {
                heap_pop();
                continue;
            }
            auto edge = heap_top();
            // add endpoint to tree
            in_tree[get<2>(edge)] = true;
            total_weight += get<0>(edge);
            edges.pb({get<1>(edge), get<0>(edge)});

            // look through neighbors of endpoint and add them to the heap
            foreachp(neighbor, weight, graph[get<2>(edge)])
            {
                if (!in_tree[neighbor])
                    heap.insert({weight, get<2>(edge), neighbor});
            }
        }
        return total_weight;
    }

    // Returns a topological sort order of a dag
    // If dag is not actually a dag, this will return a vl that is shorter than dag
    vl topo_sort(const vvl &dag)
    {
        ll n = len(dag);
        vl order;
        vb DFS_processed(n, false);
        vb DFS_processing(n, false);
        bool found_cycle = false;
        function<void(ll)> DFS = [&](ll node) -> void
        {
            if (found_cycle)
                return;
            if (DFS_processed[node])
                return;
            DFS_processing[node] = true;
            foreach (child, dag[node])
            {
                if (DFS_processing[child])
                {
                    // found cycle!
                    dprint("Potential error: topo_sort found a cycle in graph");
                    found_cycle = true;
                    return;
                }
                if (!DFS_processed[child])
                {
                    DFS(child);
                }
            }
            DFS_processed[node] = true;
            DFS_processing[node] = false;
            order.pb(node);
        };
        repe(i, 0, n)
        {
            DFS(i);
        }
        reverse(order.begin(), order.end());
        return order;
    }
    const ll inf = 1LL << 62;
    // Input: a matrix m with:
    // m[i][i] = 0 for all i
    // m[i][j] = weight(i, j) for adjecent nodes i, j
    // m[i][j] = graph::inf for non-adjacent nodes i, j
    void floyd_warshall(vvl& m)
    {
        int n = len(m);
        repe(i, 0, n) m[i][i] = min(m[i][i], ll(0));
        repe(k, 0, n) repe(i, 0, n) repe(j, 0, n) if (m[i][k] != inf && m[k][j] != inf)
        {
            auto newDist = max(m[i][k] + m[k][j], -inf);
            m[i][j] = min(m[i][j], newDist);
        }
        rep(k, 0, n) if (m[k][k] < 0) rep(i, 0, n) rep(j, 0, n) if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
    }
    // Finds cycles for directed graphs where degree of every node is 1
    // Returns a vvl: vector of the cycles in the graph
    vvl cycles(const vl& adj, vb& in_cycle, vb& in_chain, bool is1idx = false)
    {
        vvl cycles_;
        walk(i, adj)
        {
            if (is1idx && i == 0)
                continue;
            ll slow = i;
            ll fast = i;
            do {
                if (in_chain[slow] || in_cycle[slow] || in_chain[fast] || in_cycle[fast])
                    break;
                slow = adj[slow];
                fast = adj[adj[fast]];
            } while (slow != fast);
            if (slow == fast && !in_cycle[slow] && !in_chain[slow]) {
                vl cycle;
                // now slow and fast are equal, they must be in a cycle
                while (!in_cycle[slow]) {
                    in_cycle[slow] = true;
                    cycle.pb(slow);
                    slow = adj[slow];
                }
                cycles_.pb(cycle);
            }
            fast = i;
            while (!in_cycle[fast] && !in_chain[fast]) {
                in_chain[fast] = true;
                fast = adj[fast];
            }
        }
        return cycles_;
    }

    // Finds cycles for directed graphs where degree of every node is 1
    struct FunctionalGraph {
        vb in_cycle;
        vb in_chain;
        const vl& adj;
        vvl cycs;

        vl cycle_number;
        vl dist_from_cycle;

        FunctionalGraph(const vl& adj_, bool is1idx = false) :
            in_cycle(len(adj_)),
            in_chain(len(adj_)),
            adj(adj_),
            cycle_number(len(adj_), -1),
            dist_from_cycle(len(adj_))
        {
            cycs = cycles(adj, in_cycle, in_chain, is1idx);

            walk(i, cycs) {
                foreach(v, cycs[i]) cycle_number[v] = i;
            }

            ll n = len(adj);
            FOR(i, (int) is1idx, n - 1) {
                dfs(i);
            }
        }

        void dfs(ll node) {
            ll child = adj[node];
            if (cycle_number[node] != -1) {
                return;
            }
            dfs(child);
            cycle_number[node] = cycle_number[child];
            dist_from_cycle[node] = 1 + dist_from_cycle[child];
        }
    };

///   TREE  ALGORITHMS   ///
/// Also check out dfs.h ///

    // Only works for trees!
    pair<ll, vl> longest_path(vvpl &graph, ll n)
    {
        vl dist(n);
        vl parents(n);
        pl farthest = {0, 0};
        function<void(ll, ll)> dfs = [&](ll node, ll parent) -> void
        {
            chkmax(farthest, mp(dist[node], node));
            foreachp (child, weight, graph[node])
            {
                if (child == parent)
                    continue;
                dist[child] = dist[node] + weight;
                parents[child] = node;
                dfs(child, node);
            }
        };
        dfs(0, -1);
        ll start = farthest.second;
        farthest = {0, 0};
        vv::fill(dist, 0);
        vv::fill(parents, 0);

        dfs(start, -1);
        parents[start] = -1;
        ll end = farthest.second;
        vl path;
        while (end != -1)
        {
            path.pb(end);
            end = parents[end];
        }

        return {dist[farthest.second], path};
    }

///   TREE  ALGORITHMS   ///
/// Also check out dfs.h ///
}
