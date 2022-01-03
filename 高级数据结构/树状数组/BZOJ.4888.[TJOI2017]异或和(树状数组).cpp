/*
3652kb	1036ms
$Description$
求所有区间和的异或和。
$n\leq 10^5,\ \sum a_i\leq 10^6$。
$Solution$
这样的题还是要先考虑按位做。
记$s_i$表示前缀和（$s_0$=0）。假设当前是第$k$位，我们要统计区间和在第$k$位为$1$的区间有多少个（或是奇偶性）。
枚举区间右端点$i$，然后我们要统计有多少个$s_i-s_j$在第$k$位为$1$。
当$s_i$第$k$位为$1$时：
　　如果$s_j$第$k$位为$0$，那$s_j$的后$k$位必须小于等于$s_i$的后$k$位才不会发生退位，$s_i$第$k$位上的$1$才能保留。
　　如果$s_j$第$k$位为$1$，那$s_j$的后$k$位必须大于$s_i$的后$k$位，才能退位使得$s_i-s_j$的第$k$位为$1$。
当$s_i$第$k$位为$0$时，同理讨论一下就可以了。（其实要注意$s_i$是不减的，这样前$k$位的影响很容易被处理掉）
所有数的和是$\leq10^6$的。所以对于每一位，我们用两个权值树状数组维护第$k$位为$0/1$的$s_i$的后$k$位就可以了。
复杂度$O(n\log^2A)$。
似乎还可以只用[一个树状数组]做？~~不管了懒得思考.jpg。~~大体看了下，差不多也是这样讨论，但是可以直接求区间和代替，不需要讨论$s_j$这一位是0还是1...
还可以用[FFT]做（虽然常数有点大过不去），但是我怎么看不懂啊=-=。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int sum[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct BIT
{
	#define N 1000005
	int n;
	bool t[N];
	#undef N
	#define lb(x) (x&-x)
	inline void Clear()
	{
		memset(t,0,n+1<<1);
	}
	inline void Add(int p)
	{
		for(; p<=n; p+=lb(p)) t[p]^=1;
	}
	inline bool Query(int p)
	{
		bool res=0;
		for(; p; p^=lb(p)) res^=t[p];
		return res;
	}
}T0,T1;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+read();
	int ans=0;
	for(int k=0; 1<<k<=sum[n]; ++k)
	{
		T0.Clear(), T1.Clear();
		T0.n=T1.n=1<<k, T0.Add(1);
		int s=0;
		for(int i=1,t0=1,t1=0,lim=(1<<k)-1; i<=n; ++i)
		{
			int val=sum[i]&lim;
			if(sum[i]>>k&1)
				s^=t1^T1.Query(val+1)^T0.Query(val+1), T1.Add(val+1), t1^=1;//(t1-T1.Query(val+1)+T0.Query(val+1))&1, ++t1;
			else
				s^=t0^T0.Query(val+1)^T1.Query(val+1), T0.Add(val+1), t0^=1;//(t0-T0.Query(val+1)-T1.Query(val+1))&1, ++t0;
		}
		ans+=s<<k;
	}
	printf("%d\n",ans);

	return 0;
}
