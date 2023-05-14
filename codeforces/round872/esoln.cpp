#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
#include<map>
using namespace std;

//  Definition of the macro.
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

typedef long long ll;

typedef vector<vector<int>> vvi;
typedef vector<int> vi;

typedef vector<vector<ll>> vvl;
typedef vector<ll> vl;
typedef vector<bool> vb;

// Number Theory
ll mod(ll a, ll p) {
    return (a % p + p) % p;
}

ll M = pow(10, 9) + 7;
ll mod(ll a) {
    return mod(a, M);
}

ll inv(ll x, ll y) {
    ll p = y;

    ll ax = 1;
    ll ay = 0;
    while (x > 0) {
        ll q = y / x;
        tie(ax, ay) = make_tuple(ay - q * ax, ax);
        tie(x, y) = make_tuple(y % x, x);
    }

    return mod(ay, p);
}

ll mdiv(ll x, ll y) {
    x = mod(x);
    y = mod(y);
    return mod(x * inv(y, M), M);
}


// Looping
#define rep(i, d, u) for(int i = d; i <= u; ++i)
#define dep(i, u, d) for(int i = u; i >= d; --i)

// Printing

template<typename T>
void print(const T& t) {
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void print(const T& t, const Args&... args) {
    std::cout << t << " ";
    print(args...);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        os << *it;
        if (it != vec.end() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for (const auto& item : s) {
        os << item << " ";
    }
    os << "}";
    return os;
}

// List manipulation
template<typename T>
vector<T> vslice(const vector<T>& v, int start=0, int end=-1) {
    int n = v.size();
    if (end == -1) {
        end = n;
    }
    int len = end - start;
    vector<T> result(len);
    for (int i = 0; i < len; i++) {
        result[i] = v[start + i];
    }
    return result;
}

template<typename Container, typename T>
bool contains(const Container& c, const T& value) {
    return std::find(c.begin(), c.end(), value) != c.end();
}

bool all(std::vector<bool> v) {
    return std::all_of(v.begin(), v.end(), [](bool b){ return b; });
}

bool any(std::vector<bool> v) {
    return std::any_of(v.begin(), v.end(), [](bool b){ return b; });
}

template <typename T, typename F>
void sort_vec(vector<T>& v, F key) {
    sort(v.begin(), v.end(), [&](const T& a, const T& b) {
        return key(a) < key(b);
    });
}
int n,a[100005];
vector<int> e[100005];
set<int> s[100005],stmp;
int ans=0,sid[100005],stp=0;
bool cmp(int x,int y)
{
	return (int)s[sid[x]].size()>(int)s[sid[y]].size();
}
void set_xor(int x,int y)
{
	stmp.clear();
	set<int>::iterator it=s[x].begin();
	while(it!=s[x].end())
	stmp.insert(y^(*(it++)));
	s[x]=stmp;
	return ;
}
void dfs(int u,int f)
{
	vector<int> v;
	for(int i=0;i<(int)e[u].size();i++)
	if(e[u][i]!=f)
	{
		dfs(e[u][i],u);
		v.push_back(e[u][i]);
	}
	if((int)v.size()==0)
	{
		sid[u]=(++stp);
		s[sid[u]].insert(0);
		return ;
	}
	sort(v.begin(),v.end(),cmp);

    print("Exploring node", u, "sorted children", v);
    for (auto child : v) {
        print("\t", child, ":", s[sid[child]]);
    }

	int hv_tg=a[v[0]];
	a[v[0]]=0;
	a[u]^=hv_tg;
	bool flg=false;
	set<int> setchk;
	for(int i=1;i<(int)v.size();i++)
	{
		int x=v[i];
		set_xor(sid[x],a[x]^hv_tg);
		set<int>::iterator it=s[sid[x]].begin();
		while(it!=s[sid[x]].end())
		{
			int val=(*it); it++;
			if(s[sid[v[0]]].find(val)!=s[sid[v[0]]].end())
			flg=true;
			if(setchk.find(val)!=setchk.end())
			flg=true;
			setchk.insert(val);
		}
	}
	if(flg==false)
	{
		//cout<<"Node "<<u<<" "<<(int)v.size()-1<<endl;
		ans+=(int)v.size()-1;
		for(int i=1;i<(int)v.size();i++)
		{
			int x=v[i];
			set<int>::iterator it=s[sid[x]].begin();
			while(it!=s[sid[x]].end())
			s[sid[v[0]]].insert(*(it++));
		}
		sid[u]=sid[v[0]];
		return ;
	}
	map<int,int> h;
	for(int i=0;i<(int)v.size();i++)
	{
		int x=v[i];
		set<int>::iterator it=s[sid[x]].begin();
		while(it!=s[sid[x]].end())
		h[*(it++)]++;
	}
	sid[u]=(++stp);
	int mx_app=0;
	map<int,int>::iterator it=h.begin();
	while(it!=h.end())
	{
		pair<int,int> p=(*it);
		if(p.second>mx_app)
		{
			mx_app=p.second;
			s[sid[u]].clear();
		}
		if(p.second==mx_app)
		s[sid[u]].insert(p.first);
		it++;
	}
	ans+=(int)v.size()-mx_app;
	return ;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	set_xor(sid[1],a[1]);
	if(s[sid[1]].find(0)==s[sid[1]].end())
	ans++;
	printf("%d\n",ans);
	return 0;
}