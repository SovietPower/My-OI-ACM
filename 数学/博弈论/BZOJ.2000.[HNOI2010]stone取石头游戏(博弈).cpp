/*
17916kb	368ms
$Description$
有一些数字，被分成若干双端队列（从两边都可以取）和最多两个栈（只能从某一边一个一个取）的形式。两人轮流取这些数字，每个人都想最大化自己取到的数字和，求最后两人各能取到多少。
$n\leq10^6$。
$Solution$
对于最左边的栈，如果有$A_1\geq A_2$，那么先手取了$A_2$，后手一定会取走$A_1$（如果赚，显然后手要取；如果不赚，先手可以取别的最后依旧让后手取走）。同样扩展到左边连续递减的一段，两人都是轮流取的（这样$i$为奇数时，后手取$A_{i-1}$可能就不赚了）。
最右边的栈同理。
然后能发现，谁能取到最左和最右边的数只与数字总个数有关，如果一共奇数个，先手可以同时取走最左和最右，否则后手可以。（nb...感觉真要证会很复杂）
那么我们就可以处理完左右递减的那一段了。剩下的等会再说。

考虑双端队列，如果有$A_{i-1}\leq A_i\geq A_{i+1}$，且先手取走$A_{i-1}$，那么后手一定去取$A_i$，先手一定会取走$A_{i+1}$，所以收益差是固定的，为$A_i-A_{i-1}-A_{i+1}$。这里的先手是指取$A_{i-1}$的人。那么我们就可以将这三个数压成一个数，去求收益差。
那么我们就可以将这种上凸的情况全合并掉，把序列变成只有递减的、递增的、下凸的三种情况，显然这三种一定是从大到小轮流选的。

这样合并两个栈，因为左边递减的已经合并了，也没有上凸情况了，所以只剩下递增情况了。同样和双端队列那些放一起轮流选就行了。

最后求出个差，知道总数就知道答案了。
注意合并后的元素是可能出现$0$的，空位置要再开个数组判。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+5;

LL sk[N],A[N];
bool tag[N];
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
	int n=read(),top=0,sta=0;
	LL sum=0,ans=0;
	for(int i=1; i<=n; ++i)
	{
		sk[++top]=read();
		tag[top]=(sk[top]>0), sta^=(sk[top]>0), sum+=sk[top];
		while(top>2 && tag[top] && tag[top-1] && tag[top-2] && sk[top-1]>=std::max(sk[top-2],sk[top]))
			sk[top-2]=sk[top]+sk[top-2]-sk[top-1], top-=2;
	}
	int l=1,r=top,cnt=0,v=sta?1:-1;
	for(; tag[l]&&tag[l+1]&&sk[l]>=sk[l+1]; l+=2) ans+=v*(sk[l]-sk[l+1]);
	for(; tag[r]&&tag[r-1]&&sk[r]>=sk[r-1]; r-=2) ans+=v*(sk[r]-sk[r-1]);
	for(int i=l; i<=r; ++i) tag[i]&&(A[++cnt]=sk[i]);
	std::sort(A+1,A+1+cnt,std::greater<LL>());
	for(int i=1; i<=cnt; ++i) i&1?ans+=A[i]:ans-=A[i];
	printf("%lld %lld\n",sum+ans>>1,sum-ans>>1);

	return 0;
}
