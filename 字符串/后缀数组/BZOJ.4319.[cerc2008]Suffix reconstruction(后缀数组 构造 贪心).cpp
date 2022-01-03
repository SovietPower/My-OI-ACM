/*
6680kb	576ms
题意: 给定SA数组，求满足SA[]的一个原字符串(每个字符为小写字母)，无解输出-1. 
假设我们现在有suf(SA[j])，要构造suf(SA[i]) (要满足i>j) 
考虑后缀的比较方式，先比较第一位，再比较suf(SA[i]+1)与suf(SA[j]+1) 
若suf(SA[i]+1)>suf(SA[j]+1)，则两字符串第一位可以相同；否则一定要在第一位满足suf(SA[i])>suf(SA[j]) 
按照这种方式构造，就能保证尽可能多的重复使用字母 
如何比较suf(SA[i]+1)与suf(SA[j]+1)？不要忘了给了SA是可以求rk的。。比较rk即可。
无解即使用字符种数超过了小写字母个数 
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=5e5+5;

int n,sa[N],rk[N],A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) sa[i]=read();
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	int x=0; A[sa[1]]=x;
	for(int i=2; i<=n&&x<26; ++i)
		if(rk[sa[i-1]+1]<rk[sa[i]+1]) A[sa[i]]=x;
		else A[sa[i]]=++x;
	if(x>=26) printf("-1");
	else
		for(int i=1; i<=n; ++i) printf("%c",A[i]+'a');

	return 0;
}
