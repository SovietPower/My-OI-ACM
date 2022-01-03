/*
1016kb	64ms
$Description$
给定序列$ai$，求$ai$的一个最长子序列$bi$，满足b[i]&b[i-1]!=0（$b_i\&b_{i-1}\neq0(2\leq i\leq len)$）。
$Solution$
我们只需要判断，$b$序列的上一个数与当前数与起来有一位不为0即可。
f[i][j]表示前i个数中，满足$b$序列的最后一个数第j位为1，的最长子序列长度。
想了想怎么只会$\log^2$的转移。。
当前能转移ai为1的位。因为所有位转移到的位置都是一样的，所以在它们中取个max就行了。
复杂度$O(n\log a)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define BIT 30

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
	static int f[33];
	int n=read();
	for(int i=1; i<=n; ++i)
	{
		int ai=read(),tmp=0;
		for(int j=0; j<=BIT; ++j)
			if(ai>>j&1) tmp=std::max(tmp,f[j]);
		++tmp;
		for(int j=0; j<=BIT; ++j)
			if(ai>>j&1) f[j]=tmp;
	}
	int ans=0;
	for(int i=0; i<=BIT; ++i) ans=std::max(ans,f[i]);
	printf("%d\n",ans);

	return 0;
}
