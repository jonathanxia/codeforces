/**
 *    author:  tourist
 *    created: 12.06.2023 10:41:14       
**/
#include <bits/stdc++.h>
 
using namespace std;
 
const vector<int> p10 = {1, 10, 100, 1000, 10000};
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  
  int decide = 0;

  while (tt--) {
    string s;
    cin >> s;
    int len = (int) s.size();
    const int inf = (int) 2.01e9;
    vector<vector<int>> f(5, vector<int>(2, -inf));
    f[0][0] = 0;
    for (int pos = len - 1; pos >= 0; pos--) {
      vector<vector<int>> new_f(5, vector<int>(2, -inf));
      int me = (int) (s[pos] - 'A');
      for (int mx = 0; mx < 5; mx++) {
        for (int have = 0; have < 2; have++) {
          for (int dig = 0; dig < 5; dig++) {
            int new_mx = max(mx, dig);
            int new_have = have + (dig != me);
            int new_value = f[mx][have] + (dig < mx ? -1 : 1) * p10[dig];
            if (new_have <= 1) {
                if (new_f[new_mx][new_have], new_value) {
                    decide = pos;
                }
              new_f[new_mx][new_have] = max(new_f[new_mx][new_have], new_value);
            }
          }
        }
      }
      swap(f, new_f);
    }
    int ans = -inf;
    for (int mx = 0; mx < 5; mx++) {
      for (int have = 0; have < 2; have++) {
        ans = max(ans, f[mx][have]);
      }
    }
    cout << ans << '\n';
    cout << "decided to change " << decide << endl;
  }
  return 0;
}