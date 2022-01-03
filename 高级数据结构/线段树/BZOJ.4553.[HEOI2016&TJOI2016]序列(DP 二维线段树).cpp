/*
BZOJ上直接MLE...洛谷P4093 4508ms(比Bit套Segtree慢3倍+) 293.33MB 
$O(n^2)$DP很好写，对于当前的i从之前满足条件的j中选一个最大值,$dp[i]=d[j]+1$
 for(int j=1; j<i; ++j)
	if(a[j]<=minv[i]&&maxv[j]<=a[i])//序列只会变换一次 
		dp[i]=max{dp[j]+1};
转移要满足两个条件：$a[j]<=minv[i]\ \&\&\ maxv[j]<=a[i]$ 
一个二维偏序问题，CDQ、树套树都可以。
拿$minv[x]$和$a[y]$作为两个坐标轴，$dp[j]$表示其上一点$(A[j],maxv[j])$.
这样就成了一个二维平面，可以向其中插入一些点dp[i]，询问一个矩形区域(也是一段前缀)中某点最大值 
线段树套线段树 树状数组套线段树都可做 复杂度$O(nlog^2n)$ 
后者时间还可以 
空间消耗比较大 写指针吧。。
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
#define lson l,m,rt->ls
#define rson m+1,r,rt->rs
const int N=1e5+5;

int n,m,A[N],maxv[N],minv[N],MaxA,MaxV;
namespace Seg_Tree2D
{
	struct Node
	{
		int maxv;
		Node *ls,*rs;
		Node(): maxv(0),ls(NULL),rs(NULL) { }
	}pool[N<<7];//(logN)^2=256(2^8) 开得小点吧要不空间会炸 
	struct Node2D
	{
		Node *root;
		Node2D *ls,*rs;
		Node2D(): root(NULL),ls(NULL),rs(NULL) { }
	}pool2D[N<<1],*root;
	inline Node *new_Node()
	{
		static int cnt=0;
		return &pool[cnt++];
	}
	inline Node2D *new_Node2D()
	{
		static int cnt=0;
		return &pool2D[cnt++];
	}
	Node2D *Build(int l,int r)
	{
		Node2D *rt = new_Node2D();
		if(l<r)
		{
			int m=l+r>>1;
			rt->ls = Build(l,m);
			rt->rs = Build(m+1,r);
		}
		return rt;
	}
	int Query(int l,int r,Node *rt,int L,int R)
	{
		if(!rt) return 0;
		if(L<=l && r<=R) return rt->maxv;
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(lson,L,R),Query(rson,L,R));
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
	int Query2D(int l,int r,Node2D *rt,int L,int R,int y1,int y2)
	{
		if(L<=l && r<=R) return Query(1,MaxA,rt->root,y1,y2);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query2D(lson,L,R,y1,y2),Query2D(rson,L,R,y1,y2));
			else return Query2D(lson,L,R,y1,y2);
		return Query2D(rson,L,R,y1,y2);
	}
	void Insert(int l,int r,Node *&rt,int p,int v)
	{
		if(!rt) rt = new_Node();//!
		rt->maxv = std::max(rt->maxv, v);
		if(l<r)
		{
			int m=l+r>>1;
			if(p<=m) Insert(lson,p,v);
			else Insert(rson,p,v);
		}
	}
	void Insert2D(int l,int r,Node2D *rt,int p,int y,int v)
	{
		Insert(1, MaxA, rt->root, y, v);
		if(l<r)
		{
			int m=l+r>>1;
			if(p<=m) Insert2D(lson,p,y,v);
			else Insert2D(rson,p,y,v);
		}
	}
	void Init()
	{
		root = Build(1,MaxV);
	}
	int Query_Max(int l,int r,int y1,int y2)
	{
		return Query2D(1,MaxV,root,l,r,y1,y2);
	}
	void Insert_Node(int x,int y,int v)
	{
		Insert2D(1,MaxV,root,x,y,v);
	}
}
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}


int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i)
		maxv[i]=minv[i]=A[i]=read(), MaxA=std::max(MaxA,A[i]);
	for(int x,y,i=1; i<=m; ++i)
		x=read(), y=read(), maxv[x]=std::max(maxv[x],y), minv[x]=std::min(minv[x],y);
	for(int i=1; i<=n; ++i) MaxV=std::max(MaxV,maxv[i]);
	Seg_Tree2D::Init();
	int ans=0;
	for(int v,i=1; i<=n; ++i)
	{
		v = Seg_Tree2D::Query_Max(1,minv[i],1,A[i]) + 1;
		Seg_Tree2D::Insert_Node(A[i],maxv[i],v);
		ans=std::max(ans,v);
	}
	printf("%d",ans);

	return 0;
}
