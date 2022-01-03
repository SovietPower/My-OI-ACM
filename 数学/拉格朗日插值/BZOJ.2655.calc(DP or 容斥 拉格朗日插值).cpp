/*
2804kb	160ms
$Description$
合法的序列定义为：长度为$n$，每个数在$[1,k]$内且两两不同。序列价值定义为所有数的乘积。求所有合法序列的价值和。模$p$。
$n\leq 500,\ k\leq 10^9,\ p\leq 10^9$且为质数。
$Solution$
首先把无序化成有序，选严格递增的数，最后乘个$n!$。
然后容易想到令$f_{i,j}$表示到第$i$个数，当前选的是$j$的价值和。复杂度是$O(nA)$的。~~然后忘掉这个做法吧这个做法没前途。~~
~~上面这个做法最后还要$O(A)$求一遍和，感觉不够优美。~~

直接令$f_{i,j}$表示选了$i$个数，选的最大的数$\leq j$的价值和。转移为：$f_{i,j}=f_{i,j-1}+f_{i-1,j-1}\times j$。
复杂度还是$O(nA)$。最后的答案就是$f_{n,A}$。
（以后遇到这种DP要注意）打表差分~~或是看题解~~可以发现，$f_{i,j}$是一个关于$j$的$2i$次的多项式。
把$f_{i,j}$展开大概就是这样：$f_{i,j}=\sum\limits_{k=1}^{j-1}f_{i-1,k}\times(k+1)$，求和会给多项式次数+1，乘$k+1$其实就是乘的$x+1$（并不算个常数），所以多项式次数也会+1，所以是$2i$次的。
那就可以暴力$n^2$DP算出$2n+1$个$f_{n,0,1...2n}$的值，然后拉格朗日插值就可以得到$f_{n,A}$了。
复杂度$O(n^2)$。

容斥：
令$f_i$表示$n=i$时的答案，转移的时候枚举，强制令$j$个数和$i$选的数相同，容斥一下，那么：
$$f_i=\sum\limits_{j=0}^{i-1}(-1)^jA_{i-1}^jf_{i-j-1}g(j+1)$$
其中$g(j)=\sum_{i=1}^Ai^j$，就是选$j$个相同数的贡献和。可以用伯努利数/拉格朗日插值$O(n^2)$预处理。
至于为啥是$A_{i-1}^j$不是$C_{i-1}^j$...不怎么会解释...不管了感性理解了。
代码是DP的。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=1003;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k,const int mod)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
int Lagrange(const int *y,const int n,const int x,const int mod)
{
	static int pre[N],suf[N],ifac[N];
	pre[0]=x, suf[n+1]=1; LL tmp=1;
	for(int i=1; i<=n; ++i) pre[i]=1ll*pre[i-1]*(x+mod-i)%mod, tmp=tmp*i%mod;
	ifac[n]=FP(tmp,mod-2,mod);
	for(int i=n; i; --i) suf[i]=1ll*suf[i+1]*(x+mod-i)%mod, ifac[i-1]=1ll*i*ifac[i]%mod;
	LL ans=0;
	for(int i=0,up,down; i<=n; ++i)
	{
		if(i) up=1ll*y[i]*pre[i-1]%mod*suf[i+1]%mod;
		else up=1ll*y[i]*suf[i+1]%mod;
		down=(n-i)&1?mod-1ll*ifac[i]*ifac[n-i]%mod:1ll*ifac[i]*ifac[n-i]%mod;
		ans+=1ll*up*down%mod;
	}
	return ans%mod;
}

int main()
{
	static int f[503][N];

	const int A=read(),n=read(),mod=read(),n2=n<<1;
	for(int i=1; i<=n2; ++i) f[1][i]=f[1][i-1]+i, Mod(f[1][i]);
	for(int i=2; i<=n; ++i)
		for(int j=1; j<=n2; ++j)
			f[i][j]=f[i][j-1]+1ll*f[i-1][j-1]*j%mod, Mod(f[i][j]);
	LL fac=1;
	for(int i=2; i<=n; ++i) fac=fac*i%mod;
	printf("%lld\n",fac*Lagrange(f[n],n2,A,mod)%mod);

	return 0;
}
//void Violence()
//{
//	static int f[N][N],g[N][N];
//	const int A=read(),n=read(),mod=1000000007;
//	for(int i=1; i<=A; ++i) f[1][i]=f[1][i-1]+i, Mod(f[1][i]);
//	for(int i=2; i<=n; ++i)
//	{
//		for(int j=1; j<=A; ++j)
//			f[i][j]=f[i][j-1]+1ll*f[i-1][j-1]*j%mod, Mod(f[i][j]);
//		printf("\ni:%d\n",i);
//		for(int j=1; j<=A; ++j) printf("%d ",g[i][j]=f[i][j]); puts("");
//		for(int k=1; k<=10; ++k)
//		{
//			printf("k:%d\n",k);
//			for(int j=1; j<=A-k; ++j) g[i][j]=g[i][j+1]-g[i][j], printf("%d ",g[i][j]);
//			puts("");
//		}
//	}
//	int fac=1;
//	for(int i=2; i<=n; ++i) fac=1ll*fac*i%mod;
//	printf("%lld\n",fac%mod*f[n][A]%mod);
//}
