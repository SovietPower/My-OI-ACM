/*
218ms	32600KB
$Description$
给定一张$n$个点$m$条边的无向图，允许有自环重边。求最少加多少条边后，其存在从$1$出发最后回到$1$的欧拉回路。
注意，欧拉回路是指要经过所有边，无边（边包括自环）连向的孤立点不需要考虑。但是$1$一定要经过。
$n,m\leq10^6$。

$Solution$
如果图连通，奇度数点两两连边即可。
如果图不连通，对于每个奇度数点需要向外连一条边；没有奇度数点的连通块就随便找一个点往外连两条边。另外强制选$1$即可。
答案是统计的边数除以$2$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+6;

int Enum,H[N],nxt[N<<1],to[N<<1],fa[N],dgr[N],cnt[N];
bool tag[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<=n; ++i) fa[i]=i;
	tag[1]=1;
	for(int i=1,u,v; i<=m; ++i)
	{
		int r1=Find(u=read()),r2=Find(v=read());
		fa[r1]=r2, ++dgr[u], ++dgr[v], tag[u]=tag[v]=1;
	}
	for(int i=1; i<=n; ++i) cnt[Find(i)]+=dgr[i]&1;
	int ans=0,two=0,tot=0;
	for(int i=1; i<=n; ++i)
		if(tag[i] && Find(i)==i)
		{
			++tot;
			if(cnt[i]) ans+=cnt[i];
			else ++two;
		}
	printf("%d\n",tot==1?ans>>1:(ans>>1)+two);

	return 0;
}
