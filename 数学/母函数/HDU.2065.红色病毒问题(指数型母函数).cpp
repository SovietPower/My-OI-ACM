//0MS	1576K
//https://www.cnblogs.com/SovietPower/p/9095543.html#_label4
#include <cstdio>
#include <cctype>
#define mod (100)
#define gc() getchar()

inline long long read()
{
	long long now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,long long k)
{
	int t=1;
	for(; k; k>>=1, x=x*x%mod)
		if(k&1) t=t*x%mod;
	return t;
}

int main()
{
	int T; long long n;
	while(T=read(),T){
		for(int Case=1; Case<=T; ++Case)
			n=read(), printf("Case %d: %d\n",Case,(FP(4,n-1)+FP(2,n-1))%mod);
		putchar('\n');
	}
	return 0;
}
