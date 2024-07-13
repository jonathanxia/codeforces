// Link: https://atcoder.jp/contests/abc362/tasks/abc362_b
#include<lib/geo/base/point.h>
using P=geo::Point<ll>;

void solve() {
    P a;
    P b;
    P c; cin >> a >> b >> c;

    if ((b-a).dot(c-a) == 0) {
        print("Yes"); return;
    }
    if ((c-b).dot(a-b) == 0) {
        print("Yes"); return;
    }
    if ((a - c).dot(b - c) == 0) {
        print("Yes"); return;
    }
    print("No");
}

int main() {
    init();
    solve();
    return 0;
}