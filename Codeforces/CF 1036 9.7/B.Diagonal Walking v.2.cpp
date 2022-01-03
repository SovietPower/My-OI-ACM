#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int Q=read();
	for(LL n,m,k,mx,mn; Q--; )
	{
		n=read(),m=read(),k=read();
		if(std::max(n,m)>k) {puts("-1"); continue;}
		mn=std::min(n,m), mx=std::max(n,m);
		if(n==m&&(n&1))
		{
			if(k&1) printf("%I64d\n",k);
			else printf("%I64d\n",k-2);
		}
		else if(n==m)
		{
			if(k&1) printf("%I64d\n",k-2);
			else printf("%I64d\n",k);
		}
		else if((mx-mn)&1) printf("%I64d\n",k-1);
		else
		{
			if((k-mn)&1) printf("%I64d\n",k-2);
			else printf("%I64d\n",k);
		}
	}
	return 0;
}
