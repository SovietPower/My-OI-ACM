/*
5283ms	11.62M
$Description$
给定$n$，求$1\sim n$中的素数个数。
$2\leq n\leq10^{11}$。
$Solution$
Min_25筛。只需要求出$g(n,|P|)$。
*/
#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=317000<<1;

int cnt,P[N>>2],id1[N],id2[N];
LL g[N],w[N];
bool notP[N];

void Init(int n)
{
	notP[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!notP[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&i*P[j]<=n; ++j)
			if(notP[i*P[j]]=1,!(i%P[j])) break;
	}
}

int main()
{
	LL n; scanf("%lld",&n);
	int m=0,Sqr=sqrt(n+0.5); Init(Sqr);
	for(LL i=1,j; i<=n; i=j+1)
	{
		w[++m]=n/i, j=n/w[m];
		if(w[m]<=Sqr) id1[w[m]]=m;
		else id2[j]=m;
		g[m]=w[m]-1;
	}
	w[m+1]=-1;
	for(int j=1; j<=cnt; ++j)
	{
		int pj=P[j]; LL lim=1ll*pj*pj;
		for(int i=1; lim<=w[i]; ++i)
		{
			int k=w[i]/pj<=Sqr?id1[w[i]/pj]:id2[n/(w[i]/pj)];
			g[i]-=g[k]-j+1;
		}
	}
	printf("%lld\n",g[1]);

	return 0;
}
