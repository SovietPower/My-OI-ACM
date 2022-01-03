/*
4ms	640KB
记起点为$S$，终点为$T$，走过的最靠左的点是$L$，最靠右的点是$R$。
那么坐标轴被分成了五段：
$0\sim L-1$：经过$0$次；
$L\sim S-1$：经过偶数次；
$S\sim T$：经过奇数次；
$T+1\sim R$：经过偶数次；
$R+1\sim\infty$：经过$0$次。
第二段和第四段可以经过$0$次（也就是可以没有第二段或第四段）。注意如果是第二/三/四段$A_i=0$的话会有花费。
$f[i][j]$表示到$i$点，处在第$j$段，的最小花费。转移很简单。
复杂度$O(n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(); LL f[5]={0};
	for(int i=1; i<=n; ++i)
	{
		int ai=read();
		LL mn=f[0]; f[0]=f[0]+ai;
		mn=std::min(mn,f[1]), f[1]=mn+(ai?ai&1:2);
		mn=std::min(mn,f[2]), f[2]=mn+(ai?ai+1&1:1);
		mn=std::min(mn,f[3]), f[3]=mn+(ai?ai&1:2);
		mn=std::min(mn,f[4]), f[4]=mn+ai;
	}
	printf("%lld\n",std::min(f[2],std::min(f[3],f[4])));

	return 0;
}
