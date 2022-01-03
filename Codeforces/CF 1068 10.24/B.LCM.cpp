#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;

inline LL read()
{
	LL now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	LL n=read(),ans=0;
//	for(LL i=1,nxt; i<=n; i=nxt+1)
//		nxt=n/(n/i), ++ans;
//	printf("%I64d\n",ans);
	ans=1;
	for(LL i=2; i*i<=n; ++i)
	{
		if(n%i) continue;
		int cnt=1;
		while(!(n%i)) ++cnt,n/=i;
		ans*=cnt;
	}
	if(n!=1) ans<<=1;
	printf("%I64d\n",ans);

	return 0;
}
