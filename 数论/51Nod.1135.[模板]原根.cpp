/*
46ms	1,880KB
https://www.cnblogs.com/SovietPower/p/10044472.html
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k,int mod)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
int Find_root(int P)
{
	static int p[N];
	int cnt=0,x=P-1;
	for(int i=2; i*i<=x; ++i)
		if(!(x%i))
		{
			p[++cnt]=i;
			while(!(x%i)) x/=i;
		}
	if(x!=1) p[++cnt]=x;
	for(int x=2; ; ++x)
	{
		bool ok=1;
		for(int i=1; i<=cnt; ++i) if(FP(x,(P-1)/p[i],P)==1) {ok=0; break;}
		if(ok) return x;
	}
	return -1;
}

int main()
{
	printf("%d\n",Find_root(read()));
	return 0;
}
