#include <set>
#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
typedef unsigned long long ull;
const int N=2e5+5;

int n,K,pw2[N];
ull pw1[N];
char s[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool Check(int x)
{
	static ull s1[N];
	static int s2[N];
	std::map<ull,int> mp1;
	std::map<int,int> mp2;
	for(int i=1; i<=n; ++i) s1[i]=s1[i-1]*131+s[i], s2[i]=1ll*s2[i-1]*1313%mod+s[i], Mod(s2[i]);
	for(int i=K; i<=n; ++i)
	{
		ull v1=s1[i]-s1[i-K]*pw1[K];
		int v2=(s2[i]+mod-1ll*s2[i-K]*pw2[K]%mod)%mod;
		++mp1[v1], ++mp2[v2];
		if(mp1[v1]>=x && mp2[v2]>=x) return 1;
	}
	return 0;
}

int main()
{
	n=read(), K=read(), scanf("%s",s+1);
	pw1[0]=1, pw2[0]=1;
	for(int i=1; i<=n; ++i) pw1[i]=pw1[i-1]*131, pw2[i]=1ll*pw2[i-1]*1313%mod;
	int l=0,r=n/K,mid,ans=0;
	while(l<=r)
		if(Check(mid=l+r>>1)) ans=mid, r=mid-1;
		else l=mid+1;
	printf("%d\n",ans);

	return 0;
}
