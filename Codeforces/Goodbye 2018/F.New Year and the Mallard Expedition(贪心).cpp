/*
31ms	700KB
写了近一天，改了4遍越改越麻烦...mmp...
其实很好写...
先假设所有路程都飞过去，能量不够等会再补。则此时的答案为$ans=\sum\limits_{i=1}^nL_i$。
然后从$i=1\sim n$枚举。如果此时的能量不够飞$L_i$的距离，就从之前补。
所以记$W,G$分别表示之前飞过的$water$有多少、之前飞过的$grass$有多少。
显然能量来自，将飞过的$W$路程变成游过去，还不够的话将飞过的$G$路程变成走过去，再不够的话，如果出现过$water$就来回游补够能量，没出现过$water$就在$grass$来回走补够能量。
所以对于$L_i$，我们需要从$W$转移过来的能量有$t=\min\{L_i,2W\}$（$W$的路程能变成$2W$能量，因为是将原先的飞替换成游），也就是需要将之前$\frac t2$路程的飞变为游泳，来获得这$t$能量。所以$ans$+=$\frac t2\times2$，$W$-=$\frac t2$（为了避免小数将$W$*=$2$，此时就是$W$-=$t$）。
如果此时$L_i-t$仍不为$0$，那么同样从$G$转移。
还不为$0$，则如上所述来回游/走。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

char s[N];
LL A[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(); LL ans=0;
	for(int i=1; i<=n;++i) ans+=A[i]=read();
	scanf("%s",s+1);
	LL W=0,G=0;
	for(int i=1,cost=5; i<=n; ++i)
	{
		if(s[i]=='G') G+=A[i]<<1;
		else if(s[i]=='W') W+=A[i]<<1, cost=3;
		LL rest=A[i],t;
		t=std::min(rest,W), rest-=t, ans+=t, W-=t;
		t=std::min(rest,G), rest-=t, ans+=t<<1, G-=t;
		ans+=rest*cost;
	}
	printf("%I64d\n",ans);

	return 0;
}
