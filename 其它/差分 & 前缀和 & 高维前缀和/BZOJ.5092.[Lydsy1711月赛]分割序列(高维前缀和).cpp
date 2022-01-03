/*
6576kb	1748ms
首先处理$a_i$的前缀异或和$s_i$。那么在对于序列$a_1,...,a_n$，在$i$位置处分开的价值为：$s_i+s_i\ ^{\wedge}s_n$。
虽然有个加，但依旧可以考虑按位计算。如果$s_n$的第$k$位为$1$，那$s_i$的第$k$位为$0$或是$1$贡献都是$2^k$；如果$s_n$的第$k$位为$0$，那么$s_i$第$k$位为$0$则贡献为$0$，为$1$则贡献为$2*2^k$。
也就是说我们要求是否存在$i\leq n$，$s_i$的第$k$位为$1$且前$k$位都满足之前的限制（某些位必须为$1$）。
不妨去求，第$k$位为$1$且满足限制的最靠前的位置$i$，判断是否有$i\leq n$。
因为限制就是某些位必须为$1$，其它位任意，也就是超集。所以用高维前缀和维护满足某种限制的集合中，最靠前的位置就可以了。
复杂度$O(2^kk)$。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<20)+5;

int s[300005],f[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	static int pw[30];
	pw[0]=1;
	for(int i=1; i<=21; ++i) pw[i]=pw[i-1]<<1;

	int n=read(),mx=0;
	memset(f,0x3f,sizeof f);
	for(int i=1,t; i<=n; ++i)
		s[i]=s[i-1]^read(), mx=std::max(mx,s[i]), f[s[i]]=std::min(f[s[i]],i);
	int bit=1;
	while(pw[bit]<=mx) ++bit;
	for(int i=0,lim=1<<bit; i<bit; ++i)
		for(int s=0; s<lim; ++s)
			if(!(s&pw[i])) f[s]=std::min(f[s],f[s|pw[i]]);
	for(int i=1; i<=n; ++i)
	{
		int ans=0,t=0;
		for(int j=bit-1; ~j; --j)
			if(s[i]&pw[j]) ans|=pw[j];
			else if(f[t|pw[j]]<=i) t|=pw[j], ans+=pw[j+1];//+= not |=...
		printf("%d\n",ans);
	}
	return 0;
}
