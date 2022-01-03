/*
有一种不需要重构线性基的方法：询问时将K二进制拆分(按size位)，若K在第j位有1,且当前答案在第i位没有1（还可以更大）或是 K在第j位没有1,且当前答案在第i位有1(偏小？)，则ans^=base[i]。
不太理解。~~（随大流吧。。）~~
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 51
typedef long long LL;
const int N=1e5+5;

int n,size;
LL base[69];
char IN[MAXIN],*SS=IN,*TT=IN;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void Insert(LL x)
{
	for(int i=Bit; ~i; --i)
		if(x>>i & 1)
			if(base[i]) x^=base[i];
			else {base[i]=x, ++size; break;}
}
inline LL Query(LL K)
{
	LL ans=0;
	for(int i=Bit,now=size; ~i; --i)
		if(base[i])
			if((K>>(--now) & 1)^(ans>>i & 1)) ans^=base[i];
	return ans;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) Insert(read());
	for(int Q=read(); Q--; )
	{
		LL K=read()-(size!=n);
		printf("%lld\n",(K>=(1ll<<size))?-1ll:Query(K));
	}
	return 0;
}
