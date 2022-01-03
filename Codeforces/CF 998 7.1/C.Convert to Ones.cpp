/*
如果X,Y的大小关系确定，那可以完全利用小的那个。即策略只有两种：把所有0换在一起，一次反转；反转所有段的0。统计有多少段0即可。
当时闲的数了一下1的段数，然后就把zero和one写反了，然后就被MainTest给×了==。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
using std::min;
typedef long long LL;
const int N=4e5+7;
const LL INF=1e17;

int n;
LL X,Y;
char s[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), X=read(), Y=read(), scanf("%s",s+1);
	int cnt=0;
	for(int i=1; i<=n; ++i) if(s[i]=='0') ++cnt;
	if(!cnt) return putchar('0'),0;//判1的话还要判一下这个...
	if(cnt==n) return printf("%I64d",Y),0;

	LL zero=0,one=0;
	if(s[1]=='0') ++zero; else ++one;
	for(int i=2; i<=n; ++i)
		if(s[i]=='1'&&s[i-1]=='0') ++one;
		else if(s[i]=='0'&&s[i-1]=='1') ++zero;
	printf("%I64d",min((zero-1ll)*X+Y,min(zero*Y,min((one-1ll)*X+2ll*Y,one*Y+Y))));

	return 0;
}
