/*
2292ms	116300KB
这个数据范围有毒。。
这种题记得用fread。

$Description$
$n$个位置，最初每个位置上没有数。
$m$次操作，操作有两种：
1. 在一个没有数的位置$x$加一个数$v$。
2. 给定$x$，询问$[l,r]$中与$x$相差最小的数，即$\min_{v\in[l,r]}|x-v|$。
$n\leq 5\times10^5,\ m\leq 10^6$。

$Solution$
最简单的是线段树套set，$O(m\log^2n)$+大常数所以过不了。
**Sol 1**
考虑离线，把询问按$r$排序，每次用在$r$位置插入的值更新，然后求以$r$为右端点的询问。

设此时的一个询问为$[L,R],x$，询问编号为$id$。
设已经插入的值为$v_i$，对应的操作编号为$i$，插入位置为$pos_i\leq R$。
则$v_i$能更新询问当且仅当$pos_i\geq L$且$i\lt id$。

将询问拆成，找最大的$v_i$满足$v_i\leq x$且$pos_i\geq L$且$i\lt id$，和找最小的$v_i$满足$v_i\geq x$且$pos_i\geq L$且$i\lt id$。
对第一种询问，只需考虑$[1,x]$中，最靠右的满足$pos_i\geq L$且$i\lt id$的$i$是哪个。不妨考虑用一个线段树，对每个节点$[l,r]$，判断$l\leq v_i\leq r$时是否有符合条件的$i$，如果有就继续先找右儿子再找左儿子，如果该区间没有就return。
也就是用一个线段树维护所有当前的$v_i$，节点$[l,r]$保存所有$l\leq v_i\leq
r$的$i$。
然后如何判断某节点的$v_i$中是否存在$i$使$pos_i\geq L$且$i\lt id$？
注意到我们是按$pos$从小到大更新插入的值，所以后插入的值$pos$一定大于之前的。而节点中有必要保留的点，是要么$pos$更大、要么$i$更小的点。所以如果在某节点插入$v_i$时，$i$小于该节点中另一个值的操作编号，那个值就可以删掉。
容易发现这样每个节点都是一个单调队列，从队首到队尾，编号$i$递增，$pos$递增。
所以每个节点的查询，只需要二分第一个$pos\geq L$的值，然后判断其编号$i$是否有$i\lt id$（或最后一个$i\lt id$的值，然后判断是否其$pos\geq L$）。
这样每次查询复杂度$O(\log^2n)$。每次插入值，就更新根节点到该值整条链上的单调队列，复杂度$O(\log n)$。

所以复杂度$O(n\log n+m\log^2n)$。
注意空间也是$O(n\log n)$的，刚开始要建树，根据每个节点上数的个数（前缀和算）分配一下其单调队列的空间。

**Sol 2**
在线的话可以分块。每个块因为最多有$\sqrt n$个数，所以在每次插入时，暴力将这个数放到对应位置，使每块里的数保持有序。
查询时，边界暴力，整块中因为块内有序，可以二分第一个小于等于$x$的数$A[p]$，$A[p],A[p+1]$即为可能答案。
复杂度$O(m\sqrt n+m\sqrt n\log n)$。和std跑的差不多快。。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define pb emplace_back
typedef long long LL;
const int N=5e5+5,M=1e6+6,Q=1e7+1e6+5/*队列最少的空间，1e7还是太小*/;

int A[M],sum[M],Ans[M],qid[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int L,pos,val;
}q[M];
std::vector<int> vec[N];
struct Segment_Tree
{
	#define S M<<2	//值域为M！
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	int now,res,qL,qid,pos[M],L[S],R[S],q[Q];
	#undef S
	void Build(int l,int r,int rt)
	{
		L[rt]=now, R[rt]=now-1;	//初始化该节点的队首和队尾 
		now+=sum[r]-sum[l-1];	//分配该节点的空间 
		if(l==r)
		{
			pos[l]=rt;			//记一下每个值叶节点的位置 
			return;
		}
		int m=l+r>>1;
		Build(lson), Build(rson);
	}
	void Update(int p,int id,int val)
	{
		for(int rt=pos[val]; rt; rt>>=1)	//记录叶节点位置，自底向上for就可以了 
		{
			int h=L[rt], t=R[rt];
			while(h<=t && q[t]>id) --t;
			q[++t]=id, R[rt]=t;
		}
	}
	bool Check(int rt)
	{
		int l=L[rt],r=R[rt],mid;
		while(l<=r)
		{
			mid=l+r>>1;
			if(q[mid]<qid && ::q[q[mid]].pos>=qL) return 1;
			if(q[mid]<qid) l=mid+1;
			else r=mid-1;
		}
		return 0;
//		while(l<r)
//		{
//			mid=l+r+1>>1;
//			if(q[mid]<qid) l=mid;
//			else r=mid-1;
//		}
//		return q[l]<qid && ::q[q[l]].pos>=qL;
	}
	void QueryL(int l,int r,int rt,int qR)
	{
		if(res||L[rt]>R[rt]) return;	//! 区间里没有数记得return 
		if(r<=qR)
		{
			if(!Check(rt)) return;	//先找到对应区间，再Check，少Check一些是不是会快 
			if(l==r) {res=l; return;}	//当然不合法区间不会DFS到叶节点 
		}
		int m=l+r>>1;
		if(m<qR) QueryL(rson,qR);
		QueryL(lson,qR);
	}
	void QueryR(int l,int r,int rt,int qL)
	{
		if(res||L[rt]>R[rt]) return;	//! 区间里没有数记得return 
		if(qL<=l)
		{
			if(!Check(rt)) return;
			if(l==r) {res=l; return;}
		}
		int m=l+r>>1;
		if(qL<=m) QueryR(lson,qL);
		QueryR(rson,qL);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Query(int id,int cnt)
{
	int L=q[id].L,val=q[id].val,ans=2e9;
	T.qL=L, T.qid=id;

	T.res=0, T.QueryL(1,cnt,1,val);
	if(T.res) ans=A[val]-A[T.res];
	T.res=0, T.QueryR(1,cnt,1,val);
	if(T.res) ans=std::min(ans,A[T.res]-A[val]);

	Ans[id]=ans==2e9?-1:ans;
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		int n=read(),m=read(),cnt=m;
		for(int i=1; i<=m; ++i)
		{
			if(!read()) q[i]=Quries{0,read(),read()};
			else q[i]=Quries{read(),read(),read()};
			A[i]=q[i].val;
		}
		std::sort(A+1,A+1+m), cnt=std::unique(A+1,A+1+m)-A-1;	//值的个数为m不是n！ 

		memset(sum,0,cnt+1<<2), memset(qid,0,n+1<<2);
		for(int i=1; i<=n; ++i) std::vector<int>().swap(vec[i]);

		for(int i=1; i<=m; ++i)
		{
			int v=std::lower_bound(A+1,A+1+cnt,q[i].val)-A;
			q[i].val=v;
			if(!q[i].L) qid[q[i].pos]=i, ++sum[v];
			else vec[q[i].pos].pb(i);
		}
		for(int i=1; i<=cnt; ++i) sum[i]+=sum[i-1];	//注意n,m,cnt含义！

		#define S 1,cnt,1
		T.now=1, T.Build(S);

		for(int i=1; i<=n; ++i)	//枚举R 
		{
			if(qid[i]) T.Update(i,qid[i],q[qid[i]].val);
			for(auto v:vec[i]) Query(v,cnt);
		}
		
		for(int i=1; i<=m; ++i) q[i].L && printf("%d\n",Ans[i]);
	}

	return 0;
}
