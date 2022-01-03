/*
327ms	78600KB
我写的比较无脑... 按天数为下标建线段树。将物品区间按价格排序，考虑依次加到线段树对应区间上。
设当前区间剩余所需个数的最小值是$mn$（初始都为$k$），当前物品区间、个数、单位价格分别是$(l,r,a,cost)$。$mn\gt a$时，直接区间减$a$统计一下答案就行了；当$mn\leq a$时，一定至少有一个位置会被减成$0$，暴力在线段树找到那个/那些位置把$size$清零，$mn$设为$INF$，统计一下答案即可。
因为每个数只会被清空一次，也就是只会暴力做$O(n)$次，所以复杂度$O((n+m)\log n)$。
其实只要拿价格建一棵值域线段树，每个位置维护有多少个物品就行了。查询就是在树上二分出前$k$小的和（树状数组也行）。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;
const LL INF=3e18;

char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int l,r,num,cost;
	bool operator <(const Node &x)const
	{
		return cost<x.cost;
	}
}A[N];
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	LL mn[S];//mn[rt]=INF要足够大！
	int sz[S],tag[S];
	LL Ans;
	#undef S
	#define Upd(rt,v) mn[rt]+=v, tag[rt]+=v
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs]), sz[rt]=sz[ls]+sz[rs]
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt,int K)
	{
		mn[rt]=K, sz[rt]=r-l+1;
		if(l==r) return;
		int m=l+r>>1; Build(lson,K), Build(rson,K);
	}
	void Modify2(int l,int r,int rt,int a,int cost)
	{
		if(mn[rt]>a) {Ans+=1ll*cost*a*sz[rt], Upd(rt,-a); return;}
		if(l==r) {Ans+=1ll*cost*mn[rt], sz[rt]=0, mn[rt]=INF; return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		Modify2(lson,a,cost), Modify2(rson,a,cost), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int a,int cost)
	{
		if(L<=l && r<=R) {Modify2(l,r,rt,a,cost); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,a,cost);
		if(m<R) Modify(rson,L,R,a,cost);
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

int main()
{
	#define S 1,n,1
	const int n=read(),K=read(),m=read();
	for(int i=1; i<=m; ++i) A[i]=(Node){read(),read(),read(),read()};
	std::sort(A+1,A+1+m), T.Build(S,K);
	for(int i=1; i<=m; ++i) T.Modify(S,A[i].l,A[i].r,A[i].num,A[i].cost);
	printf("%I64d\n",T.Ans);

	return 0;
}
