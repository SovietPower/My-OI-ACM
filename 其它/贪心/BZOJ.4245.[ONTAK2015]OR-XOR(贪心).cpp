/*
5508kb	768ms
从高到低位贪心，判断答案的该位能否为0。
求一个前缀和sum。对于最高位，答案的这一位可以为0当且仅当至少存在m个位置满足sum[i]在这一位上为0。
注意sum[n]这一位必须为0。
如果确定高位为0，则高位为1的sum[i]就不能再选（即不能做右端点）。
这样求一遍所有位即可。复杂度$O(n\log a)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;
const LL LIM=(1ll<<61)-1ll;

int n,m;
bool ban[N];
LL sum[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool OK(int bit)
{
	if(sum[n]>>bit&1) return 0;
	int cnt=0;
	for(int i=1; i<=n; ++i)
		if(!ban[i]&&!(sum[i]>>bit&1))
			if(++cnt==m) break;
	if(cnt<m) return 0;
	for(int i=1; i<=n; ++i)
		if(sum[i]>>bit&1) ban[i]=1;
	return 1;
}

int main()
{
	n=read(),m=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]^read();
	if(m==1) return printf("%lld\n",sum[n]),0;

	LL ans=0;
	for(int i=60; ~i; --i) if(!OK(i)) ans|=1ll<<i;
	printf("%lld\n",ans);

	return 0;
}
