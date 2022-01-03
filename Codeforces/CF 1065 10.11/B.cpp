#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
const int N=1e5+5;
#define int long long
inline long long read()
{
	long long now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

 main()
{
	long long n=read(),m=read();
	long long ans1=std::max(0ll,n-m*2),ans2=0;
	int l=0,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		long long res=n-mid;
		if((res*(res-1)/2)>=m) ans2=mid,l=mid+1;
		else r=mid-1;
	}
//	for(int i=n; i; --i)
//		if(1ll*i*(i-1)/2<m) break;
//		else ans2=n-i;
//	if(!m) ans2=n;
	printf("%I64d %I64d\n",ans1,ans2);

	return 0;
}
