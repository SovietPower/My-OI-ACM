/*
5592kb	1028ms
题意：求哪些点一定在最大匹配中。
再写一遍吧。
求哪些点不一定在最大匹配中。首先求一遍最大匹配，未匹配点当然不一定在最大匹配中。
设一个未匹配点为A，如果存在边A-B，且存在匹配边B-C，那么可以A替换C，即匹配边变成A-B。最大匹配数不会改变。
所以C，也就是与未匹配点相邻的点的匹配点，不一定在最大匹配中。
这样DFS一遍就行了，这儿的复杂度是$O(n+m)$。
求最大匹配的时候，匈牙利不是$O(nm)$吗，竟然能过么。。还是写一遍网络流（Dinic是$O(sqrt(n)m)$吧，ISAP呢？）。
ISAP这么慢的么==~~（虽然也是前15吧）~~。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=2e4+5,M=2e5+7+N+N/*边数*/,INF=2e9;

int S,T,Enum,H[N],nxt[M],fr[M],to[M],cap[M],pre[N],lev[N],lk[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	static int q[N];
	for(int i=S; i<T; ++i) lev[i]=T+1;
	int h=0,t=1; q[0]=T,lev[T]=0;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==T+1&&cap[i^1])
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[S]<=T;
}
inline int Augment()
{
	for(int i=T; i!=S; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1];
	return 1;
}
int ISAP()
{
	static int cur[N],num[N];
	if(!BFS()) return 0;
	int res=0,x=S;
	for(int i=S; i<=T; ++i) cur[i]=H[i],++num[lev[i]];
	while(lev[S]<=T)
	{
		if(x==T) res+=Augment(),x=S;
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=T;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=S) x=fr[pre[x]];
		}
	}
	return res;
}
void DFS(int x)
{
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[lk[to[i]]]) DFS(lk[to[i]]);
}

int main()
{
	int n=read(),m=read(),k=read(); Enum=1, S=0, T=n+m+1;
	for(int i=1; i<=n; ++i) AE(S,i,1);
	for(int i=1; i<=m; ++i) AE(i+n,T,1);
	int beg=Enum;
	for(int u; k--; ) u=read(), AE(u,read()+n,1);

	ISAP();
	for(int i=beg+1; i<=Enum; i+=2)
		if(!cap[i]) lk[fr[i]]=to[i], lk[to[i]]=fr[i];
	vis[0]=1;
	for(int i=1; i<=n+m; ++i) if(!lk[i]&&!vis[i]) DFS(i);
	for(int i=1; i<=n; ++i) if(!vis[i]) printf("%d\n",i);
	for(int i=1; i<=m; ++i) if(!vis[i+n]) printf("%d\n",i);

	return 0;
}
