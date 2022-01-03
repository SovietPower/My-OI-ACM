//39404kb	5876ms 跑的又比以前慢自闭了 
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
//#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=5e5+5;

int ref[N],h[N],Ans[M],root[N],fa[N];
//char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int u,v,w;
	bool operator <(const Edge &x)const
	{
		return w<x.w;
	}
}e[M];
struct Queries
{
	int s,v,k,id;
	bool operator <(const Queries &x)const
	{
		return v<x.v;
	}
}q[M];
struct Segment_Tree
{
	#define S N*18
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,l+r>>1
	#define rson rs,(l+r>>1)+1,r
	int tot,son[S][2],sz[S];
	#undef S

	void Insert(int &x,int l,int r,int p)
	{
		sz[x=++tot]=1;
		if(l<r) p<=(l+r>>1) ? Insert(lson,p) : Insert(rson,p);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x|y;
		ls=Merge(ls,son[y][0]), rs=Merge(rs,son[y][1]);
		return sz[x]+=sz[y],x;
	}
	int Query(int x,int l,int r,int k)
	{
		if(l==r) return l;
		int lsz=sz[ls];
		return lsz>=k?Query(lson,k):Query(rson,k-lsz);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int Getfa(int x)
{
	return x==fa[x]?x:fa[x]=Getfa(fa[x]);
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
inline void Merge(int x,int y)
{
	int r1=Getfa(x),r2=Getfa(y);
	if(r1!=r2) fa[r2]=r1, root[r1]=T.Merge(root[r1],root[r2]);
}
inline int Query(int n,int x,int k)
{
	int rt=root[Getfa(x)];
	return T.sz[rt]<k?-1:ref[T.Query(rt,1,n,T.sz[rt]-k+1)];
}

int main()
{
	const int n=read(),m=read(),Q=read();
	for(int i=1; i<=n; ++i) ref[i]=h[i]=read();
	std::sort(ref+1,ref+1+n); int cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) h[i]=Find(h[i],cnt);
	for(int i=1; i<=n; ++i) T.Insert(root[i],1,cnt,h[i]);

	for(int i=1; i<=m; ++i) e[i]=(Edge){read(),read(),read()};
	for(int i=1; i<=Q; ++i) q[i]=(Queries){read(),read(),read(),i};
	std::sort(e+1,e+1+m), std::sort(q+1,q+1+Q);

	for(int i=1; i<=n; ++i) fa[i]=i;
	e[m+1].w=2e9;
	for(int i=1,now=1; i<=Q; ++i)
	{
		while(e[now].w<=q[i].v) Merge(e[now].u,e[now].v), ++now;
		Ans[q[i].id]=Query(cnt,q[i].s,q[i].k);
	}
	for(int i=1; i<=Q; printf("%d\n",Ans[i++]));

	return 0;
}
