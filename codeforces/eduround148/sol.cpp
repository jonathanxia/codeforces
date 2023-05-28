#include<bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int add(int x, int y, int mod = MOD)
{
	return ((x + y) % mod + mod) % mod;
}

int mul(int x, int y, int mod = MOD)
{
	return (x * 1ll * y) % mod;
}

int binpow(int x, int y, int mod = MOD)
{
	int z = add(1, 0, mod);
	while(y > 0)
	{
		if(y % 2 == 1) z = mul(z, x, mod);
		y /= 2;
		x = mul(x, x, mod);
	}
	return z;
}

vector<int> psum(vector<int> v)
{
	vector<int> ans(1, 0);
	for(auto x : v) ans.push_back(add(ans.back(), x));
	return ans;
}

int main()
{
	int n;
	cin >> n;
	vector<int> a(n);
	cin >> a[0];
	int x, y, m, k;
	cin >> x >> y >> m >> k;
	for(int i = 1; i < n; i++)
		a[i] = add(mul(a[i - 1], x, m), y, m);

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
	
	for(int i = 0; i <= k; i++)
		a = psum(a);
	long long ans = 0;
	
	for(int i = 1; i <= n; i++) {
        cout << "a = " << a[i + 1] << endl;
		ans ^= (a[i + 1] * 1ll * i);
    }
	cout << ans << endl;
}