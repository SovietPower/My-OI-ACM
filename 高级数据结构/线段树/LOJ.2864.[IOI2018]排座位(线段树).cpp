/*
27496ms	1688K
先令编号从$1$开始。我们要求$[1,i]$这些数字能否构成一个矩形。
考虑能否用线段树维护，让每个叶子节点$i$表示前$i$个数能否构成矩形。
一种方法是维护前$i$个点最左上点和最右下点的坐标，直接判断这两个点构成的矩形面积是否是$i$。
发现修改的时候这个最值不好维护，每次修改可能是$O(n)$的。
考虑合法矩形的特征。把前$i$个点标记为黑点，其余点是白点。那么前$i$个点构成了一个矩形当且仅当：
1. 左边和上边都是白点的黑点有且只有一个。
2. 不存在一个白点，它的上下左右有两个及以上黑点。

正确性比较显然...？（雾）不说了。
记左边上边都是白点的黑点数量为$t1$，上下左右有两个及以上黑点是白点数量为$t2$。注意到$t1>0$，$t2$非负，那么$i$合法当且仅当$t1+t2=1$，所以只在叶节点处维护前$i$个点为黑点时，$t1+t2$的值就好了。非叶节点就维护区间最小值及最小值的个数。
考虑修改时如何维护。
记$l$为点$i$周围点（上下左右）编号的次小值，点$i$作为白点时，会对$[l,i-1]$这些位置有贡献。
记$r$为点$i$左边、上边的点的编号的最小值，那么点$i$作为黑点时，会对$[i,r-1]$这些位置有贡献。
每次交换两个点$x,y$，最多只会影响$10$个点的$l,r$，所以把这些点取出来，减掉在线段树上的贡献，交换$x,y$之后再把它们的贡献加上即可。
注意要对这些点判重。
*/
#include "seats.h"
#include <cstdio>
#include <cctype>
#include <algorithm>
#define F(p,i) (p+Way[i])
#define ID(x,y) ((x-1)*m+y)
#define Check(x,y) (x>=1&&x<=n&&y>=1&&y<=m)
#define gc() getchar()
const int N=1e6+5,Way[]={1,0,-1,0,1};//down left up right

int n,m,tot,A[N],X[N],Y[N],val[N];
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int mn[S],cnt[S],tag[S];
	#undef S
	#define Upd(rt,v) tag[rt]+=v, mn[rt]+=v
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs]), cnt[rt]=(mn[rt]==mn[ls]?cnt[ls]:0)+(mn[rt]==mn[rs]?cnt[rs]:0)
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r)
		{
			mn[rt]=val[l], cnt[rt]=1;
			return;
		}
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
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int CalcW(int p)
{
	int mn1=tot+1,mn2=mn1,x=X[p],y=Y[p];
	for(int i=0,xn,yn; i<4; ++i)
		if(xn=F(x,i),yn=F(y,i+1),Check(xn,yn))
		{
			int w=A[ID(xn,yn)];
			if(w<mn1) mn2=mn1, mn1=w;
			else if(w<mn2) mn2=w;
		}
	return mn2;
}
inline int CalcB(int p)
{
	int x=X[p],y=Y[p],xn1=F(x,1),yn1=F(y,2),xn2=F(x,2),yn2=F(y,3);
	return std::min(Check(xn1,yn1)?A[ID(xn1,yn1)]:tot+1,Check(xn2,yn2)?A[ID(xn2,yn2)]:tot+1);
}
#define S 1,tot,1
void give_initial_chart(int n,int m,std::vector<int> R,std::vector<int> C)
{
	int tot=n*m; ::n=n, ::m=m, ::tot=tot;
	for(int i=1; i<=tot; ++i) X[i]=R[i-1]+1,Y[i]=C[i-1]+1,A[ID(X[i],Y[i])]=i;
//	for(int i=1; i<=tot; ++i) X[i]=read()+1,Y[i]=read()+1,A[ID(X[i],Y[i])]=i;
	for(int i=1; i<=tot; ++i)
	{
		val[i]=val[i-1];
		if(CalcW(i)<i) --val[i];
		if(CalcB(i)>i) ++val[i];
		for(int j=0,x=X[i],y=Y[i],xn,yn,w; j<4; ++j)
			if(xn=F(x,j),yn=F(y,j+1),Check(xn,yn))
			{
				if((w=A[ID(xn,yn)])<i && CalcB(w)==i) --val[i];
				else if(w>i && CalcW(w)==i) ++val[i];
			}
	}
	T.Build(S);
}
int swap_seats(int a,int b)
{
	static int B[12];
	++a, ++b;
	int x=X[a],y=Y[a],t=2; B[1]=a, B[2]=b;
	for(int i=0,xn,yn; i<4; ++i)
		if(xn=F(x,i),yn=F(y,i+1),Check(xn,yn)) B[++t]=A[ID(xn,yn)];
	x=X[b],y=Y[b];
	for(int i=0,xn,yn; i<4; ++i)
		if(xn=F(x,i),yn=F(y,i+1),Check(xn,yn)) B[++t]=A[ID(xn,yn)];
	std::sort(B+1,B+1+t);
	for(int i=1; i<=t; ++i)
		if(B[i]!=B[i-1])
		{
			int p=B[i],l=CalcW(p),r=CalcB(p);
			if(l<p) T.Modify(S,l,p-1,-1);
			if(r>p) T.Modify(S,p,r-1,-1);
		}
	std::swap(A[ID(X[a],Y[a])],A[ID(X[b],Y[b])]);
	std::swap(X[a],X[b]), std::swap(Y[a],Y[b]);
	for(int i=1; i<=t; ++i)
		if(B[i]!=B[i-1])
		{
			int p=B[i],l=CalcW(p),r=CalcB(p);
			if(l<p) T.Modify(S,l,p-1,1);
			if(r>p) T.Modify(S,p,r-1,1);
		}
	return T.cnt[1];
}

//int main()
//{
//	int n=read(),m=read(),Q=read(); ::n=n, ::m=m;
//	give_initial_chart(n,m);
//	while(Q--) printf("%d\n",swap_seats(read(),read()));
//
//	return 0;
//}
