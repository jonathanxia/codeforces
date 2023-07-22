#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long 
#define pb(e) push_back(e)
#define sv(a) sort(a.begin(),a.end())
#define sa(a,n) sort(a,a+n)
#define mp(a,b) make_pair(a,b)
#define vf first
#define vs second
#define all(x) x.begin(),x.end()
 
void solve(){
	int n , m , q;
	cin >> n >> m >> q;
	string st;
	cin >> st;
	vector<pair<int,int>> ranges;
	for(int i = 0; i < m; i++){
		int l , r;
		cin >> l >> r;
		l--;
		r--;
		ranges.pb(mp(l,r));
	}
	set<int> s;
	for(int i = 0; i < n; i++)s.insert(i);
	vector<int> v;
	int pos_in_v[n];
	memset(pos_in_v,-1,sizeof pos_in_v);
	for(int i = 0; i < m; i++){
		auto it = s.lower_bound(ranges[i].vf);
		vector<int> toerase;
		while(it != s.end() && (*it) <= ranges[i].vs){
			toerase.pb((*it));
			v.pb(toerase.back());
			pos_in_v[toerase.back()] = v.size()-1;
			it++;
		}
		while(toerase.size()){
			s.erase(toerase.back());
			toerase.pop_back();
		}
	}
	int cnt = 0;
	for(int i = 0; i < n; i++){
		if(st[i] == '1')cnt++;
	}
	int ans = 0;
	for(int i = 0; i < min(cnt , (int)v.size()); i++){
		if(st[v[i]] == '0')ans++;
	}
	
	while(q--){
		int pos;
		cin >> pos;
		pos--;
		if(pos_in_v[pos] != -1 && pos_in_v[pos] < cnt){
			if(st[pos] == '0'){
				ans--;
			}
			else ans++;
		}
		if(st[pos] == '0'){
			st[pos] = '1';
			cnt++;
			if(cnt <= v.size() && st[v[cnt-1]] == '0')ans++;
		}
		else {
			st[pos] = '0';
			if(cnt > 0 && cnt <= v.size() && st[v[cnt-1]] == '0')ans--;
			cnt--;
		}
		cout << ans << '\n';
	}
}
 
int main(){
ios_base::sync_with_stdio(false);
cin.tie(NULL);
	//int t;cin >> t;while(t--)
	solve();
	return 0;
}