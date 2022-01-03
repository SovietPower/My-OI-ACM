/*
358ms	3600KB
$Description$
设$k$表示将一个排列$A_i$划分成若干个递增或递减子序列，所需子序列个数的最小值。令$f(n)$表示所有$1...n$的排列中，$k$的最大值。（有点绕...就是用最少的序列划分排列，$f(n)$是所有$1$到$n$的排列中所需序列最多的那个个数）
$T$次询问，每次给定一个$1...n$的排列$A_i$，你需要将其分成$k\leq f(n)$段递增或递减的序列并输出方案（不要求$k$最小，只需$\leq f(n)$）。
$T,\sum n\leq10^5$。

$Solution$
首先考虑$f(n)$是多少。
随便找一些排列比如题解中的这个：$\{1, 3, 2, 6, 5, 4, 10, 9, 8, 7, 15, 14, 13, 12, 11\}$，$k=5$，能发现$k$是最大的满足$\frac{i(i+1)}{2}\leq n$的正整数$i$。
所以我们猜$f(n)=k$，其中$k$是最大的满足$\frac{k(k+1)}{2}\leq n$的正整数。
事实上确实可以证明。也就是对于任意$n<\frac{k'(k'+1)}{2}$，总能将序列分成不超过$k'-1$个单调子序列。

设$LIS$为此时的最长上升子序列，若$|LIS|\geq k'$，删掉$LIS$，则此时$n-|LIS|<\frac{k'(k'+1)}{2}-k'=\frac{(k'-1)k'}{2}$，显然是一个同样的规模更小的问题。
否则$|LIS|\leq k'-1$，由$Dilworth$定理，$最小链覆盖=最长反链$，本题中就是$下降子序列个数=最长上升子序列长度\leq k'-1$。（对于$i<j,A_i>A_j$，连单向边$i\to j$，则最长反链即$LIS$，任意一条路径即下降子序列）
所以此时可以将序列分成不超过$k'-1$个下降子序列。

证完了。。也是够神。。不知道别的可能的做法，懒得看了。。

输出$|LIS|$个下降子序列时，令$f[i]$表示以$i$结尾的$LIS$长度，把$f[i]$相同的位置划分到同一个子序列中就可以了。（显然这些数是递减的）
复杂度$O(n\sqrt{n}\log n)$（需要$O(\sqrt{n})$次$LIS$）。
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int tot,A[N],f[N];
std::vector<int> ans[N];
struct BIT
{
	int n,t[N];
	#define lb(x) (x&-x)
	inline int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res=std::max(res,t[p]);
		return res;
	}
	inline void Modify(int p,int v)
	{
		for(; p<=n; p+=lb(p)) t[p]=std::max(t[p],v);
	}
	inline void Clear(int p)
	{
		for(; p<=n; p+=lb(p))
			if(!t[p]) break;
			else t[p]=0;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Solve(int n)
{
	static bool vis[N];
	int mx=0;
	for(int i=1; i<=n; ++i) mx=std::max(mx,f[i]=T.Query(A[i]-1)+1), T.Modify(A[i],f[i]);
	for(int i=1; i<=n; ++i) T.Clear(A[i]);
	int l=1,r=sqrt(n*2),mid;
	while(l<r)//k(k+1)/2<=n (k+1)(k+2)/2>n
		if(mid=l+r>>1,mid*(mid+1)>n*2) r=mid;//可能会爆int。。但k的上界是sqrt(2n)。
		else l=mid+1;
	int k=l;
	if(mx>=k)
	{
		++tot;
		for(int i=n,now=mx,v=N; i; --i)
			if(f[i]==now && A[i]<v)
				--now, v=A[i], vis[i]=1, ans[tot].push_back(A[i]);
		std::reverse(ans[tot].begin(),ans[tot].end());
		int cnt=0;
		for(int i=1; i<=n; ++i)
			if(!vis[i]) A[++cnt]=A[i];
			else vis[i]=0;
		if(cnt) Solve(cnt);
	}
	else
	{
		for(int i=1; i<=n; ++i) ans[tot+f[i]].push_back(A[i]);
		tot+=mx;
	}
}

int main()
{
	for(int Tot=read(); Tot--; )
	{
		const int n=read(); T.n=n;
		for(int i=1; i<=n; ++i) A[i]=read();
		tot=0, Solve(n);
		printf("%d\n",tot);
		for(int i=1; i<=tot; ++i,putchar('\n'))
		{
			printf("%d",ans[i].size());
			for(int j=0,l=ans[i].size(); j<l; ++j) printf(" %d",ans[i][j]);
			ans[i].clear();
		}
	}
	return 0;
}
