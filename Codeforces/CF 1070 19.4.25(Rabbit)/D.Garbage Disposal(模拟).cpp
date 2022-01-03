/*
模拟一下就行了。
因为刚开始读错题还写了个二分=v=
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool Check(LL x,int n,int K)
{
	LL las=0;
	for(int i=1; i<=n; ++i)
	{
		LL need=(las+K-1)/K; las=std::max(0ll,A[i]-(need*K-las));
		x-=need;
		if(x<0) return 0;
	}
	return x>=(las+K-1)/K;//不要写x*K!!!
}

signed main()
{
	int n=read(),K=read(); LL sum=0;
	for(int i=1; i<=n; ++i) sum+=A[i]=read();
	LL l=0,r=3e18,mid,ans=r;
	while(l<=r)
		if(Check(mid=l+r>>1,n,K)) ans=mid, r=mid-1;
		else l=mid+1;
	printf("%I64d\n",ans);

	return 0;
}
