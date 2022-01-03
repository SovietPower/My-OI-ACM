/*
32ms	896KB
$Description$
给定$n$个数$A_i$，且这$n$个数的$GCD$为$1$。两个人轮流进行如下操作：
1. 选择一个$>1$的数使它$-1$。
2. 第一步进行完后，所有数会变成它除以$g$，其中$g$是$n$个数的$GCD$。
当轮到一个人操作，但所有数为$1$时，该人输。求先手是否必胜。
$n\leq10^5,\ A_i\leq10^9$。

$Solution$
首先能发现一些性质：
> 1. 当有一个数变成$1$时，答案只和所有数的和$-n$的奇偶性有关。
2. 对所有数除以一个奇数，任意一个数的奇偶性不变；除以一个偶数，奇偶性不确定。
3. $g\neq1$时，除以$g$的操作不会进行超过$30$次。

考虑先手。
假设当前$\sum(A_i-1)$的奇偶性为奇数，即处于优势，那么他应该保持操作完（所有数除以$g$后）所有数的奇偶性还是偶数。
注意到当有至少一个奇数时，$GCD$不可能为偶数。而最初所有数的$GCD$为$1$，那么至少有一个奇数。另外此时偶数有奇数个，如果任意修改一个偶数，$g$一定还是奇数。
考虑现在的后手。先手进行上述操作后存在至少两个奇数，所以一定不能使$g$变为偶数来改变局面。而先手可以保持奇数的个数一直增加，所以后手没法翻盘，必败。

如果当前$\sum(A_i-1)$的奇偶性为偶数，即处于劣势，那么先手要使操作后的$g$变为偶数才可能翻盘。
由上面的分析，如果存在$>1$个的奇数，先手必败。否则先手只能修改这个奇数让$g$变成偶数。但是现在仍不能判断胜负，继续递归下一层。

最多递归$\log$层，所以复杂度$O(n\log A)$。（似乎还有个求$\gcd$...）
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int n,A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
bool DFS(bool now)
{
	int s=0,fg=0;
	for(int i=1; i<=n; ++i) A[i]==1&&(fg=1), s+=A[i]&1;
	if((n-s)&1) return now;
	if(fg||s>1) return now^1;
	for(int i=1; i<=n; ++i)
		if(A[i]&1) {--A[i]; break;}
	int g=A[1];
	for(int i=2; i<=n; ++i) g=std::__gcd(g,A[i]);
	for(int i=1; i<=n; ++i) A[i]/=g;
	return DFS(now^1);
}

int main()
{
	const int n=read(); ::n=n;
	for(int i=1; i<=n; ++i) A[i]=read();
	puts(DFS(1)?"First":"Second");

	return 0;
}
