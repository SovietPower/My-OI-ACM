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
	LL n=read(),m=read(),K=read(),L=read();
	LL ans=(L+K+m-1)/m;
	if(ans*m>n) puts("-1");
	else printf("%I64d\n",ans);

	return 0;
}
