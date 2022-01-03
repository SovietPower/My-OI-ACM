/*
733ms	142800KB
$Description$
给定一棵$n$个点的树。$q$次询问，每次询问给定$v,l,r$，求离$v$最近且DFS序在$[l,r]$之间的叶节点是哪个。
$n,q\leq5\times10^5$。

$Solution$
把询问离线。
在树上走，每次从$fa[x]$走到$x$时，设边权为$len$。此时距离$x$子树外的点的距离会增加$len$，距离$x$子树内的点的距离会减少$len$，同时这都是一段连续区间。（也可以对子树内减少$2\times len$，对所有点加上$len$）
所以建一棵线段树就做完了= =。
复杂度$O((n+q)\log n)$。

就算$INF$把$n$条边的边权全加上也爆不了`long long`啊，我有点傻逼→_→（当然转成一次区间减也不会有这个问题）
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5e5+5;
const LL INF=1ll<<60;

int n,Enum,H[N],nxt[N],len[N],fa[N],sz[N];
LL dep[N],Ans[N];
struct Node{
	int l,r,id;
};
std::vector<Node> vec[N];
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	LL tag[S],mn[S];
	#undef S
	#define Upd(rt,v) tag[rt]+=v, mn[rt]+=v
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {mn[rt]=H[l]?INF:dep[l]; return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Upd(rt,v); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
		Update(rt);
	}
	LL Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mn[rt];
		if(tag[rt]) PushDown(rt);
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
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v, sz[u]+=sz[v];
}
void DFS(int x)
{
	static int now=0;
	static LL offset=0;

	int pos=++now;
	if(x!=1) offset+=len[x], T.Modify(1,n,1,pos,pos+sz[x]-1,-2*len[x]);

	for(int i=0,l=vec[x].size(); i<l; ++i)
		Ans[vec[x][i].id]=T.Query(1,n,1,vec[x][i].l,vec[x][i].r)+offset;
	for(int v=H[x]; v; v=nxt[v]) DFS(v);

	if(x!=1) offset-=len[x], T.Modify(1,n,1,pos,pos+sz[x]-1,2*len[x]);
}

int main()
{
	int n=read(),q=read(); ::n=n;
	for(int i=2; i<=n; ++i) fa[i]=read(), dep[i]=dep[fa[i]]+(len[i]=read());
	for(int i=n; i>1; --i) ++sz[i], AE(fa[i],i);//increase ording
	++sz[1], T.Build(1,n,1);
	for(int i=1,p; i<=q; ++i) p=read(), vec[p].push_back((Node){read(),read(),i});
	DFS(1);
	for(int i=1; i<=q; ++i) printf("%I64d\n",Ans[i]);

	return 0;
}
