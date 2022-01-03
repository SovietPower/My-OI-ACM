/*
1700kb	200ms
先考虑能否断环为链。显然是可以的，因为金币不可能在整个环上平移。所以我们枚举断点$k$，表示$k$和$k+1$之间不交换金币。
令$d_i=a_i-aver$，表示$i$需要给$i-1$的金币数量，$d_i$可正可负（负的就表示$i-1$给$i$ $d_i$个金币）。显然没必要再表示$i-1$给$i$的金币数量啊。
这样再对$d_i$求个前缀和$s_i$，$|s_i|$就表示$i$位置需转手多少金币。注意因为是均分所以$s_n=0$！
那么枚举断点$k$后，答案是$\sum_{i=k+1}^n|s_i-s_k|+\sum_{i=1}^k|s_i+s_n-s_k|$。（当然要加绝对值啊→_→，求的是区间和的绝对值）
因为$s_n=0$，所以所求就是$\sum_{i=1}^n|s_i-s_k|$。$s_k$取中位数时答案最小（向两边移动会造成更多的代价）。
简直傻了啊QAQ，这个题怎么都做了这么长时间啊。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define abs(x) (x<0?-(x):x)
typedef long long LL;
const int N=1e6+5;

int A[N];
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
	int n=read(); LL aver=0;
	for(int i=1; i<=n; ++i) aver+=A[i]=read();
	aver/=n;
	for(int i=1; i<=n; ++i) A[i]=A[i]-aver+A[i-1];
	std::nth_element(A+1,A+(n+1>>1),A+n+1);
	LL ans=0;
	for(int i=1,mid=A[n+1>>1]; i<=n; ++i) ans+=abs(A[i]-mid);
	printf("%lld\n",ans);

	return 0;
}
