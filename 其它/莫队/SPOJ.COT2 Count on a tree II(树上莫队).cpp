/*
在DFS序做莫队 
当一个点不是另一个点的LCA时，需要加上它们LCA的贡献 
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=5e4+5,M=1e5+5,MAXIN=2e6;

int n,m,size,Enum,H[N],nxt[N<<1],to[N<<1],dep[N],fa[N],top[N],son[N],sz[N];
int Now,Ans[M],seq[N<<1],in[N],out[N],id,A[N],ref[N],cnt,tm[N];
//char IN[MAXIN],*SS=IN,*TT=IN;
bool vis[N];
struct Ques
{
	int l,r,lca,id;
	bool operator <(const Ques &a)const{
		return l/size<a.l/size?r<a.r:l/size<a.l/size;
	}
}q[M];

//inline int read()
//{
//	int now=0,f=1;register char c=gc();
//	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
//	for(;isdigit(c);now=now*10+c-'0',c=gc());
//	return now*f;
//}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]>=x) r=mid;
		else l=mid+1;
	return l;
}
void Discrete()
{
//	for(int i=1; i<=n; ++i) A[i]=ref[i]=read();
	for(int i=1; i<=n; ++i) scanf("%d",&A[i]),ref[i]=A[i];
	std::sort(ref+1,ref+1+n);
	cnt=1;
	for(int i=2; i<=n; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i]);
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
//	n=read(),m=read();
	scanf("%d%d",&n,&m);
	Discrete();
//	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v);
	for(int u,v,i=1; i<n; ++i) scanf("%d%d",&u,&v),AddEdge(u,v);
	Pre_DFS(1), DFS2(1,1);
	for(int u,v,w,i=1; i<=m; ++i)
	{
//		u=read(),v=read(),w=Query_LCA(u,v);
		scanf("%d%d",&u,&v),w=Query_LCA(u,v);
		q[i].id=i;//这要在continue前面。。
		if(u==v) {q[i].lca=-1; continue;}
		if(in[u]>in[v]) std::swap(u,v);
		if(w==u) q[i].l=in[w],q[i].r=in[v],q[i].lca=0;//这部分的LCA不能和u=v时用一样的！ 
//		else if(w==v) q[i].r=in[w],q[i].r=in[u],q[i].lca=0;
		else q[i].l=out[u],q[i].r=in[v],q[i].lca=in[w];//in[w] not w!
	}
	size=sqrt(id), std::sort(q+1,q+1+m);
	for(int l=1,r=0,i=1; i<=m; ++i)
		if(q[i].lca==-1) Ans[q[i].id]=1;
		else
		{
			while(l<q[i].l) Calc(seq[l++]);
			while(l>q[i].l) Calc(seq[--l]);
			while(r<q[i].r) Calc(seq[++r]);
			while(r>q[i].r) Calc(seq[r--]);
			if(q[i].lca) Calc(seq[q[i].lca]);//seq[in[lca]] not in[lca]!
			Ans[q[i].id]=Now;
			if(q[i].lca) Calc(seq[q[i].lca]);
		}
	for(int i=1; i<=m; ++i) printf("%d\n",Ans[i]);

	return 0;
}
