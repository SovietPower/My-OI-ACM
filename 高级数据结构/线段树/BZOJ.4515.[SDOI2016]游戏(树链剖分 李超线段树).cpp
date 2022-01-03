/*
35240kb	9032ms
每次在路径上加的数是个一次函数，容易看出是树剖+李超线段树维护函数最小值。
横坐标自然是取个确定的距离标准。取每个点到根节点的距离$dis[i]$作为$i$的横坐标好了，这样对于同一条重链，横坐标还是递增的。
令$w=LCA(u,v)$。如果在$(u,v)$路径上加入直线$y=kx+b$：
对于在$u\to w$路径上的点，每个点$i$的横坐标就是$dis_u-dis_i$，所以对于$i$，$y=k(dis_u-dis_i)+b=-k\cdot dis_i+k\cdot dis_u+b$，依旧是原坐标系一条$k=-k,\quad b=k\cdot dis_u+b$的直线。所以直接树剖+线段树维护即可。
另一条$w\to v$的路径同理。
线段树的每个节点维护它以及它儿子中的最小值$mn[rt]$（每个节点维护的都是一条直线，所以最小值显然就在两端点中取）。
区间查询的时候，如果当前区间完全包含于询问区间，就直接返回$mn[rt]$；否则答案与当前点维护的线段两端点的函数值取个$\min$，继续递归即可。
这样区间修改+树剖的复杂度是$O(n\log^3n)$，你只要相信树剖+李超线段树的常数很小就好了。。
注意线段树里的下标都是$dis[ref[i]]$。
写的时候的错误：1. Modify中的m和mx别混用。。2. 就算是第一次覆盖区间也要与mn[rt]取min。3. 各种细节。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;
const LL INF=123456789123456789ll;

int n,H[N],Enum,nxt[N<<1],to[N<<1],len[N<<1],fa[N],dep[N],sz[N],son[N],top[N],dfn[N],ref[N];
LL dis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
//	int have[S];
	LL K[S],B[S],mn[S],Lx[S],Rx[S],Mx[S];
	#undef S
	#define Update(rt) mn[rt]=std::min(mn[rt],std::min(mn[ls],mn[rs]))
//	void Init(int n)
//	{
//		for(int i=n<<2; i; --i) mn[i]=INF;
//	}
	void Build(int l,int r,int rt)
	{
		B[rt]=mn[rt]=INF, Lx[rt]=dis[ref[l]], Rx[rt]=dis[ref[r]];
		if(l==r) return;
		int m=l+r>>1; Mx[rt]=dis[ref[m]], Build(lson), Build(rson);
	}
	void Modify(int l,int r,int rt,int L,int R,LL k,LL b)
	{
		if(L<=l && r<=R)
		{
			LL lx=Lx[rt],rx=Rx[rt],l0=K[rt]*lx+B[rt],r0=K[rt]*rx+B[rt],l1=k*lx+b,r1=k*rx+b;
//			if(!have[rt]) {have[rt]=1, K[rt]=k, B[rt]=b, mn[rt]=std::min(mn[rt],std::min(l1,r1)); return;}//当然要和当前节点取min啊！（由另一部分区间PushUp来的啊）
			if(l0<=l1 && r0<=r1) return;
			if(l1<=l0 && r1<=r0) {K[rt]=k, B[rt]=b, mn[rt]=std::min(mn[rt],std::min(l1,r1)); return;}//更新mn！
			int m=l+r>>1;//m不是mx。。
			LL mx=Mx[rt]; double p=1.0*(B[rt]-b)/(k-K[rt]);
			if(l0<l1)
				if(p<=(double)mx) Modify(lson,L,R,K[rt],B[rt]), K[rt]=k, B[rt]=b;
				else Modify(rson,L,R,k,b);
			else
				if(p<=(double)mx) Modify(lson,L,R,k,b);
				else Modify(rson,L,R,K[rt],B[rt]), K[rt]=k, B[rt]=b;
			mn[rt]=std::min(mn[rt],std::min(l1,r1)), Update(rt);//!
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,k,b);
		if(m<R) Modify(rson,L,R,k,b);
		Update(rt);
	}
	LL Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mn[rt];
		LL res=INF;
		if(B[rt]!=INF)
		{
			LL lx=std::max(l,L),rx=std::min(r,R);
			res=std::min(K[rt]*dis[ref[lx]],K[rt]*dis[ref[rx]])+B[rt];
		}
		int m=l+r>>1;
		if(L<=m) res=std::min(res,Query(lson,L,R));
		if(m<R) res=std::min(res,Query(rson,L,R));
		return res;
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AE(int w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, dis[v]=dis[x]+len[i], DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	static int Index=0;
	top[x]=tp, ref[dfn[x]=++Index]=x;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa[x]&&v!=son[x]) DFS2(v,v);
	}
}
void Modify(int u,int w,LL k,LL b)
{
	while(top[u]!=top[w])
		T.Modify(1,n,1,dfn[top[u]],dfn[u],k,b), u=fa[top[u]];
	T.Modify(1,n,1,dfn[w],dfn[u],k,b);
}
LL Query(int u,int v)
{
	LL res=INF;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
		res=std::min(res,T.Query(1,n,1,dfn[top[u]],dfn[u])), u=fa[top[u]];
	}
	if(dep[u]>dep[v]) std::swap(u,v);
	return std::min(res,T.Query(1,n,1,dfn[u],dfn[v]));
}

int main()
{
	n=read(); int m=read();
	for(int i=1; i<n; ++i) AE(read(),read(),read());
	DFS1(1), DFS2(1,1), T.Build(1,n,1);
	for(int i=1; i<=m; ++i)
		switch(read())
		{
			case 1:
			{
				int u=read(),v=read(),w=LCA(u,v),k=read(),b=read();
				Modify(u,w,-k,dis[u]*k+b), Modify(v,w,k,(dis[u]-(dis[w]<<1))*k+b);
				break;
			}
			case 2: printf("%lld\n",Query(read(),read())); break;
		}

	return 0;
}
