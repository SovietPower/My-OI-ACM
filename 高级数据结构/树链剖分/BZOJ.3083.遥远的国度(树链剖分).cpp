/*
15420kb	2276ms（我的树剖常数还是挺小的233）
除了换根外，其余操作都是树剖模板。
初始时任意找一点为根DFS，并记此时的树为原树T。链修改显然不受换根影响。
若当前根为rt，查询x子树，有三种情况：
1. x=rt，则x子树为整棵树。
2. rt在 x在T中的子树 外，则此时x的子树就是x在T中的子树。
3. rt在 x在T中的子树 内，则除了rt所在的这棵x的子树，其余子树都是x的子树（可以用倍增/树剖找到这棵x的子树）。
前两种情况仍对应线段树上一段连续的区间，第三种则是[1,n]除去rt的子树得到的两段连续区间。直接线段树即可。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,INF=0x7fffffff;

int n,Enum,H[N],nxt[N<<1],to[N<<1],val[N],fa[N],dep[N],sz[N],son[N],top[N],in[N],Index,ref[N],out[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int A[N],cov[S],mn[S];
	#undef S

	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	#define Cov(rt,v) cov[rt]=v, mn[rt]=v
	inline void PushDown(int rt)
	{
		Cov(ls,cov[rt]), Cov(rs,cov[rt]), cov[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {mn[rt]=A[l]; return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Cov(rt,v); return;}
		if(cov[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mn[rt];
		if(cov[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::min(Query(lson,L,R),Query(rson,L,R));
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
inline int Jump(int u,int lca)
{
	int las=u;
	while(top[u]!=top[lca]) u=fa[las=top[u]];
	return u==lca?las:ref[in[lca]+1];
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int tp)
{
	top[x]=tp, T.A[in[x]=++Index]=val[x], ref[Index]=x;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x]&&v!=son[x]) DFS2(v,v);
	}
	out[x]=Index;
}
void ModifyPath(int val,int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
		T.Modify(1,n,1,in[top[u]],in[u],val), u=fa[top[u]];
	}
	if(dep[u]<dep[v]) std::swap(u,v);
	T.Modify(1,n,1,in[v],in[u],val);
}
int QueryTree(int x,int rt)
{
	if(x==rt) return T.mn[1];
	if(in[x]<=in[rt] && in[rt]<=out[x])
	{
		int w=Jump(rt,x);
		return std::min(in[w]>1?T.Query(1,n,1,1,in[w]-1):INF,out[w]<n?T.Query(1,n,1,out[w]+1,n):INF);
	}
	else return T.Query(1,n,1,in[x],out[x]);
}

int main()
{
	n=read(); int Q=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	for(int i=1; i<=n; ++i) val[i]=read();
	int rt=read(); DFS1(rt), DFS2(rt,rt), T.Build(1,n,1);
	for(int opt; Q--; )
	{
		if((opt=read())==1) rt=read();
		else if(opt==2) ModifyPath(read(),read(),read());
		else printf("%d\n",QueryTree(read(),rt));
	}
	return 0;
}
