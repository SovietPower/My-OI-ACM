/*
4704kb	168ms
$Description$
求一棵仙人掌的最大独立集。
$Solution$
如果是树，那么f[i][0/1]表示当前点不取/取的最大独立集大小，直接DP即可，即 f[x][0]+=max(f[v][0],f[v][1]), f[x][1]+=f[v][0]。
对于环，枚举环的根选不选(BZOJ1040 骑士)，单独在上面做个DP即可。

也可以Tarjan+vector，以及建圆方树来方便环的转移（改一下方点f的定义使圆点可以直接转移即可）。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5e4+5,M=120010;

int n,m,Enum,H[N],nxt[M],to[M],Index,dfn[N],low[N],fa[N],f[N][2],tmp[N][2];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DP(int u,int v)
{
	tmp[v][0]=f[v][0], tmp[v][1]=f[v][1];//don't choose u
	for(int i=fa[v],pre=v; pre!=u; pre=i,i=fa[i])
		tmp[i][0]=std::max(tmp[pre][0],tmp[pre][1])+f[i][0],
		tmp[i][1]=tmp[pre][0]+f[i][1];
	f[u][0]=tmp[u][0];

	tmp[v][0]=f[v][0], tmp[v][1]=-87654321;//choose u
	for(int i=fa[v],pre=v; pre!=u; pre=i,i=fa[i])
		tmp[i][0]=std::max(tmp[pre][0],tmp[pre][1])+f[i][0],
		tmp[i][1]=tmp[pre][0]+f[i][1];
	f[u][1]=tmp[u][1];
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++Index, f[x][0]=0, f[x][1]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x])
		{
			if(!dfn[v=to[i]]) fa[v]=x, Tarjan(v), low[x]=std::min(low[x],low[v]);
			else low[x]=std::min(low[x],dfn[v]);
			if(low[v]>dfn[x]) f[x][0]+=std::max(f[v][0],f[v][1]), f[x][1]+=f[v][0];
		}
	for(int i=H[x]; i; i=nxt[i])
		if(fa[to[i]]!=x&&dfn[to[i]]>dfn[x]) DP(x,to[i]);
}

int main()
{
	n=read(),m=read();
	while(m--) AddEdge(read(),read());
	Tarjan(1);
	int res=0; for(int i=1; i<=n; ++i) res=std::max(res,std::max(f[i][0],f[i][1]));
	printf("%d",res);
	return 0;
}
