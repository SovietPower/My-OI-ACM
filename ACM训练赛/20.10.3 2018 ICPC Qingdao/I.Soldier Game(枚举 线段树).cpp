/*
299ms	6768kB
$Description$
有$n$个物品，每个价值为$a_i$。现在要将每个物品或相邻的两个物品划分为一组，一组的权值为组中物品价值之和（每个物品属于且只属于一组）。
求划分后组的最大权值-最小权值的最小值。
$n\leq 10^5,\ \sum n\leq 10^6$。
$Solution$
最大值-最小值，考虑枚举！
区间只有$2n$个，可以将$2n$个区间排序，从小到大枚举最小值。
记$\min{\max}$表示令最大值最小时的最大值。枚举最小值区间$i$后，要用剩下的区间覆盖$1~n$且使最大值最小，并求一个$\min{\max}$，然后把区间$i$删掉（不能再作为最大值区间）。
最简单的是一个$O(n)$DP。可以发现这是一个每次删除一个区间，且答案与递推顺序无关（可以合并区间）的DP，可以用线段树维护。
线段树每个区间维护四个值：
$lmx$：包含左端点但不包含右端点的区间$\min{\max}$。
$rmx$：包含右端点但不包含左端点的区间$\min{\max}$。
$mx$：左右端点都不包含的区间$\min{\max}$。
$ans$：包含左右端点（即整个区间）的$\min{\max}$。
就可以合并区间了（初始化即长度为$1$的区间，合并区间时要用到长度为$2$的区间）。
删除区间的时候可以直接将区间赋值为$INF$（一定不会取）。
还有一个点是，最优解中最大值和最小值区间一定不会重叠（除了n=1或2），所以可以直接查询更新再删除（大概是这样）。
PS: 单点初始化时用长度为1,2的区间举个例子，lmx,rmx不存在就是-INF（取max不影响答案的取值），mx不合法就是INF（长度为1的区间不能用mx更新）。
最小的区间是-2e9，最大的区间可能为1e9，即求答案过程中可能爆int（虽然最终答案int内）。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=1e5+5,INF=2e9+10;

int A[N],B[N];
pr Ref[N<<1];
struct Segment_Tree
{
	#define S N<<2
	int lmx[S],rmx[S],mx[S],ans[S];
	#undef S
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	inline void Update(int rt,int mid)//B:长度为2的区间 B[mid]就是合并时区间相交段的值！
	{
		int l=ls,r=rs;
		lmx[rt]=std::min(std::max(lmx[rs],ans[ls]),std::max(mx[rs],std::max(B[mid],lmx[ls])));
		rmx[rt]=std::min(std::max(rmx[ls],ans[rs]),std::max(mx[ls],std::max(B[mid],rmx[rs])));
		mx[rt]=std::min(std::max(rmx[ls],lmx[rs]),std::max(mx[ls],std::max(B[mid],mx[rs])));
		ans[rt]=std::min(std::max(ans[ls],ans[rs]),std::max(lmx[ls],std::max(B[mid],rmx[rs])));
	}
	void Build(int l,int r,int rt)
	{
		if(l==r)
		{
			lmx[rt]=-INF, rmx[rt]=-INF, mx[rt]=INF/*!*/, ans[rt]=A[l];
			return;
		}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt,m);
	}
	void Modify(int l,int r,int rt,int p)
	{
		if(l==r)
		{
			ans[rt]=A[l];
			return;
		}
		int m=l+r>>1;
		p<=m ? Modify(lson,p) : Modify(rson,p);
		Update(rt,m);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int Ts=read(); Ts--; )
	{
		int n=read(),cnt=n+n-1;
		for(int i=1; i<=n; ++i) Ref[i]=mp(A[i]=read(),i);
		for(int i=1; i<n; ++i) Ref[i+n]=mp(B[i]=A[i]+A[i+1],i+n);
		std::sort(Ref+1,Ref+1+cnt);

		LL ans=1e14;
		T.Build(1,n,1);
		for(int i=1; i<=cnt && T.ans[1]!=INF; ++i)
		{
			ans=std::min(ans,1ll*T.ans[1]-Ref[i].first);
			int t=Ref[i].second;
			t<=n ? (A[t]=INF,T.Modify(1,n,1,t)) : (B[t-n]=INF,T.Modify(1,n,1,t-n));
		}
		printf("%lld\n",ans);
	}

	return 0;
}
/*
1 4
1000000000 1000000000 -1000000000 -1000000000
*/
