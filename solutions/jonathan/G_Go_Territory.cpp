// Link: https://atcoder.jp/contests/abc361/tasks/abc361_g
#include <lib/algo/enclosed_area.h>
#include <lib/vv/sum.h>

void solve() {
    ll n; cin >> n;
    vpl points(n); cin >> points;
    vl areas = algo::total_enclosed_areas(points);
    print(vv::sum(areas));
}

int main() {
    init();
    solve();
    return 0;
}