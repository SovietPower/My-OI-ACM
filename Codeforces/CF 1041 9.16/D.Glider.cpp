//直接倒序线段树边查询边维护。傻了其实O(n)就可以。
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+7;

int A[N],B[N];
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,rt<<1
	#define rson m+1,r,rt<<1|1
	int dis[N<<2],sum[N<<2];

	inline void Update(int rt)
	{
		dis[rt]=dis[ls]+dis[rs],sum[rt]=sum[ls]+sum[rs];
	}
	void Insert(int l,int r,int rt,int p,int ds,int sm)
	{
		if(l==r)
		{
			dis[rt]+=ds, sum[rt]+=sm;
			return;
		}
		int m=l+r>>1;
		if(p<=m) Insert(lson,p,ds,sm);
		else Insert(rson,p,ds,sm);
		Update(rt);
//		printf("%d~%d(%d):dis[rt]=%d sum[rt]=%d\n",l,r,rt,dis[rt],sum[rt]);
	}
	int Query(int l,int r,int rt,int k)
	{
//		printf("Q(%d,%d,%d,%d)\n",l,r,rt,k);
		if(l==r) return dis[rt]+k;
		int m=l+r>>1;
		if(sum[ls]<k) return dis[ls]+sum[ls]+Query(rson,k-sum[ls]);
		else return Query(lson,k);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),H=read();
	for(int i=1; i<=n; ++i) A[i]=read(),B[i]=read();
	int ans=H;
	A[n+1]=2e9+5;
	for(int i=n; i; --i)
	{
		T.Insert(1,n,1,i,B[i]-A[i],A[i+1]-B[i]);
		ans=std::max(ans,T.Query(1,n,1,H));
	}
	printf("%d\n",ans);

	return 0;
}
