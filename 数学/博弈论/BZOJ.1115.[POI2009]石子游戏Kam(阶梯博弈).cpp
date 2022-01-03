/*
1120kb	4ms
$Description$
有$n$堆石子。除了第一堆外，每堆石子个数都不少于前一堆的石子个数。两人轮流操作，每次可以从一堆石子中拿掉任意多的石子，但要保证操作后仍然满足初始时的条件。谁没有石子可拿时输。求先手是否必胜。
$Solution$
限制条件就是相邻两个数的差非负。那么记查分数组$d_i=a_i-a_{i-1}$。假设拿走第$i$堆的$x$个石子，影响是$d_i$-=$x$，$d_{i+1}$+=$x$，就相当于从$d_i$中拿$x$个给$d_{i+1}$。
显然原题意和对差分数组做反向的阶梯$Nim$是等价的，然后就做完啦。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1005;

int A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0; register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	for(int T=read(); T--;)
	{
		const int n=read();
		for(int i=1; i<=n; ++i) A[i]=read();
		int s=0;
		for(int i=n; i>=1; i-=2) s^=(A[i]-A[i-1]);
		puts(s?"TAK":"NIE");
	}

	return 0;
}
