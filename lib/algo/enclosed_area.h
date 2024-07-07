#include <lib/common.h>
#include <lib/commit_dsu.h>

namespace algo {
    // Calculates the total number of empty lattice points enclosed by
    // the given points, where enclosure is defined go-style.
    // Lattice points themselves do not count towards the count.
    // Returns a list of areas, where each entry is the area of an
    // empty enclosed region
    vl total_enclosed_areas(const vpl& xy) {
        const ll INF = 1e18;
        ll n = len(xy);
        if (n == 0) {
            return vl{};
        }
        map<ll, vl> points;
        foreachp(x, y, xy) {
            points[x].push_back(y);
        }
        foreachp(x, v, points) {
            v.push_back(-INF);
            v.push_back(INF);
            sort(ALL(v));
        }
        ll largest_x = points.rbegin()->first;
        points[largest_x + 1].push_back(-INF);
        points[largest_x + 1].push_back(INF);

        vector<array2> node_to_seg;
        set<array3> segs;
        segs.insert({-INF, INF, 0});
        node_to_seg.push_back({-INF, INF});
        map<ll, vl> graph;

        ll prev_x = -INF;
        foreachp(x, v, points) {
            ll m = len(v);
            set<array3> new_segs;

            // Leak everything out
            if (x - prev_x > 1) {
                foreach(arr, segs) {
                    graph[arr[2]].push_back(0);
                    graph[0].push_back(arr[2]);
                }
                segs.clear();
                segs.insert({-INF, INF, 0});
            }
            prev_x = x;

            FOR(i, 0, m - 2) {
                ll a = v[i];
                ll b = v[i + 1];
                if (a + 1 == b) continue;
                a++; b--;
                // Create new node representing this
                ll node = len(node_to_seg);
                new_segs.insert({a, b, node});
                node_to_seg.push_back({a, b});

                auto it = segs.lower_bound({a, INF + 1, INF + 1});
                it--;
                while (it != segs.end() && (*it)[0] <= b) {
                    // Check if segments intersect
                    if ((*it)[0] <= b && (*it)[1] >= a)
                    {
                        graph[node].push_back((*it)[2]);
                        graph[(*it)[2]].push_back(node);
                    }
                    it++;
                }
            }
            segs = new_segs;
        }

        // Now n is the number of nodes
        n = len(node_to_seg);

        DSU dsu(n);
        FOR(node, 0, n - 1) {
            foreach(child, graph[node]) {
                dsu.unite(node, child);
            }
        }

        ll num_components = dsu.num_components.value();
        map<ll, ll> ans;

        FOR(node, 0, n - 1) {
            ll component = dsu.find(node);
            if (component != dsu.find(0)) {
                ll a = node_to_seg[node][0];
                ll b = node_to_seg[node][1];
                ans[component] += b - a + 1;
            }
        }
        vl output;
        foreachp(k, v, ans) {
            output.push_back(v);
        }
        return output;
    }
} // namespace algo