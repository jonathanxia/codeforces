#ifndef ATCODER_SCC_HPP
#define ATCODER_SCC_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#include "atcoder/internal_scc"

namespace atcoder {

struct scc_graph {
  public:
    scc_graph() : internal(0) {}
    explicit scc_graph(int n) : internal(n) {}

    void add_edge(int from, int to) {
        int n = internal.num_vertices();
        assert(0 <= from && from < n);
        assert(0 <= to && to < n);
        internal.add_edge(from, to);
    }

    std::vector<std::vector<int>> scc() { return internal.scc(); }

  private:
    internal::scc_graph internal;
};

std::vector<std::vector<int>> scc(const std::vector<std::vector<std::pair<long long, long long>>>& g) {
    scc_graph graph(g.size());
    for (int u = 0; u < g.size(); u++) {
        for (auto [v, w] : g[u]) {
            graph.add_edge(u, v);
        }
    }
    return graph.scc();
}

}  // namespace atcoder

#endif  // ATCODER_SCC_HPP
