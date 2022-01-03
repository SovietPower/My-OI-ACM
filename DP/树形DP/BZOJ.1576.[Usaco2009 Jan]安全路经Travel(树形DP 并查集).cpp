/*
12680kb	556ms
先求最短路树。考虑每一条非树边(u,v,len)，设w=LCA(u,v)，这条边会对w->v上的点x(x!=w)有dis[u]+dis[v]-dis[x]+len的距离。
每条边用dis[u]+div[v]+len更新链。树剖就做完了。
因为每个点只需取最小值，所以把边按dis[u]+div[v]+len排序后并查集更新链也行。
复杂度$O(n*α(n)+mlogm)$。
树DP失败，好像没法处理子树内的ndis互相更新。。唉。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=1e5+5,M=4e5+5,INF=0x3f3f3f3f;

int n,fa[N],ff[N],Enum,H[N],nxt[M],to[M],len[M],dis[N],ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int u,v,w;
	bool operator <(const Edge &x)const{
		return w<x.w;
	}
}e[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int w,int u,int v)//order
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void Dijkstra()
{
	static bool vis[N];
	static std::priority_queue<pr> q;
	memset(dis,0x3f,sizeof dis);
	q.push(mp(dis[1]=0,1));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i])
				fa[v]=x, q.push(mp(-(dis[v]=dis[x]+len[i]),v));
	}
}
inline int Find(int x)
{
	return x==ff[x]?x:ff[x]=Find(ff[x]);	
}
void Update(int u,int v,int val)
{
	u=Find(u), v=Find(v);
	while(u!=v)
	{
		if(dis[u]<dis[v]) std::swap(u,v);//没必要用dep，保证在一条链上时上下不颠倒就行了 
		ans[u]=val-dis[u];
		u=ff[u]=Find(fa[u]);
	}
}

int main()
{
	n=read(), Enum=1;
	for(int m=read(),i=1; i<=m; ++i) AE(read(),read(),read());
	Dijkstra();
	int t=0;
	for(int i=2,lim=Enum; i<=lim; i+=2)
	{
		int u=to[i], v=to[i^1];
		if(fa[u]==v||fa[v]==u) continue;
		e[++t]=(Edge){u,v,dis[u]+dis[v]+len[i]};
	}
	std::sort(e+1,e+1+t);
	for(int i=1; i<=n; ++i) ff[i]=i;
	for(int i=1; i<=t; ++i) Update(e[i].u,e[i].v,e[i].w);
	for(int i=2; i<=n; ++i) printf("%d\n",ans[i]?ans[i]:-1);

	return 0;
}
