/*
$Description$
求矩形面积并。
$Solution$
对$x$坐标用扫描线扫，对$y$坐标就是线段树区间加、对区间不为$0$处的位置求和。
实现有点细节所以写一下：
1. 设离散化前原数组为$Ref$，则线段树上离散化后的$p$位置叶子的值为$Ref[p+1]-Ref[p]$，即不用离散化的长度1。所以修改的时候是改$[l,r-1]$（注意判$l=r$）（本质是叶子需要赋值，而只能赋那个区间的值）。
2. 因为这个区间加的本质是区间多次覆盖，所以不需要PushDown，加1减1只修改在对应的$\log$个大区间上。只要一个大区间被加过（覆盖）至少一次，该区间的值就为$Ref[r+1]-Ref[l]$，无需考虑子区间；否则该区间值为$sum[lson]+sum[rson]$（注意特判叶节点）。这样每次区间修改后，Update一下该区间即可。
3. 求答案的时候，操作按$x$排序，每个操作$q$的答案即为：$(x[q+1]-x[q])*sum[root]$，$sum[root]$为线段树上$y$被覆盖的区间长度和。但注意令$x[qn+1]=x[qn]$（最后一个肯定不会计入答案）。

复杂度$O(n\log n)$。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e3+5;

double Ref[N];
struct Node
{
	double x1,y1,x2,y2;
}P[N];
struct Operation
{
	double x; int l,r,val;
	bool operator <(const Operation &a)const
	{
		return x<a.x;
	}
}A[N];
struct Segment_Tree
{
	#define S N<<2
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	double sum[S]; int cnt[S];
	#undef S
	
	inline void Update(int rt,int l,int r)
	{
		if(cnt[rt]) sum[rt]=Ref[r+1]-Ref[l];
		else if(l<r) sum[rt]=sum[ls]+sum[rs];
		else sum[rt]=0;
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R)
		{
			cnt[rt]+=v, Update(rt,l,r);
			return;
		}
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
		Update(rt,l,r);
	}
	void Build(int l,int r,int rt)
	{
		sum[rt]=cnt[rt]=0;
		if(l==r) return;
		int m=l+r>>1; Build(lson), Build(rson);
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int TT=0; ++TT; )
	{
		int n=read(),cnt=0;
		if(!n) break;
		for(int i=1; i<=n; ++i) scanf("%lf%lf%lf%lf",&P[i].x1,&P[i].y1,&P[i].x2,&P[i].y2);
		for(int i=1; i<=n; ++i) Ref[++cnt]=P[i].y1, Ref[++cnt]=P[i].y2;
		std::sort(Ref+1,Ref+1+cnt);
		cnt=std::unique(Ref+1,Ref+1+cnt)-Ref-1;

		int m=0;
		for(int i=1; i<=n; ++i)
		{
			int L=std::lower_bound(Ref+1,Ref+1+cnt,P[i].y1)-Ref;
			int R=std::lower_bound(Ref+1,Ref+1+cnt,P[i].y2)-Ref-1;
			A[++m]=Operation{P[i].x1,L,R,1};
			A[++m]=Operation{P[i].x2,L,R,-1};
		}
		std::sort(A+1,A+1+m);
		
		double ans=0;
		#define S 1,cnt,1
		T.Build(S);
		for(int i=1; i<m; ++i)
		{
			if(A[i].l<=A[i].r) T.Modify(S,A[i].l,A[i].r,A[i].val);
			ans+=T.sum[1]*(A[i+1].x-A[i].x);
		}
		printf("Test case #%d\n",TT);
		printf("Total explored area: %.2f\n\n",ans);
	}
	

	return 0;
}
