#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=1e6+7;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int T=read();
	while(T--)
	{
		long long a=read(), ans=1;
		for(int i=31; i>=0; --i)
			if(a>>i&1) ans<<=1ll;
		printf("%I64d\n",ans);
	}
	return 0;
}
