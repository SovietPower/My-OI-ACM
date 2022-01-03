/*
代码正确性不保证。。
在DFS序做莫队 
当一个点不是另一个点的LCA时，需要加上它们LCA的贡献 
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=4e5+5,M=1e5+5;

int n,m,size,Enum,H[N],nxt[N<<1],to[N<<1],dep[N],fa[N],top[N],son[N],sz[N];
int Now,Ans[M],seq[N<<1],in[N],out[N],id,A[N],tm[N];
bool vis[N];
struct Ques
{
	int l,r,lca,id,x,y;
	bool operator <(const Ques &a)const{
		return l/size<a.l/size?r<a.r:l/size<a.l/size;
	}
}q[M];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void Pre_DFS(int x)
{
	in[x]=++id, seq[id]=x, sz[x]=1;
	int mx=0;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, Pre_DFS(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v],son[x]=v;
		}
	out[x]=++id, seq[id]=x;
}
void DFS2(int x,int tp)
{
	top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x]&&to[i]!=son[x])
				DFS2(to[i],to[i]);
	}
}
int Query_LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]>dep[y]?y:x;
}
void Calc(int p)
{
	if(vis[p])
		if(!--tm[A[p]]) --Now;
		else ;
	else if(++tm[A[p]]==1) ++Now;
	vis[p]^=1;
}

int main()
{
	n=read(),m=read(),size=sqrt(n<<1);
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int u,v,i=1; i<=n; ++i) u=read(),v=read(),AddEdge(u,v);
	Pre_DFS(0), DFS2(0,0);
	for(int u,v,w,i=1; i<=m; ++i)
	{
		u=read(),v=read(),w=Query_LCA(u,v),q[i].x=read(),q[i].y=read();
		q[i].id=i;
		if(u==v) {Ans[i]=1; continue;}
		if(in[u]>in[v]) std::swap(u,v);
		if(w==u) q[i].l=in[w],q[i].r=in[v],q[i].lca=0;
//		else if(w==v) q[i].r=in[w],q[i].r=in[u],q[i].lca=0;
		else q[i].l=out[u],q[i].r=in[v],q[i].lca=in[w];
	}
	std::sort(q+1,q+1+m);
	tm[0]=N;
	for(int l=1,r=0,i=1; i<=m; ++i)
		if(!Ans[q[i].id])
		{
			while(l<q[i].l) Calc(seq[l++]);
			while(l>q[i].l) Calc(seq[--l]);
			while(r<q[i].r) Calc(seq[++r]);
			while(r>q[i].r) Calc(seq[r--]);
			if(q[i].lca) Calc(q[i].lca);
			if(tm[q[i].x]&&tm[q[i].y]&&q[i].x&&q[i].y) Ans[q[i].id]=Now-1;
			else Ans[q[i].id]=Now;
			if(q[i].lca) Calc(seq[q[i].lca]);
		}
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
