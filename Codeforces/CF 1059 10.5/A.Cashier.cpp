#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+7;

int n,L,a,t[N],l[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), L=read(), a=read();
	for(int i=1; i<=n; ++i) t[i]=read(),l[i]=read();
	int ans=0, las=0; t[++n]=L;
	for(int i=1; i<=n; ++i)
	{
		ans+=(t[i]-las)/a;
		las=t[i]+l[i];
	}
	printf("%d\n",ans);

	return 0;
}
