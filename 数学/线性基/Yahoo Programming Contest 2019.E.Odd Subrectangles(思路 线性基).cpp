/*
7ms	896KB
$Description$
给定一个$n\times m$的$01$矩阵。求任意选出$r$行、$c$列（共$2^{n+m}$种方案），使得这$r$行$c$列的交的位置的$r\times c$个数的和为奇数，的方案数有多少。
$n,m\leq300$。

$Solution$
假设已经确定了选择某些行，然后把每一行$m$个数看做一个$m$位二进制数。
如果这些行异或和为$0$，那怎么选列也不行。
否则每一列异或这些行是$0$还是$1$是确定的。假设有$a$列异或后为$1$，$b$列异或后为$0$，$a+b=m$。我们要从$a$中选出奇数个，从$b$中随便选，那么方案数是$2^{a-1}\cdot2^b=2^{m-1}$（从$n$中选出奇数个数的方案数。。$C_n^1+C_n^3+C_n^5+...=\frac{2^n}{2}=2^{n-1}$）。
也就是不管行怎么选，只要异或和不为$0$，列就有$2^{m-1}$种方案。
异或和不为$0$的方案数=$2^n-$异或和为$0$的方案数。异或和为$0$的方案数可以用线性基求，是$2^{n-r}$（$n$是元素总数，$r$是矩阵的秩，也就是线性基中的元素个数），所以答案就是$(2^n-2^{n-r})\cdot2^{m-1}$。
这里线性基插入还是一样的，把一行看做$m$位数就好了。
复杂度$O(n^3)$或$O(\frac{n^3}{w})$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 998244353
typedef long long LL;
const int N=305;

int A[N][N],B[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) A[i][j]=read();
	int r=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(A[i][j])//x>>j&1
			{
				if(B[j][j]) for(int k=j; k<=m; ++k) A[i][k]^=B[j][k];
				else
				{
					for(int k=j; k<=m; ++k) B[j][k]=A[i][k];
					++r; break;
				}
			}
	printf("%d\n",(FP(2,n+m-1)+mod-FP(2,n-r+m-1))%mod);

	return 0;
}
