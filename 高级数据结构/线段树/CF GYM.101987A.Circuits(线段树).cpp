/*
109ms	13300KB
$Description$
二维平面上给定$n$个矩形，任作两条平行于$x$轴的无限长直线，使两条直线穿过的矩形数最多（两条直线穿过同一个矩形只算一个）。求穿过矩形的最大数量。
$Solution$
首先$x$坐标是没用的。其次只有线段端点有用，可以离散化成$2n$个点（$n$条线段，取两点使覆盖线段最多）。
然后我们可以枚举选择每一个点所在的位置。。只要能保证其它位置不计算经过该点的线段即可。
那只要线段树就好了。。（访问完一个左端点时将该线段加入线段树（区间加一），维护一个全局最大值就ok）
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int A[N],L[N],R[N],sum[N];
std::vector<int> vec[N];
struct Segment_Tree
{
	#define S N<<2
	int mx[S],tag[S];
	#undef S
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define Upd(rt,v) mx[rt]+=v, tag[rt]+=v
	#define Update(rt) mx[rt]=std::max(mx[ls],mx[rs])
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Modify(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) {Upd(rt,1); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R);
		if(m<R) Modify(rson,L,R);
		Update(rt);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline int Find(int r,int x)
{
	int l=1,mid;
	while(l<r)
		if(A[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	int m=read(),cnt=0;
	for(int i=1; i<=m; ++i)
		read(), A[++cnt]=R[i]=read(), read(), A[++cnt]=L[i]=read();
	std::sort(A+1,A+1+cnt);
	int tmp=cnt; cnt=1;
	for(int i=2; i<=tmp; ++i) if(A[i]!=A[i-1]) A[++cnt]=A[i];
	int n=cnt;
	for(int i=1; i<=m; ++i) L[i]=Find(cnt,L[i]), R[i]=Find(cnt,R[i]);
	for(int i=1; i<=m/*m!!!!*/; ++i) ++sum[L[i]], --sum[R[i]+1], vec[L[i]].push_back(R[i]);
	for(int i=1; i<=n; ++i) sum[i]+=sum[i-1];

	int res=1;
	for(int i=n; i; --i)
	{
		res=std::max(res,sum[i]+T.mx[1]);
		for(auto j:vec[i]) T.Modify(1,n,1,i,j);
	}
	printf("%d\n",res);

	return 0;
}
