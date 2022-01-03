/*
39360kb	5248ms
$Description$
有n个座山，其高度为hi。有m条带权双向边连接某些山。多次询问，每次询问从v出发 只经过边权<=x的边 所能到达的山中，第K高的是多少。
$Solution$
x的限制将图分成了若干连通块，如果x单调递增的话，只需要合并连通块就可以了。
离线，并查集维护所属连通块，线段树合并状态、查询K大。（强制在线的话可以主席树？ 感觉会贼难写吧。。）
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,M=5e5+5;

int n,m,Q,cnt,ref[N],h[N],Ans[M],fa[N],root[N];
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read();
struct Edge{
	int fr,to,val;
	inline void Read(){
		fr=read(), to=read(), val=read();
	}
	bool operator <(const Edge &a)const{
		return val<a.val;
	}
}e[M];
struct QUERY{
	int fr,x,k,id;
	inline void Read(int i){
		fr=read(), x=read(), k=read(), id=i;
	}
	bool operator <(const QUERY &a)const{
		return x<a.x;
	}
}q[M];
struct Segment_Tree
{
	#define S N*18
	#define lson son[x][0]
	#define rson son[x][1]
	int tot,sz[S],son[S][2];

	void Insert(int &x,int l,int r,int p)
	{
		sz[x=++tot]=1;
		if(l==r) return;
		int m=l+r>>1;
		if(p<=m) Insert(lson,l,m,p);
		else Insert(rson,m+1,r,p);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x^y;
		lson=Merge(lson,son[y][0]), rson=Merge(rson,son[y][1]);
		sz[x]+=sz[y]; /*sz[y]=0;*/ return x;
	}
	int Query(int x,int l,int r,int k)
	{
		if(l==r) return l;
		int ls=sz[lson];
		if(k<=ls) return Query(lson,l,l+r>>1,k);
		return Query(rson,(l+r>>1)+1,r,k-ls);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
int Getfa(int x){
	return x==fa[x]?x:fa[x]=Getfa(fa[x]);
}
inline int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
void Merge(int x,int y)
{
	int r1=Getfa(x), r2=Getfa(y);
	if(r1==r2) return;
	fa[r2]=r1, root[r1]=T.Merge(root[r1],root[r2]);
}
int Query(int x,int k)
{
	int rt=Getfa(x);
	return T.sz[root[rt]]<k?-1:ref[T.Query(root[rt],1,cnt,T.sz[root[rt]]-k+1)];
}

int main()
{
	n=read(), m=read(), Q=read();
	for(int i=1; i<=n; ++i) ref[i]=h[i]=read(), fa[i]=i;
	std::sort(ref+1,ref+1+n), cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) h[i]=Find(h[i]), T.Insert(root[i],1,cnt,h[i]);

	for(int i=1; i<=m; ++i) e[i].Read();
	std::sort(e+1,e+1+m);
	for(int i=1; i<=Q; ++i) q[i].Read(i);
	std::sort(q+1,q+1+Q);

	for(int i=1,now=1; i<=Q; ++i)
	{
		while(now<=m && e[now].val<=q[i].x) Merge(e[now].fr,e[now].to), ++now;
		Ans[q[i].id]=Query(q[i].fr,q[i].k);
	}
	for(int i=1; i<=Q; ++i) printf("%d\n",Ans[i]);

	return 0;
}
