/*
824kb	16ms
$Description$
给定$n$，对于方程$x\oplus 3x=2x$，需求出：
1. 有多少$x\leq n$的正整数解。
2. 有多少$x\leq 2^n$的正整数解，模1e9+7。
$n\leq 10^{18}, 1000$组数据。
$Solution$
`x^3x=2x -> x^2x=3x`
因为`a^b + ((a&b)<<1)=a+b`，`x^2x = x+2x`，所以x和2x的二进制表示中不存在相邻的1。
（或者，因为`x+2x=3x`，所以`x^2x`没有抵消任何的1，所以x和2x没有相邻的1）
那么第一问数位DP，第二问上界为$2^n$，按位DP就行了。
$f[i]$表示到第$i$位的方案数。每位要么填$0$要么填$1$，所以$f[i]=f[i-1]+f[i-2]$。就是斐波那契数列（从斐波那契表示法也能看出与这个DP的类似）。
答案是$f[n+1]$（$2^n$是$n+1$位。。==）

好像第一问能用类似二进制拆分的方法O(64)做？https://blog.csdn.net/jr_mz/article/details/50351557 。不想看了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
typedef long long LL;
const int N=66;

int bit[N];
LL f[N][2];
bool vis[N][2];
struct Matrix
{
	int a[2][2];
	Matrix operator *(const Matrix &x)const
	{
		Matrix res;
		for(int i=0; i<2; ++i)
			for(int j=0; j<2; ++j)
			{
				LL tmp=1ll*a[i][0]*x.a[0][j]+1ll*a[i][1]*x.a[1][j];
				res.a[i][j]=tmp%mod;
			}
		return res;
	}
};

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int FP(Matrix x,LL k)
{
	Matrix t=x;
	for(--k; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return (t.a[0][0]+t.a[0][1])%mod;
	return t.a[0][0];
}
LL DFS(int x,int lim,int las)
{
	if(!x) return 1;
	if(!lim && vis[x][las]) return f[x][las];

	LL res=0; int up=lim?bit[x]:1;
	res+=DFS(x-1,lim&&!up,0);
	if(up&&!las) res+=DFS(x-1,lim&&up,1);

	if(!lim) vis[x][las]=1,f[x][las]=res;
	return res;
}
LL Solve(LL n)
{
	int cnt=0;
	for(; n; bit[++cnt]=n&1, n>>=1);
	return DFS(cnt,1,0)-1;
}

int main()
{
	Matrix mat;
	mat.a[0][0]=mat.a[0][1]=mat.a[1][0]=1, mat.a[1][1]=0;
	for(int T=read(); T--; )
	{
		LL n=read();
		printf("%lld\n%d\n",Solve(n),FP(mat,n));
	}
	return 0;
}
