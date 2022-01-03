/*
6492kb	376ms
多次询问求仙人掌上两点间的最短路径。
如果是在树上，那么求LCA就可以了。
先做着，看看能不能把它弄成树。
把仙人掌看作一个图(实际上就是)，求一遍根节点到每个点的最短路dis[i]。
对于u,v，若w=LCA(u,v)不在环上(u,v不同在一个环)，那么dis(u,v)可以像在树上一样直接求得。
若w=u||w=v，(且w不是环内的一个点)，dis(u,v)=dis[u/v]-dis[w]。
如果w在环上，那么设x,y为u,v往上能到的最近的环上的两个点，那么dis(u,v)=dis[u]-dis[x]+dis[v]-dis[y]+(x,y在环上的最短距离)。
设cdis[i]为按DFS序得到的根节点到i的距离，len[i]为环i的长，x,y在环上的最短距离就是min(abs(cdis[x]-cdis[y]),len[bel]-abs(cdis[x]-cdis[y]))。
怎么把它弄成一棵树 求LCA？
所有在一个环上的点以这个环深度最小的点作为父节点，由父节点向子节点连边就行了。之前缩一下点。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=1e4+5,M=2e5+5;

int n,m,Q,Enum,H[N],nxt[M<<1],to[M<<1],val[M<<1],dis[N],cnt,bel[N],len[N],cdis[N],dep[N],fa[N][16];
std::priority_queue<pr> q;
bool vis[N],vis2[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void Dijkstra()
{
	memset(dis,0x3f,sizeof dis);
	dis[1]=0, q.push(mp(0,1));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis2[x]) continue;
		vis2[x]=1;
		for(int i=H[x]; i; i=nxt[i])
			if(dis[to[i]]>dis[x]+val[i])
				dis[to[i]]=dis[x]+val[i], q.push(mp(-dis[to[i]],to[i]));
	}
}
void DFS(int x)
{
	vis[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x][0]&&!bel[to[i]])
			if(!vis[v=to[i]]) fa[v][0]=x,cdis[v]=cdis[x]+val[i],dep[v]=dep[x]+1,DFS(v);
			else{//find a circle v
				len[++cnt]=cdis[x]-cdis[v]+val[i];
				for(int j=x,pre; j!=v; j=pre)
					bel[j]=cnt, pre=fa[j][0], fa[j][0]=v;
				//不给bel[v]赋值，因为v可能作为多个环的交点。
			}
}
void Init_LCA()
{
	for(int x=2; x<=n; ++x)
//		for(int i=1; i<16&&dep[x]>=(1<<i); ++i)
		for(int i=1; i<16; ++i)
			fa[x][i]=fa[fa[x][i-1]][i-1];
}
void Query_LCA(int &u,int &v)
{
	if(dep[u]<dep[v]) std::swap(u,v);
	for(int i=15; ~i; --i)
		if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];//这样dep[1]=1！
	if(u==v) return;
	for(int i=15; ~i; --i)
		if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
//	u=fa[u][0], v=fa[v][0];
}
void DFS_for_Deep(int x){
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x][0]) dep[to[i]]=dep[x]+1, DFS_for_Deep(to[i]);
}

int main()
{
	n=read(),m=read(),Q=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v,read());
	Dijkstra(), DFS(1);
	Enum=0, memset(H,0,sizeof H);
	for(int i=2; i<=n; ++i) AddEdge(fa[i][0],i,0);
	dep[1]=1, DFS_for_Deep(1)/*在新树上得到dep啊。。*/, Init_LCA();
	int u,v,x,y,l;
	while(Q--)
	{
		u=read(),v=read(),Query_LCA(x=u,y=v);//此时的x,y若在环上，则是最接近u,v的环上的点(再往上跳一步就是LCA，环深度最低的点) 
		if(x!=y && bel[x] && bel[x]==bel[y])//x!=y即u,v不是在一条链上 //注意判bel[x]!=0！ 
			printf("%d\n",dis[u]+dis[v]-dis[x]-dis[y]+std::min(std::abs(cdis[x]-cdis[y]),len[bel[x]]-std::abs(cdis[x]-cdis[y])));
		else if(x==y) printf("%d\n",dis[u]+dis[v]-(dis[x]<<1));
		else printf("%d\n",dis[u]+dis[v]-(dis[fa[x][0]]<<1));//不在一个环上也直接更新。
	}
	return 0;
}
