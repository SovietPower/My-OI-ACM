/*
17424kb	2664ms
$Description$
给定一个序列$A_i$。求有多少个子区间，满足该区间众数出现次数大于区间长度的一半。
$n\leq5\times10^5,\ 0\leq A_i\lt n$。
$Solution$
考虑$x$作为众数合法的区间有哪些。令$B_i=\ A_i==x?1:-1$，对$B_i$求个前缀和$s_i$（区间和->两点）。那么区间$[l,r]$合法当且仅当$s_r-s_{l-1}\gt0$。
其实就是对$s_i$求顺序对个数。用树状数组或者值域线段树可以$O(n\log n)$，那么总复杂度是$O(n^2\log n)$的（枚举$O(n)$次$x$）。（但是这样可以过$type=1$的点了）
考虑枚举$x$作为众数时，$B_i,s_i$有什么性质。
$Sol1$
我们发现$B$序列会有少数$1$和很多连续的$-1$段。连续的$-1$是可以一起求的。
用线段树维护$s$的值域中（$[-n,n]$）每个值之前出现过多少次。
假设其中一段极长$-1$段是$[l,r]$，$s_{l-1}=sum$，因为$s_i$是递减的，容易发现对这段区间，依次要查询的是$[-n,sum-2],[-n,sum-3],...$这些区间的和。然后这段区间的更新就是对$[sum-1,sum-(r-l+1)]$整体$+1$。
考虑查询的时候具体是求什么。设$T_i$为树状数组/线段树上下标$i$位置的值（$i$之前出现的次数），$len=r-l+1$。考虑$T_i$被统计的次数，有$$Ans=\sum_{i=-n}^{sum-1-len}len*T_i+\sum_{i=sum-len}^{sum-2}T_i(sum-1-i)$$

所以用线段树维护$\sum T_i,\ \sum i*T_i$就好啦。复杂度$O(n\log n)$。
树状数组也可以维护（区间加等差数列？），然而没看懂怎么实现，可以看[这篇博客](https://blog.csdn.net/baidu_36797646/article/details/80081085)orz。

$Sol2$
另一种做法是[TA爷(~~？好像都这么叫~~)的做法](https://blog.csdn.net/TA201314/article/details/78948477)。
还是考虑优化枚举众数$x$后的求解方法。
因为序列里会有很多$-1$，称能够出现和为正的区间叫合法区间。那么$i$能作为某个极长合法区间的右端点$r$当且仅当，$B_l+B_{l+1}+..+B_i=0$，且$i$后面的最大前缀和非正。左端点同理。
怎么找呢。就是拿$+1$往左右推，遇到$-1$就用$+1$填，没有$+1$了就结束。这样会将序列分割成一段段小区间，每段小区间是合法的。（不知道怎么说.jpg）
不难发现对所有数枚举这些小区间是$O(n)$的。所以拿上面那个$O(n^2\log n)$的算法直接分别处理这些小区间就好了。复杂度$O(n\log n)$。
就是单点加区间查，可以直接树状数组。

$Sol3$
有种（感觉比较暴力的）分治做法。
设当前区间是$[l,r]$，中点为$mid$。注意到一个性质是，若$x$是区间$[l,r]$的众数，那么对于任意$k\in[l,r)$，$x$至少是区间$[l,k]$或区间$(k+1,r]$的众数。那么取$k=mid$，先求子区间就可以求出所有经过$mid$的区间中，可能作为众数的数有哪些。注意一个区间的众数只有$O(\log n)$个。
然后就可以枚举每个众数，看它的子区间有哪些。从$mid$往左往右扫两次就差不多惹。
复杂度$O(n\log^2n)$。实际跑起来挺优秀的叭。（可能还比$Sol2$优？）

似乎还有$O(n)$的？emm见LOJ统计叭。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int beg[N],ed[N],pre[N],nxt[N],A[N],B[N];
bool tag[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct BIT
{
	int D,n,t[N<<1];
	#define lb(x) (x&-x)
	void Add(int p,int v)
	{
		for(p+=D; p<=n; p+=lb(p)) t[p]+=v;
	}
	int Query(int p)
	{
		int res=0;
		for(p+=D; p; p^=lb(p)) res+=t[p];
		return res;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read(); read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) pre[i]=ed[A[i]], ed[A[i]]=i;
	for(int i=n; i; --i) nxt[i]=beg[A[i]], beg[A[i]]=i;
	LL ans=0; T.D=n, T.n=n<<1, T.Add(0,1);
	for(int x=0; x<n; ++x)
	{
		if(!beg[x]) continue;
		for(int i=beg[x]; i; )
		{
			int p=i; B[p]=1;//
			for(int t=1; p<=n&&t>=0; ++p,t+=B[p]=(A[p]==x?1:-1)) tag[p]=1;
			while(i && i<p) i=nxt[i];
		}
		for(int i=ed[x]; i; )
		{
			int p=i; B[p]=1;
			for(int t=1; p&&t>=0; --p,t+=B[p]=(A[p]==x?1:-1)) tag[p]=1;
			while(i>p) i=pre[i];
		}
		for(int i=beg[x]; i; )
		{
			int p=i;
			while(tag[p-1]) --p;
			int tmp=p,t=0;
			while(p<i) T.Add(--t,1), ++p;//这部分显然没有Query的必要。
			while(tag[p]) T.Add(t+=B[p],1), ans+=T.Query(t-1), ++p;
			p=tmp,t=0;
			while(p<i) T.Add(--t,-1), tag[p++]=0;
			while(tag[p]) T.Add(t+=B[p],-1), tag[p++]=0;
			while(i && i<=p) i=nxt[i];//<=
		}
	}
	printf("%lld\n",ans);

	return 0;
}
