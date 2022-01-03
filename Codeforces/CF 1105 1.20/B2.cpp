#include<bits/stdc++.h>
#define pr pair<int, int>
#define mp(x, y) make_pair(x, y)
#define fi first
#define se second
#define ull unsigned long long
#define LL long long
using namespace std;
const int N = 1e6 + 10, mod = 1e9 + 7, INF = 1e9 + 10;
template <typename A, typename B> inline bool chmin(A &a, B b)
{
	if(a > b)
	{
		a = b;
		return 1;
	}
	return 0;
}
template <typename A, typename B> inline bool chmax(A &a, B b)
{
	if(a < b)
	{
		a = b;
		return 1;
	}
	return 0;
}
template <typename A, typename B> inline LL add(A x, B y)
{
	if(x + y < 0) return x + y + mod;
	return x + y >= mod ? x + y - mod : x + y;
}
template <typename A, typename B> inline void add2(A &x, B y)
{
	if(x + y < 0) x = x + y + mod;
	else x = (x + y >= mod ? x + y - mod : x + y);
}
template <typename A, typename B> inline LL mul(A x, B y)
{
	return 1ll * x * y % mod;
}
template <typename A, typename B> inline void mul2(A &x, B y)
{
	x = (1ll * x * y % mod + mod) % mod;
}
template <typename A> inline void debug(A a)
{
	cout << a << '\n';
}
template <typename A> inline LL sqr(A x)
{
	return 1ll * x * x;
}
#define gc() getchar()
inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
int n, K;
ull ha[N], po[N], base = 27;
int cnt = 0, omg[N];
char s[N];
map<ull, std::vector<int> > mp;
int main()
{
	n = read();
	K = read();
	scanf("%s", s + 1);
	po[0] = 1;
	for(int i = 1; i <= n; i++) po[i] = po[i - 1] * base;
	for(int i = 1; i <= n; i++)
	{
		ha[i] = (ha[i - 1] + s[i]) * base;
		omg[s[i]]++;
		if(omg[s[i]] == 1) cnt++;
		if(i > K)
		{
			omg[s[i - K]]--;
			if(omg[s[i - K]] == 0) cnt--;
		}
		if(i >= K && cnt == 1) mp[ha[i] - ha[i - K] * po[i - (i - K + 1) + 1]].push_back(i);
	}
	int ans = 0;
	for(map<ull, std::vector<int> >::iterator it = mp.begin(); it != mp.end(); it++)
	{
		std::vector<int> t = (it -> se);
		int now = 0, r = 0;
		for(int i = 0; i < t.size(); i++)
			if((t[i] - K + 1) > r) now++, r = t[i];
		chmax(ans, now);
	}
	cout << ans;
	return 0;
}
