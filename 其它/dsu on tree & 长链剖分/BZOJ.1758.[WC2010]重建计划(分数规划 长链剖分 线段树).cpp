/*
25192kb	9500ms
二分答案，然后判断是否存在一条长度在[L,R]的路径满足权值和非负。
考虑暴力DP，$f[i][j]$表示点$i$的子树中深度为$j$的路径权值的最大值。
显然可以长链剖分。因为每次匹配的长度是一个区间，所以可以用线段树维护。
复杂度$O(n\log n\log v)$。
然而线段树巨大的常数比用一堆vector的点分治还要慢。。但是我不会zkw。。
偏移重儿子$f$数组时$f$所有元素加的值（$tag$）（甚至整个$f$数组）其实不需要。。在线段树上的位置是对的，就直接用线段树上的节点值和dis就好了。
这就是后者的写法。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 150000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;
const double INF=1ll<<60;

int n,L,R,Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],mxd[N],son[N],w[N],pos[N];
double X;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int cnt,A[S],id[N];
	double mx[S];
	#undef S
	void Build(int l,int r,int rt)
	{
		A[++cnt]=rt;
		if(l==r) {id[l]=rt; return;}
		int m=l+r>>1; Build(lson), Build(rson);
	}
	void pre(int n)
	{
		Build(1,n,1);
	}
	inline void Init()
	{
		for(int i=1; i<=cnt; ++i) mx[A[i]]=-INF;
	}
	void Modify(int l,int r,int rt,int p,double v)
	{
		mx[rt]=std::max(mx[rt],v);
		if(l==r) return;
		int m=l+r>>1;
		p<=m?Modify(lson,p,v):Modify(rson,p,v);
//		Update(rt);
	}
	double Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return mx[rt];
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(lson,L,R),Query(rson,L,R));
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
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void DFS1(int x,int fa)
{
	int mx=-1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa) DFS1(v,x), mxd[v]>mx&&(mx=mxd[v],son[x]=v,w[x]=len[i]);
	mxd[x]=++mx;
}
void DFS2(int x,int fa)
{
	static int Index=0;
	pos[x]=++Index;
	if(son[x])
	{
		DFS2(son[x],x);
		for(int i=H[x],v; i; i=nxt[i])
			if((v=to[i])!=fa&&v!=son[x]) DFS2(v,x);
	}
}
bool Solve(int x,int fa,double dis)
{
	static double tmp[N];
	int px=pos[x]; T.Modify(1,n,1,px,dis);
	if(!son[x]) return 0;
	if(Solve(son[x],x,dis+w[x]-X)) return 1;
	if(mxd[x]>=L && T.Query(1,n,1,px+L,px+std::min(mxd[x],R))-dis>=0) return 1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa && v!=son[x])
		{
			if(Solve(v,x,dis+len[i]-X)) return 1;
			int pv=pos[v];
			for(int j=0; j<=mxd[v]; ++j)
			{
				tmp[j]=T.mx[T.id[pv+j]];//另一种写法，这不能是f[pos[v]+j]啊，这样f是dis不是dp数组啊。
				int l=std::max(0,L-j-1),r=std::min(mxd[x],R-j-1);
				if(l<=r && tmp[j]+T.Query(1,n,1,px+l,px+r)-dis*2>=0) return 1;
			}
			for(int j=0; j<=mxd[v]; ++j) T.Modify(1,n,1,px+j+1,tmp[j]);
		}
	return 0;
}
bool Check(double mid)
{
	T.Init(), X=mid; return Solve(1,1,0);
}

int main()
{
	n=read(),L=read(),R=read(); int mn=1e6,mx=0;
	for(int i=1,u,v,w; i<n; ++i) u=read(),v=read(),w=read(),AE(u,v,w),mn=std::min(mn,w),mx=std::max(mx,w);
	DFS1(1,1), DFS2(1,1), T.pre(n);
	double l=mn,r=mx,mid;
	for(int T=1; T<=31; ++T)
		if(Check(mid=(l+r)*0.5)) l=mid;
		else r=mid;
	printf("%.3lf\n",l);

	return 0;
}
