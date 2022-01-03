/*
30120kb	2680ms
首先暴力DP，$f[i][j][0/1]$表示当前是第$i$个数，所有数的和模$P$为$j$，有没有出现过质数的方案数。
我们发现每一次的转移都是一样的。
假设没有第三维$0/1$，那如果拿DP数组$f[i]$和$f[i]$组合，得到的就是$f[2\times i]$（$i$次DP后的结果与$i$次DP后的结果组合，就是$2\times i$次DP后的结果）。所以有：$f[2\times i][(j+k)\%p]=\sum\limits_{j=0}^{P-1}\sum\limits_{k=0}^{P-1}f[i][j]\times f[i][k]$。
而第三维代表的意思是，有没有出现过质数。容斥一下，拿没有使用数限制DP出来的结果，减去，一个质数都不用DP出来的结果，就是答案了。
所以就可以倍增/快速幂（并不需要矩阵快速幂）。一次DP是$O(p^2)$的，复杂度$O(m+p^2\log n)$。

其实和[[SDOI2015]序列统计](https://www.luogu.org/problemnew/show/P3321)比较像，所以有很多人写的循环卷积，好像确实可以优化到$O(m+p\log p\log n)$，但是这题显然用不到...
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod 20170408
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=2e7+5,M=102;

bool notP[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void Init(const int n)
{
	static int cnt,P[N>>3];
	notP[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!notP[i]) P[++cnt]=i;
		for(int j=1; j<=cnt&&1ll*i*P[j]<=n; ++j)//LL!
		{
			notP[i*P[j]]=1;
			if(!(i%P[j])) break;
		}
	}
}
void Mult(int *f,int *g,int P)
{
	static int res[M];
	memset(res,0,sizeof res);
	for(int i=0; i<P; ++i)
		if(f[i])
			for(int j=0,v; j<P; ++j)
				if(g[j])
					v=i+j>=P?i+j-P:i+j, Add(res[v],1ll*f[i]*g[j]%mod);
	memcpy(f,res,sizeof res);
}
int Solve(int k,int m,int P)
{
	static int x[M],t[M];
	memset(x,0,sizeof x);
	for(int i=1; i<=m; ++i) if(notP[i]) Add(x[i%P],1);//++ not =1!!
	memcpy(t,x,sizeof x);
	for(--k; k; k>>=1,Mult(x,x,P))
		if(k&1) Mult(t,x,P);
	return t[0];
}

int main()
{
	const int n=read(),m=read(),P=read();
	Init(m);
	int t=Solve(n,m,P);
	for(int i=1; i<=m; ++i) notP[i]=1;
	printf("%d\n",(Solve(n,m,P)+mod-t)%mod);

	return 0;
}
