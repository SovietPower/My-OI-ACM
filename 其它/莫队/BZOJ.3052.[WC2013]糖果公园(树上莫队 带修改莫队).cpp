//67376kb	27280ms
//树上莫队+带修改莫队 模板题 
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 400000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=1e6+3;

int n,m,Enum,H[N],nxt[N<<1],to[N<<1],val[M],W[N],col[N],las[N],tm[M];
int fa[N],dep[N],sz[N],son[N],top[N],Index,in[N],out[N],seq[N<<1];
LL Now,Ans[M];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Queries
{
	int l,r,lca,bl,br,tm,id;
	bool operator <(const Queries &x)const
	{
		if(bl!=x.bl) return bl<x.bl;//能优化15%？
		if(br!=x.br) return bl&1?br<x.br:br>x.br;
		return (bl^br)&1?tm<x.tm:tm>x.tm;
//		if(bl==x.bl) return br==x.br?tm<x.tm:br<x.br;
//		return bl<x.bl;
	}
}q[M];
struct Modify
{
	int pos,val,bef;
}qm[M];

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
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
			if(mx<sz[v]) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int tp)
{
	seq[in[x]=++Index]=x, top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x]&&to[i]!=son[x]) DFS2(to[i],to[i]);
	}
	seq[out[x]=++Index]=x;
}
void Calc(int p)
{
	vis[p] ? Now-=1ll*W[tm[col[p]]--]*val[col[p]] : Now+=1ll*W[++tm[col[p]]]*val[col[p]];
	vis[p]^=1;
}
void Change(int p,int v)
{
	if(vis[p]) Calc(p), col[p]=v, Calc(p);
	else col[p]=v;
}

int main()
{
	n=read(), m=read(); int Q=read();
	for(int i=1; i<=m; ++i) val[i]=read();
	for(int i=1; i<=n; ++i) W[i]=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	for(int i=1; i<=n; ++i) col[i]=las[i]=read();
	DFS1(1), DFS2(1,1);
	int qcnt=0, mcnt=0, size=pow(n,2.0/3.0);
	for(int i=1,x,y,w; i<=Q; ++i)
		if(!read()) qm[++mcnt]=(Modify){x=read(),y=read(),las[x]},las[x]=y;
		else
		{
			x=read(), y=read();
//			if(x==y) {q[++qcnt].lca=-1, Ans[qcnt]=...; continue;}
			w=LCA(x,y);
			if(in[x]>in[y]) std::swap(x,y);
			if(x==w) q[++qcnt]=(Queries){in[x],in[y],0,in[x]/size,in[y]/size,mcnt,qcnt};
			else q[++qcnt]=(Queries){out[x],in[y],w/*in[w]*/,out[x]/size,in[y]/size,mcnt,qcnt};
		}
	std::sort(q+1,q+1+qcnt);
	for(int i=1,t=0,l=1,r=0,ql,qr,qt; i<=qcnt; ++i)
	{
		ql=q[i].l, qr=q[i].r, qt=q[i].tm;
		while(t<qt) ++t,Change(qm[t].pos,qm[t].val);
		while(t>qt) Change(qm[t].pos,qm[t].bef),--t;
		if(ql==qr) {Ans[q[i].id]=1ll*val[col[seq[q[i].l]]]*W[1]; continue;}
		while(l<ql) Calc(seq[l++]);
		while(l>ql) Calc(seq[--l]);
		while(r<qr) Calc(seq[++r]);
		while(r>qr) Calc(seq[r--]);
		if(q[i].lca) Calc(q[i].lca);//Calc(seq[in[lca]]) = Calc(lca)
		Ans[q[i].id]=Now;
		if(q[i].lca) Calc(q[i].lca);
	}
	for(int i=1; i<=qcnt; ++i) printf("%lld\n",Ans[i]);

	return 0;
}
