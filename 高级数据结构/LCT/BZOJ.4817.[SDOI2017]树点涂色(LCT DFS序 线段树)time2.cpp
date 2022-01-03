/*
14980kb	3456ms
对于操作二，输出$val[x]+val[y]-2*val[LCA(x,y)]+1$就可以了，不需要考虑$fa[LCA(x,y)]$。$x$的颜色会被计算两次，但应该一定是统计它一次。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int n,Enum,H[N],nxt[N<<1],to[N<<1],in[N],out[N],dep[N],fa[N],sz[N],son[N],top[N],A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int mx[S],tag[S];
	#undef S
	#define Upd(rt,v) mx[rt]+=v, tag[rt]+=v
	#define Update(rt) mx[rt]=std::max(mx[ls],mx[rs])
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {mx[rt]=A[l]; return;}
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
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mx[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(lson,L,R),Query(rson,L,R));
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
	int QueryP(int l,int r,int rt,int pos)
	{
		if(l==r) return mx[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		return pos<=m ? QueryP(lson,pos) : QueryP(rson,pos);
	}
	#undef ls
	#undef rs
	#undef lson
	#undef rson
	#undef Upd
	#undef Update
}T;

namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]
	int son[N][2],fa[N],L[N];

	inline void Init(const int n){
		for(int i=1; i<=n; ++i) L[i]=i;
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	inline void Update(int x){
		L[x]=lson?L[lson]:x;
	}
	void Rotate(int x)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(n_root(a)) son[b][son[b][1]==a]=x;
		if(son[x][r]) fa[son[x][r]]=a;
		fa[x]=b, fa[a]=x, son[a][l]=son[x][r], son[x][r]=a;
		Update(a);
	}
	void Splay(int x)
	{
		int a;
		while(n_root(x))
		{
			if(n_root(a=fa[x])) Rotate(son[a][0]==x^son[fa[a]][0]==a?x:a);
			Rotate(x);
		}
		Update(x);
	}
	void Access(int x)
	{
		for(int pre=0; x; x=fa[pre=x])
		{
			Splay(x);
			if(rson) T.Modify(1,n,1,in[L[rson]],out[L[rson]],1);//L!
			if(pre) T.Modify(1,n,1,in[L[pre]],out[L[pre]],-1);
			rson=pre;
		}
	}
}

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
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
	static int Index=0;
	A[in[x]=++Index]=dep[x];
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
			dep[v]=dep[x]+1, fa[v]=x, LCT::fa[v]=x, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
	out[x]=Index;
}
void DFS2(int x,int tp)
{
	top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x] && v!=son[x]) DFS2(v,v);
	}
}

int main()
{
	int n=read(),q=read(); ::n=n;
	for(int i=1; i<n; ++i) AE(read(),read());
	dep[1]=1, DFS1(1), DFS2(1,1), T.Build(1,n,1), LCT::Init(n);
	for(int x,y; q--; )
		switch(read())
		{
			case 1: LCT::Access(read()); break;
			case 2: x=read(), y=read(), printf("%d\n",T.QueryP(1,n,1,in[x])+T.QueryP(1,n,1,in[y])-(T.QueryP(1,n,1,in[LCA(x,y)])<<1)+1); break;
			case 3: x=read(), printf("%d\n",T.Query(1,n,1,in[x],out[x])); break;
		}

	return 0;
}
