/*
624MS	9416K
$Description$
给定一张$n$个点$m$条边的无向图。定义割集$E$为去掉$E$后使得图不连通的边集。定义一个bond为一个极小割集（即bond中边的任意一个真子集都不是割集）。
对每条边，求它在多少个bond中。
$n\leq20,\quad n-1\leq m\leq\frac{n(n-1)}{2}$。
$Solution$
首先bond是极小割集，所以一定是将图分成了**两个连通块**。
状压表示点集，如果$s$是一个连通块，且剩下的所有点$s'=2^n-1-s$也是一个连通块，那么$s$与$s'$之间的边就形成了一个bond，这些边的$ans$++。
所以，我们只需要枚举一个连通块$s$。
然后怎么统计边的答案呢？显然不能枚举一遍bond中的边，那样复杂度就成了$O(2^nm)$。
总的bond个数可以这样求出来。
如果一条边$(u,v)$不在bond中，显然$u,v$此时在同一连通块中。也就是我们求一下$u,v$在同一连通块时bond有多少个，就是这条边不在多少个bond中了。用总个数一减就可以得到这条边的答案。
$u,v$在同一连通块时bond的个数，就是包含$\{u,v\}$的集合中有多少个bond。那么就可以用高维前缀和枚举超集得到答案了。
复杂度$O(2^nn)$。
还有一个问题是，要预处理哪些集合是一个连通块。
递推一下，枚举当前已经是一个连通块的点集，那么每次加入一个与该点集相邻的点，形成的仍然是一个连通块。
复杂度也是$O(2^nn)$。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=(1<<20)+4;

int e[25],f[N],sum[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Pre(int n)
{
	for(int i=0; i<n; ++i) f[1<<i]=1;//not f[i]...
	for(int s=0,lim=1<<n; s<lim; ++s)
	{
		if(!f[s]) continue;
		for(int i=0; i<n; ++i)
			if(!(s>>i&1) && s&e[i]) f[s|(1<<i)]=1;
//		int adj=0;
//		for(int i=0; i<n; ++i) s>>i&1&&(adj|=e[i]);
//		for(int i=0; i<n; ++i)
//			if(!(s>>i&1) && adj>>i&1) f[s|(1<<i)]=1;
	}
}

int main()
{
	static int u[500],v[500];

	for(int TT=read(),T=1; T<=TT; ++T)
	{
		int n=read(),m=read(),lim=1<<n;
		memset(e,0,sizeof e), memset(f,0,lim<<2), memset(sum,0,lim<<2);
		for(int i=1; i<=m; ++i)
			u[i]=read(), v[i]=read(), e[u[i]]|=1<<v[i], e[v[i]]|=1<<u[i];
		Pre(n);
		int tot=0;
		for(int s=0; s<lim; ++s)
		{
			if(!f[s]||!f[lim-1-s]) continue;
			if(s>lim-1-s) break;
			sum[s]=1, sum[lim-1-s]=1, ++tot;
		}
		for(int i=0; i<n; ++i)
			for(int s=0; s<lim; ++s)
				if(!(s>>i&1)) sum[s]+=sum[s|(1<<i)];
//		for (int i = 1; i <= s; i += 2)
//			if (f[i] ^ f[s ^ i]) f[i] = f[s ^ i] = 0; else if(f[i]) ++tot;
//		for (int i = 0; i < n; ++i)
//			for (int j = 0; j <= s; ++j)
//				if (!(j & (1 << i))) f[j] += f[j | (1 << i)];
		printf("Case #%d:",T);
		for(int i=1; i<=m; ++i)
			printf(" %d",tot-sum[(1<<u[i])|(1<<v[i])]);
		putchar('\n');
	}
	return 0;
}
