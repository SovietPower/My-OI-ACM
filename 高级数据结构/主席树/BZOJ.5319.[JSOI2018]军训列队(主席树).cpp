/*
210300kb	12428ms
对于询问$l,r,k$，设$t=r-l+1$。对于指定区间$[k,k+t-1]$，显然$k$左边的人都要从$k$开始依次排列，$k+t-1$右边的人要从$k+t-1$往左依次排列。区间中的比较麻烦。
~~也比较显然的是~~存在一个点$mid\in[k-1,k+t-1]$，使得$mid$左边的人都被排在$[k,mid]$中，右边的人都被排到$[mid+1,k+t-1]$中。而且代价很好算，就是需要求一个等差数列的和，以及左边所有人的坐标和。
考虑如何找这个$mid$。显然有$mid$左边人的数量等于$mid-k+1$，所以可以二分+主席树，但是是$\log^2$的。
注意到查的区间是个前缀，所以可以直接在主席树上二分。
那么复杂度就是$O(n\log n)$啦。
~~莫名想写指针~~
为啥我的主席树这么慢\_(:з」∠)\_ 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define F(l,r) (1ll*((r)-(l)+1)*(l+r)>>1)//n(a1+an)/2... l<=r+1
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int A[N],root[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m,
	#define rson rs,m+1,r
	#define lson2 ls,son[y][0],l,m
	#define rson2 rs,son[y][1],m+1,r
	#define S N*21
	int tot,son[S][2],sz[S];
	LL lsum,rsum,sum[S];
	#undef S
	void Insert(int &x,int y,int l,int r,int p)
	{
		sz[x=++tot]=sz[y]+1, sum[x]=sum[y]+p;
		if(l==r) return;
		int m=l+r>>1;
		p<=m?(rs=son[y][1],Insert(lson2,p)):(ls=son[y][0],Insert(rson2,p));
	}
	int Query(int x,int y,int l,int r,int K)//y-x
	{
		if(l==r) return lsum+=sum[y]-sum[x],l;//mid=k-1 -> lsum=sum[now]=0
		int m=l+r>>1,t=sz[son[y][0]]-sz[ls];
		return m-K+1>=t?(rsum+=sum[son[y][1]]-sum[rs],Query(lson2,K)):(lsum+=sum[son[y][0]]-sum[ls],Query(rson2,K+t));
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
	int n=read(),Q=read(),mx=0,mn=N;
	for(int *s=A+1,*ed=A+1+n; s!=ed; ++s) mx=std::max(mx,*s=read()), mn=std::min(mn,*s);
	for(int i=1; i<=n; ++i) T.Insert(root[i],root[i-1],mn,mx,A[i]);
	for(int l,r,ql,qr; Q--; )
	{
		l=read(),r=read(),ql=read(),qr=ql+r-l;
		if(ql<=mn||qr>=mx) printf("%lld\n",std::abs(T.sum[root[r]]-T.sum[root[l-1]]-F(ql,qr)));
		else
		{
			T.lsum=0, T.rsum=0;
			int mid=T.Query(root[l-1],root[r],mn,mx,ql);
			printf("%lld\n",F(ql,mid)-T.lsum+T.rsum-F(mid+1,qr));
		}
	}
	return 0;
}
