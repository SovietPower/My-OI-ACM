/*
155ms	15800KB
$Description$
有一张n个点m条边的无向图，每个点有点权。图是安全的当且仅当所有边的两个端点权值不同。保证初始时图是安全的。
现在有权值为x的病毒，若它感染了某个点a，则该点点权变为a^x。
求有多少数对(S,x)，满足病毒的权值为x，且感染了S集合中的所有点后，满足图仍是安全的。
$Solution$
设一条边两个端点的权值为a,b，病毒权值为x。因为a≠b,a^x≠b^x，即对于某条边，病毒同时感染或同时不感染这条边是没事的。
而当且仅当x=a^b时，其感染某一个点，会出现不合法的情况。
于是可以对每条边设一个权值a^b。若病毒权值为某个ai^bi，则合法的感染点有n-(该权值的边形成的连通块数)(连通块看做一个共同的点)个，可以直接sort后并查集。
至于没出现过的某种权值，自然是有2^n种方案。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Mod(x) x>=mod&&(x-=mod)
#define mod 1000000007
typedef long long LL;
const int N=5e5+5;

LL A[N];
int pw[N],fa[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int u,v; LL w;
	Edge() {}
	Edge(int u,int v):u(u),v(v) {w=A[u]^A[v];}
	bool operator <(const Edge &x)const{
		return w<x.w;
	}
}e[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	int n=read(),m=read(),K=read();
	pw[0]=1;
	for(int i=1; i<=n; ++i) fa[i]=i, pw[i]=pw[i-1]<<1, Mod(pw[i]);

	for(int i=1; i<=n; ++i) A[i]=readll();
	for(int i=1; i<=m; ++i) e[i]=Edge(read(),read());

	std::sort(e+1,e+1+m);
	long long ans=0;
	int tot=0; e[m+1].w=-1;
	for(int i=1,cnt=n,las=1,u,v; i<=m; ++i)
	{
		if(Find(u=e[i].u)!=Find(v=e[i].v)) fa[fa[u]]=fa[v], --cnt;
		if(e[i].w!=e[i+1].w)
		{
			ans+=pw[cnt], cnt=n, ++tot;
			for(int j=las; j<=i; ++j)
				fa[e[j].u]=e[j].u, fa[e[j].v]=e[j].v;
			las=i+1;
		}
	}
	printf("%I64d\n",(ans+((1ll<<K)-tot)%mod*pw[n])%mod);

	return 0;
}
