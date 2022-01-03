/*
93ms	38500KB
$Description$
给定一张无向图。你可以任选两个点S,T(S≠T)作为起点终点，记v为S->T必须经过的边的数量，求最大的v。
(such that连用时such就是个代词啊)
$Solution$
圆方树缩环，方点与圆点之间的边边权为0，圆点之间的边边权为1，求直径。
不想在圆点间再建方点。。
官方题解：与答案有关的边一定是桥。把所有之间没有桥的点合并为1个点，建出一棵新树。求这棵树的直径。反正就这样了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=3e5+5;

int n,m,tot,Index,dfn[N],low[N],Max,V,top,sk[N];
struct Edge
{
	int Enum,H[N<<1],nxt[N<<2],to[N<<2],val[N<<2];//Square point...
	inline void AddEdge(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
	inline void AddTreeEdge(int u,int v,int w)
	{
		to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=w, H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], val[Enum]=w, H[v]=Enum;
	}
}G,T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Tarjan(int x,int f)
{
	low[x]=dfn[x]=++Index, sk[++top]=x;
	for(int i=G.H[x],v; i; i=G.nxt[i])
		if(!dfn[v=G.to[i]])
		{
			Tarjan(v,x), low[x]=std::min(low[x],low[v]);
			if(dfn[x]==low[v])
			{
				T.AddTreeEdge(x,++tot,0);
				do{
					T.AddTreeEdge(tot,sk[top--],0);
				}while(sk[top+1]!=v);
			}
			else if(dfn[x]<low[v]) T.AddTreeEdge(x,v,1), --top;//出栈！
		}
		else if(v!=f) low[x]=std::min(low[x],dfn[v]);
}
void DFS(int x,int f,int d)
{
	if(d>Max) Max=d, V=x;
	for(int i=T.H[x]; i; i=T.nxt[i])
		if(T.to[i]!=f) DFS(T.to[i],x,d+T.val[i]);
}

int main()
{
	tot=n=read(),m=read();
	for(int i=1; i<=m; ++i) G.AddEdge(read(),read());
	Tarjan(1,1);
	DFS(1,1,0), DFS(V,V,0);
	printf("%d",Max);

	return 0;
}
