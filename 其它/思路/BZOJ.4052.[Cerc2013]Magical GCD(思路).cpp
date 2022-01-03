/*
1116KB	620MS
gcd有结合律，而且gcd每次改变至少会变小两倍，而且只会减小。
所以对于每个右端点，可以暴力维护每种gcd出现的最靠前的位置（只有$log$种gcd）。
by SovietPower...
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=105;

char IN[MAXIN],*SS=IN,*TT=IN;

inline LL read()
{
	LL now=0; register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
LL Gcd(LL x,LL y)
{
	return y?Gcd(y,x%y):x;
}

int main()
{
	static int pos[N];
	static LL val[N];

	for(int T=read(); T--; )
	{
		int n=read(); LL ans=0;
		for(int i=1,t=0; i<=n; ++i)
		{
			LL ai=read();
			int las=t; t=0;
			for(int j=1; j<=las; ++j)
			{
				LL tmp=Gcd(val[j],ai);
				if(val[t]!=tmp) val[++t]=tmp, pos[t]=pos[j], ans=std::max(ans,tmp*(i-pos[j]+1));
			}
			if(val[t]!=ai) val[++t]=ai, pos[t]=i, ans=std::max(ans,ai);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
