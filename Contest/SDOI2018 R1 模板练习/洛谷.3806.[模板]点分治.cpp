#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e4+5,S=1e7+5;

int n,m,Enum,root,Min,sz[N],H[N],to[N<<1],nxt[N<<1],val[N<<1],D[N],que[N],Q[105],Ans[105];
bool vis[N],exist[S];//bitsetËæ±ãÓÃ»á¸üÂý¡£¡£

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], val[Enum]=w, H[v]=Enum;
}
void Get_root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=f)
		{
			Get_root(v,x,tot), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx,root=x;
}
void DFS(int x,int f,int d)
{
	D[++D[0]]=d;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]] && to[i]!=f) DFS(to[i],x,d+val[i]);
}
void Calc(int x,int val)
{
	D[0]=0, DFS(x,x,val);
	for(int i=1; i<=D[0]; ++i)
		for(int j=1; j<=m; ++j)
			if(Q[j]>=D[i]) Ans[j]|=exist[Q[j]-D[i]];
	for(int i=1; i<=D[0]; ++i)
		exist[D[i]]=1,que[++que[0]]=D[i];
}
void Solve(int x)
{
	vis[x]=1, que[0]=0, exist[0]=1/*!*/;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) Calc(to[i],val[i]);
	for(int i=1; i<=que[0]; ++i) exist[que[i]]=0;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
			Min=N, Get_root(to[i],x,sz[to[i]]), Solve(root);
}

int main()
{
	n=read(),m=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v,read());
	for(int i=1; i<=m; ++i) Q[i]=read();
	Min=N, Get_root(1,1,n), Solve(root);
	for(int i=1; i<=m; ++i) puts(Ans[i]?"AYE":"NAY");

	return 0;
}
