#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define int ll
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define forn(i, l, r) for(int i = l; i <= r; ++i)
#define ford(i, r, l) for(int i = r; i >= l; --i)
#define FOR(i, n) for(int i = 0; i < n; ++i)
#define fi first
#define se second
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pb push_back
#define task "MEETING"
#define endl "\n"
#define sz(a) a.size()
#define C(x, y) make_pair(x, y)
#define bit(i, mask) (mask >> i & 1)
 
template<typename T> bool maximize(T &res, const T &val) { if (res <= val){ res = val; return true; }; return false; }
template<typename T> bool minimize(T &res, const T &val) { if (res >= val){ res = val; return true; }; return false; }
 
 
const int N =  2e6 + 7;
const int K = 1e2 + 1;
const int MOD = 998244353;
const int INF = 1e18 + 9999;
const int block_size = 230;
const int offset = N;
const int LIM = 2e5;
const int AL = 26;
 
int k, a[N], cnt[21], lg[N], pos[N], fact[N], sum[N], b[N];
 
int check[N];
 
int mul(int x, int y) {return x * y % MOD;}
 
int bin_pow(int x, int y)
{
    int res = 1;
    for(; y; y >>= 1, x = mul(x, x))
        if(y & 1) res = mul(res, x);
    return res;
}
 
void solve()
{
    cin >> k;
    if(k == 0) return cout << 1, void();
    int n = 1 << k;
    lg[0] = 0;
    lg[1] = 0;
    forn(i, 2, n) lg[i] = lg[i / 2] + 1;
    fact[0] = 1;
    rep(i, n) fact[i] = fact[i - 1] * i % MOD, pos[i] = -1;
    forn(i, 1, k) cnt[i] = 1 << i - 1;
    forn(i, 0, n - 1)
    {
        cin >> a[i];
        if(a[i] != -1)
            cnt[lg[a[i] - 1] + 1]--, pos[a[i]] = i;
        sum[i] = 0;
        if(a[i] == -1) sum[i]++;
    }
    if(k == 1)
    {
        if(a[0] == a[1]) return cout << 2, void();
        return cout << 1, void();
    }
    if(pos[1] != -1 && pos[2] != -1)
    {
        if((pos[1] >> k - 1) == (pos[2] >> k - 1)) return cout << 0, void();
    }
    forn(i, k - 1, k - 1)
    {
        int l = (1 << i) + 1;
        int r = 1 << i + 1;
        forn(j, l, r) if(pos[j] != -1)
        {
            int idx = pos[j] >> k - i;
            if(check[idx]) return cout << 0, void();
            check[idx] = 1;
        }
        forn(j, 0, (1 << i) - 1) check[j] = 0;
    }
    int res = 1;
    int len = 2;
    ford(i, k, 2)
    {
        res = mul(res, fact[cnt[i]]);
        int t = 0;
        //cout << cnt[k] << " " << res << endl;
        for(int j = 0; j <= (1 << i - 1) - 1; ++j) sum[j] = sum[j * 2] + sum[j * 2 + 1];
        //if(k)
        for(int j = 0; j + len - 1 <= n - 1; j += len)
        {
            bool flag = 0;
            forn(l, j, j + len - 1) if(a[l] != -1)
            {
                if(((1 << i - 1) + 1) <= a[l] && a[l] <= (1 << i))
                {
                    flag = 1;
                    break;
                }
            }
            if(!flag)
            {
                res = mul(res, sum[t]);
                sum[t]--;
            }
            t++;
            
        }
        
        len <<= 1;
       // cout << i << " " << res << endl;
    }
 
    if(pos[1] == -1 && pos[2] == -1) res = mul(res, 2);
 
    cout << res << endl;
 
}
 
signed main()
{
 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(fopen(task".inp", "r"))
    {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
 
    int TC = 1;
   // cin >> TC;
 
    while(TC--)
    {
        solve();
       // cout << endl;
    }
 
    return 0;
}