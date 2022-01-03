/*
62ms	0KB
$Description$
给定一个$n\times m$的矩阵$A_{i,j}$，每次可以将一列或一行取负。求一个方案使得若干次操作后，每行每列的和都非负。
$n,m\leq100,\ 元素绝对值|A_{i,j}|\leq100$。

$Solution$
容易想到每次找和为负的一行或一列取负。这样做正确性及复杂度会有啥问题么？
注意到每次取负，所有数的和是单调递增的，所以一定会结束。且每次和至少会增加$2$（$-1\to1$），而所有数的和最小是$-10^6$，最大是$10^6$，所以最多操作$10^6$次，复杂度$O(10^6n)$。
自己写了写，写的真是麻烦。。不需要`queue`，每次$O(nm)$`for`一遍反转行列即可。
*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
typedef long long LL;
const int N=105;

int A[N][N];
bool x[N],y[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Print(bool *a,int n)
{
	int t=0;
	for(int i=1; i<=n; ++i) t+=a[i];
	printf("%d ",t);
	for(int i=1; i<=n; ++i) a[i]&&printf("%d ",i);
	putchar('\n');
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) A[i][j]=read();
	for(; ; )
	{
		bool ok=1;
		for(int i=1; i<=n; ++i)
		{
			int s=0;
			for(int j=1; j<=m; ++j) s+=x[i]^y[j]?-A[i][j]:A[i][j];
			if(s<0) x[i]^=1, ok=0;
		}
		for(int j=1; j<=m; ++j)
		{
			int s=0;
			for(int i=1; i<=n; ++i) s+=x[i]^y[j]?-A[i][j]:A[i][j];
			if(s<0) y[j]^=1, ok=0;
		}
		if(ok) break;
	}
	Print(x,n), Print(y,m);

	return 0;
}
