// Work in progress

vector<basis<int>> bs;
vector<pair<pair<int, int>, int>> queries;
vector<int> ans, sz, marker;
vector<bool> used;
 
int get_size(int v, int p) {
    sz[v] = 1;
    for(int u: adj[v]) {
        if(u != p && !used[u]) {
            sz[v] += get_size(u, v);
        }
    }
    return sz[v];
}
 
void dfs_basis(int v, int p, basis<int> pref_bs) {
    basis<int> nw_bs = pref_bs;
    nw_bs.add(a[v]);
    bs[v] = nw_bs;
    for(auto u: adj[v]) {
        if(u != p && !used[u]) {
            dfs_basis(u, v, nw_bs);
        }
    }
}
 
void dfs_marker(int v, int p, int mark) {
    marker[v] = mark;
    for(int u: adj[v]) {
        if(u != p && !used[u]) {
            dfs_marker(u, v, mark);
        }
    }
}
 
void decompose(int u, vector<int> qidx) {
    get_size(u, -1);
    int n = sz[u], centroid = u, p = -1;
    while(true) {
        int nxt = -1;
        for(int v: adj[centroid]) {
            if(v != p && !used[v] && sz[v] > n / 2) {
                nxt = v;
                break;
            }
        }
 
        if(nxt != -1) {
            p = centroid;
            centroid = nxt;
        } else {
            break;
        }
    }
 
    used[centroid] = true;
    basis<int> pref_bs;
    pref_bs.init(MAXLOG);
    pref_bs.add(a[centroid]);
    bs[centroid] = pref_bs;
 
    int mark = 0;
    vector<vector<int>> children_queries(adj[centroid].size());
    for(int v: adj[centroid]) {
        if(!used[v]) {
            dfs_marker(v, centroid, mark);
            dfs_basis(v, centroid, pref_bs);
        }
        mark++;
    }
 
    marker[centroid] = mark;
    for(int idx: qidx) {
        auto [xy, k] = queries[idx];
        auto [x, y] = xy;
        if(marker[x] == marker[y] && x != centroid) {
            children_queries[marker[x]].push_back(idx);
        } else {
            basis<int> q_basis = bs[x].merge(bs[y]);
            if(q_basis.can_create(k)) {
                ans[idx] = 1;
            } else {
                ans[idx] = 0;
            }
        }
    }
 
    int i = 0;
    for(int v: adj[centroid]) {
        if(!used[v] && children_queries[i].size() > 0) {
            decompose(v, children_queries[i]);
        }
        i++;
    }
}