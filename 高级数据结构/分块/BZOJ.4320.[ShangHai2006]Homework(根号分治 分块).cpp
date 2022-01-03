/*
3656kb	1208ms
$\mathbb{mod}$一个数$y$的最小值，可以考虑枚举剩余系，也就是枚举区间$[0,y),[y,2y),[2y,3y)...$中的最小值（求后缀最小值也一样）更新答案，复杂度是$O(\frac ny)$的。注意到$y>\sqrt n$时，枚举次数$<\sqrt n$。

我们可以对$y$根号分治，设$m=\sqrt{V}$（$V$是值域）。
当$y\leq m$时，可以维护一个大小为$m$的桶$s_i$（表示模数为$i$时的$\min\{a\ \mathbb{mod}\ i,a\in S\}$），插入一个数时更新所有桶的值，查询时直接输出。
当$y>m$时，枚举$[0,y),[y,2y),[2y,3y)...$这些权值区间求最小值，为了方便可以直接求后缀最小值，也就是$0,y,2y...$这些位置的后缀最小值。
枚举的复杂度是$O(\sqrt V)$的，怎么$O(1)$求一个位置的后缀最小值呢。
不妨每次插入$a$就对$1\sim a$这些位置与$a$取$\min$。我们对值域分块，这样更新的复杂度是$O(\sqrt V)$的，查询某个位置的后缀最小值是$O(1)$的。
然后总复杂度就是$O(n\sqrt V)$了。

查后缀最小值也就是这个数往后的一个数是多少。因为只有插入，离线之后也可以看成只有删除，右边第一个数是可以并查集维护的。删掉一个数就是合并两个位置。
复杂度$O(n\sqrt V\alpha(V))$，也可以过。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+3,INF=1<<30,size=548;//(int)sqrt(3e5); //BZOJ编译器版本低到这样写会CE? = = 
//最大值(初值)不能是N！N对一个大数取模后可能还更小。。
int g[size+3],bel[N],tag[size+3],mn[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline char GetOpt()
{
	register char c=gc();
	while(c!='A'&&c!='B') c=gc();
	return c;
}
inline void Add(const int x)
{
	for(int i=1; i<=size; ++i) g[i]=std::min(g[i],x%i);
	for(int i=0,l=bel[x]; i<l; ++i) tag[i]=std::min(tag[i],x);
	for(int i=bel[x]*size; i<=x; ++i) mn[i]=std::min(mn[i],x);
}
inline int Query(const int x)
{
	if(x<=size) return g[x];
	int res=INF;
	for(int i=0; i<N; i+=x)
		res=std::min(res,std::min(mn[i],tag[bel[i]])-i);
	return res;
}

int main()
{
	for(int i=0; i<=size; ++i) g[i]=INF, tag[i]=INF;
	for(int i=0; i<N; ++i) bel[i]=i/size, mn[i]=INF;
	for(int Q=read(); Q--; )
		switch(GetOpt())
		{
			case 'A': Add(read()); break;
			case 'B': printf("%d\n",Query(read())); break;
		}

	return 0;
}
