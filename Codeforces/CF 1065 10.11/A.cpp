#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int t=read();
	while(t--)
	{
		LL s=read(),a=read(),b=read(),c=read();
		LL ans=s/c; ans+=ans/a*b;
		printf("%I64d\n",ans);
	}
	return 0;
}
