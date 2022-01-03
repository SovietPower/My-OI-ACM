//«©µΩÃ‚ 
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	for(int Ts=read(),T=1; T<=Ts; ++T)
	{
		int n=read(),ans=0;
		for(int i=1; i<=n; ++i)
		{
			int a=read(),b=a/10;
			if(b*10<a) ++b;
			ans+=a+b;
		}
		printf("Case #%d: %d\n",T,ans);
	}

	return 0;
}
