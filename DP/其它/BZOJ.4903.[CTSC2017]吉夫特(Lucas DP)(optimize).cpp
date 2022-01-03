/*
3800kb	688ms
https://www.cnblogs.com/SovietPower/p/9775319.html
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 2000000
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=(1<<18)+3,L=(1<<9)-1;

struct io
{
	char IN[MAXIN],*s;
	io():s(IN) {IN[fread(IN,1,MAXIN,stdin)]=0;}
	inline operator int()
	{
		int x=0;
		for(; *s<48; ++s);
		for(; *s>47; x=x*10+*s++-48);
		return x;
	}
}io;

int main()
{
	static int f[N];
	int n=io; LL ans=0,sum;
	for(int i=1,a; i<=n; ++i)
	{
		a=io,sum=0;
		int l=a&L, r=a>>9;
		for(int j=r; j<=L; j=(j+1)|r)
			sum+=f[(j<<9)|l];
		ans+=sum%=mod, ++sum;
		r<<=9;
		for(int j=l; j; j=(j-1)&l)
			f[j|r]+=sum, Mod(f[j|r]);
		f[r]+=sum, Mod(f[r]);//0|r
	}
	printf("%lld\n",ans%mod);

	return 0;
}
