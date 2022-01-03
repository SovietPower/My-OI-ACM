/*
27376kb	9684ms
显然如果有能力牌，那么应该选最大的尽可能的打出$k-1$张。
然后下面说的期望都是乘总方案数后的，即所有情况的和。然后$w_i$统一用$A_i$表示了。

$Sol1$
所以考虑枚举最终抽到了几张能力牌。那么我们要算：$F(n,m)$表示抽到$n$张攻击牌，打出最大的$m$张的期望伤害；$G(n,m)$表示抽到$n$张能力牌，打出最大的$m$张的期望倍数。
考虑怎么算$F(n,m)$。不妨枚举攻击最小的那张是什么。也就是把攻击牌从大到小排序，$f[i][j]$表示在前$i$张中选$j$张的期望伤害，其中第$i$张一定取。转移就再枚举一下次小的，$f[i][j]=C_{i-1}^{j-1}A_i+\sum\limits_{k=j-1}^{i-1}f[k][j-1]$。
$G(n,m)$同理。令$g[i][j]$表示从前$i$大的能力牌中选$j$张的期望倍数，其中第$i$张一定取。$g[i][j]=A_i\sum\limits_{k=j-1}^{i-1}g[k][j-1]$。
两个DP都可以前缀和优化。所以复杂度是$O(n^2)$的。

那么$F,G$的转移同样枚举选出来的最小的那张，$F(n,m)=\sum\limits_{i=m}^{N}C_{N-i}^{n-m}f[i][m]$，$G(n,m)=\sum\limits_{i=m}^{N}C_{N-i}^{n-m}g[i][m]$。对于单个$F/G(n,m)$的计算是$O(n)$的。
然后$Ans=\sum\limits_{i=1}^{k-1}G(i,i)F(m-i,k-i)+\sum\limits_{i=k}^NG(i,k-1)F(m-i,1)$。我们只会用到$O(n)$个$F/G$的值，现算一下即可，总复杂度是$O(n^2)$的。

为了方便应该把$f/g$的一二维交换下=-=。

$Sol2$
设$f[i][j]$表示考虑了前$i$张牌，抽到了$j$张攻击牌的期望伤害。肯定是选出最大的若干张打出。将牌从小到大排序，然后根据$j$确定这张牌选不选，有$$f[i][j]=f[i-1][j]+C_{i-1}^{j-1}A_i+\begin{cases}0,&m-j\geq k-1\\f[i-1][j-1],&m-j<k-1\end{cases}$$

考虑$i$的贡献，$m-j\geq k-1$时，只能取一张攻击牌，那取$i$就能保证打出的是最大的那张；否则取完$i$之后还可以在取$j-1$张的情况。然后再统计上以前的只考虑$i-1$张牌时的$f[i-1][j]$（注意这个=-=）。
$g[i][j]$表示考虑了前$i$张牌，抽到了$j$张能力牌的期望倍数。因为是选最大的$\min(k-1,\ j)$张打出，所以把能力牌从大到小排序，有$$g[i][j]=g[i-1][j]+\begin{cases}g[i-1][j-1]*A_i,&j<k\\g[i-1][j-1],&j\geq k\end{cases}$$

就是$j<k$时用$A_i$，否则抽到$A_i$也不用。
那么答案就是$\sum_{i=0}^mf[n][i]g[n][m-i]$啦。
复杂度也是$O(n^2)$，不过常数要更小。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <functional>
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define gc() getchar()
typedef long long LL;
const int N=1505;

int A[N],B[N],f[N][N],g[N][N],C[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int F(int n,int m,int N)
{
	LL ans=0; int *f=::f[m];
	for(int i=m; i<=N; ++i) ans+=1ll*C[N-i][n-m]*f[i]%mod;
	return ans%mod;
}
int G(int n,int m,int N)
{
	LL ans=0; int *g=::g[m];
	for(int i=m; i<=N; ++i) ans+=1ll*C[N-i][n-m]*g[i]%mod;
	return ans%mod;
}

int main()
{
	C[0][0]=1;
	for(int Ts=read(),mx=0; Ts--; )
	{
		int n=read(),m=read(),K=read();
		if(mx<n)
		{
			for(int i=mx+1; i<=n; ++i)
			{
				C[i][i]=C[i][0]=1;
				for(int j=1; j<i; ++j) C[i][j]=C[i-1][j-1]+C[i-1][j], Mod(C[i][j]);
			}
			mx=n;
		}
		for(int i=1; i<=n; ++i) A[i]=read();
		for(int i=1; i<=n; ++i) B[i]=read();
		std::sort(A+1,A+1+n,std::greater<int>()), std::sort(B+1,B+1+n,std::greater<int>());

		g[0][0]=1;//!! K=1时会用到啊=-= 
		for(int i=1; i<=n; ++i) f[1][i]=B[i], g[1][i]=A[i];//or not
		for(int i=2,lim=std::min(n,m); i<=lim; ++i)
		{
			int sf=0,sg=0;
			for(int j=i; j<=n; ++j)
				Add(sf,f[i-1][j-1]), f[i][j]=(1ll*C[j-1][i-1]*B[j]+sf)%mod,
				Add(sg,g[i-1][j-1]), g[i][j]=1ll*A[j]*sg%mod;
		}
		LL ans=0;
		for(int i=std::max(0,m-n); i<=n&&i<=m; ++i)//m-i<=n 枚举的是能力牌 可以是0啊=v= 
			if(i<K) ans+=1ll*G(i,i,n)*F(m-i,K-i,n)%mod;
			else ans+=1ll*G(i,K-1,n)*F(m-i,1,n)%mod;
		printf("%lld\n",ans%mod);
	}

	return 0;
}
