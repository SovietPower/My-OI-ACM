//直接线段树查询并维护。
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=4e5+5;//2N

int n,A[N];
LL ref[N],t,sum[N];
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,rt<<1
	#define rson m+1,r,rt<<1|1
	#define S N<<2
	int sz[S];
	#define Update(rt) sz[rt]=sz[ls]+sz[rs]
	void Insert(int l,int r,int rt,int p)
	{
		if(l==r) {++sz[rt]; return;}
		int m=l+r>>1;
		if(p<=m) Insert(lson,p);
		else Insert(rson,p);
		Update(rt);
	}
	void Delete(int l,int r,int rt,int p)
	{
		if(l==r) {--sz[rt]; return;}
		int m=l+r>>1;
		if(p<=m) Delete(lson,p);
		else Delete(rson,p);
		Update(rt);
	}
	int Query(int l,int r,int rt,int R)
	{
		if(r<=R) return sz[rt];
		int m=l+r>>1;
		if(m<R) return sz[ls]+Query(rson,R);
		else return Query(lson,R);
	}
}T;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL readll()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline int Find(LL x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	n=read(), t=readll(); int tot=0;
	for(int i=1; i<=n; ++i) A[i]=read(),sum[i]=sum[i-1]+(LL)A[i];
	for(int i=1; i<=n; ++i) ref[++tot]=sum[i-1],ref[++tot]=sum[i]-t+1;
	std::sort(ref+1,ref+1+tot); int cnt=1;
	for(int i=2; i<=tot; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) T.Insert(1,cnt,1,A[i]=Find(sum[i]-t+1,cnt));
	LL ans=0;
	for(int i=1; i<=n; ++i)
	{
		ans+=T.Query(1,cnt,1,Find(sum[i-1],cnt));
		T.Delete(1,cnt,1,A[i]);
	}
	printf("%I64d\n",ans);

	return 0;
}
