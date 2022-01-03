#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+7;

int n,ref[N],val[N],cnt[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
//	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
//	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	n=read(); LL sum=0;
	for(int i=1; i<=n; ++i) ref[i]=val[i]=read(), sum+=val[i];
	for(int i=1; i<n; ++i) AddEdge(read(),read());

	std::sort(ref+1,ref+1+n); int t=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++t]=ref[i];
	for(int i=1; i<=n; ++i) ++cnt[val[i]=Find(val[i],t)];

	LL ans=1e16;
	for(int i=1; i<=t; ++i)
		ans=std::min(ans,1ll*(n-cnt[i])*ref[i]+sum-1ll*cnt[i]*ref[i]);
	printf("%lld\n",ans);

	return 0;
}
