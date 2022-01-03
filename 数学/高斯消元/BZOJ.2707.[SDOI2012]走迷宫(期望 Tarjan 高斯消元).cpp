/*
21136kb	5168ms
$Description$
给定一张有向图，从S随机游走，输出到T的期望步数（可能无穷大）。
$n\leq 10^4,\ m\leq 10^6$，保证每个强连通分量大小$\leq 100$。
$Solution$
一个点到达终点的期望步数 $E_i=\sum_{(i,j)\in G}\frac{E_j+1}{out[i]}$，$out[i]$为点$i$的出度。
那么对于一个DAG可以直接在反向图上拓扑+DP求解。
于是对于环内高斯消元，缩点后拓扑+DP。
无解(无限步)的情况: 起点到不了终点；起点能够走到一个环，且在这个环内无法走到终点(走不出去)。
ps:1.T连出的边不能计算。
2.期望的计算式有个+1！
3.建反向边！
4.重边 
**注：**
如果$E_i$表示从起点到点$i$的期望步数，那么起点可能多次到达点$i$，$E_i$这个值就。。（可以就直接拿起点做例子？）
如果$E_i$表示到达终点的期望步数就没有这个问题。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1e4+5,M=1e6+5;

int n,m,S,T,Enum,H[N],to[M],nxt[M],_H[N],_to[M],_nxt[M],in[N],q[N];
int tot,bel[N],scc[N][103],num[N],sz[N],Index,dfn[N],low[N],sk[N],top;
double A[105][105],E[N],out[N];
bool vis[N],vis_s[N],exist[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	_to[Enum]=u, _nxt[Enum]=_H[v], _H[v]=Enum;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++Index, sk[++top]=x, exist[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!dfn[to[i]]) Tarjan(to[i]),low[x]=std::min(low[x],low[to[i]]);
		else if(exist[to[i]]) low[x]=std::min(low[x],dfn[to[i]]);
	if(dfn[x]==low[x])
	{
		++tot;
		do
		{
			bel[sk[top]]=tot, num[sk[top]]=sz[tot],
			scc[tot][sz[tot]++]=sk[top], exist[sk[top--]]=0;
		}while(sk[top+1]!=x);
	}
}
void DFS(int x)
{
	vis[x]=vis_s[bel[x]]=1;
	if(x==T) return;//有没有都行 
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) /*++in[bel[x]],//Wrong*/DFS(to[i]);
}
void Gauss(int n)
{
	for(int j=0; j<n; ++j)
	{
		int mxrow=j;
		for(int i=j+1; i<n; ++i)
			if(fabs(A[i][j])>fabs(A[mxrow][j])) mxrow=i;
		if(mxrow!=j) for(int k=0; k<=n; ++k) std::swap(A[mxrow][k],A[j][k]);
		for(int i=j+1; i<n; ++i)
			if(A[i][j])
			{
				double t=A[i][j]/A[j][j];
				for(int k=j; k<=n; ++k)
					A[i][k]-=A[j][k]*t;
			}
	}
	for(int i=n-1; ~i; --i)
	{
		for(int j=i+1; j<n; ++j) A[i][n]-=A[i][j]*A[j][n];
		A[i][n]/=A[i][i];
	}
}

int main()
{
	n=read(),m=read(),S=read(),T=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),out[u]+=1.0,AddEdge(u,v);
	for(int i=1; i<=n; ++i)
		if(!dfn[i]) Tarjan(i);
	DFS(S);
	if(!vis[T]) {puts("INF"); return 0;}
	for(int x=1; x<=n; ++x)
		for(int i=H[x]; i; i=nxt[i])
			if(bel[x]!=bel[to[i]]) ++in[bel[x]];//反向图上的入度+1。
	for(int i=1; i<=tot; ++i)
		if(vis_s[i]&&!in[i]&&bel[T]!=i) {puts("INF"); return 0;}
	for(int i=1; i<=n; ++i) out[i]=1.0/out[i];
	int h=0,t=0;
	q[t++]=bel[T];
//	for(int i=1; i<=tot; ++i)
//		if(!in[i]) q[t++]=i;//in[]=0的只能是bel[T].
	while(h<t)
	{
		int now=q[h++];
		memset(A,0,sizeof A);
		for(int j=0; j<sz[now]; ++j)
		{
			int x=scc[now][j];
			A[j][j]=1.0, A[j][sz[now]]=E[x]/*之前加上的*/;
			if(x==T) continue;//不计算终点连出的边！
			for(int i=H[x]; i; i=nxt[i])
				if(bel[to[i]]==now){
					A[j][sz[now]]+=out[x],//步数+1.
					A[j][num[to[i]]]-=out[x];//是点的出度不是in[]! //-=不能直接赋值=：有重边！
				}
		}
		Gauss(sz[now]);
		for(int j=0; j<sz[now]; ++j)
		{
			int x=scc[now][j];
			E[x]=A[j][sz[now]];
			for(int i=_H[x]; i; i=_nxt[i])
				if(bel[_to[i]]!=now){
					if(!--in[bel[_to[i]]]) q[t++]=bel[_to[i]];
					E[_to[i]]+=(E[x]+1)*out[_to[i]];
				}
		}
	}
	printf("%.3lf",E[S]);

	return 0;
}
