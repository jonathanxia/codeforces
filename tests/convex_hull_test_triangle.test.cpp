#define PROBLEM "https://judge.yosupo.jp/problem/count_points_in_triangle"

#include <lib/common.h>
#include <lib/geo/convex_polygon.h>

void solve() {
    using P = geo::Point<ll>;
    ll n; cin >> n;
    vector<P> A(n); cin >> A;
    ll m; cin >> m;
    vector<P> B(m); cin >> B;
    ll q; cin >> q;
    cepeat(q) {
        ll a, b, c; cin >> a >> b >> c;
        geo::ConvexPolygon<ll> poly({A[a], A[b], A[c]}, true);
        ll ans = 0;
        FOR(i, 0, m - 1) ans += (poly.side(B[i]) == 1);
        print(ans);
    }
}

int main() {
  solve();
  return 0;
}