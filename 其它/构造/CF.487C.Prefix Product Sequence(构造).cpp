/*
46ms	600KB
$Description$
对于一个序列$a_i$，定义其前缀积序列为$a_1\ \mathbb{mod}\ n,\ (a_1a_2)\ \mathbb{mod}\ n,...,(a_1a_2...a_n)\ \mathbb{mod}\ n$。
给定$n$，求一个$n$的排列，使得该排列的前缀积序列是$[0,1,2,...,n-1]$的一个排列。无解输出$NO$。
$n\leq10^5$。
$Solution$
考虑无解的情况。因为$n!\equiv0\ (\mathbb{mod}\ n)$，所以$(n-1)\not\equiv0\ (\mathbb{mod}\ n)$。
$n$为质数显然可以满足。否则设$n=pq$。
若$p\neq q$，那么有$(n-1)!\equiv0\ (\mathbb{mod}\ n)$，GG了。
若$p=q$，当$n>4$时，$2p<n$，所以也有$(n-1)!\equiv0\ (\mathbb{mod}\ n)$，GG。
所以$n$为大于$4$的合数时无解。特判一下$n=4$。

首先$a_1$要填$1$，$a_n$要填$n$。
考虑能不能直接让前缀积序列变成$1,2,...,0$。那么$a_i=\frac{i}{i-1}\ \mathbb{mod}\ n,\ i>1$。
只需要判断是否有$\frac{a}{a-1}=\frac{b}{b-1},\ 1\lt a\neq b\lt n$。
稍微化一下，$\frac{a}{a-1}=1+\frac1a,\ \frac{b}{b-1}=1+\frac1b$，而我们知道每个数的逆元是唯一的，所以这么做就OK啦。
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=1e5+5;

int A[N],inv[N];

bool IsPrime(int x)
{
	int t=0;
	for(int i=2; x!=1; ++i)
		while(!(x%i))
		{
			x/=i;
			if(++t>1) return 0;
		}
	return 1;
}

int main()
{
	int n; scanf("%d",&n);
	if(n==4) return printf("YES\n1\n3\n2\n4\n"),0;
	if(!IsPrime(n)) return puts("NO"),0;
	A[1]=1, A[n]=n, inv[1]=1;
	for(int i=2; i<n; ++i) inv[i]=1ll*(n-n/i)*inv[n%i]%n, A[i]=1ll*i*inv[i-1]%n;
	puts("YES");
	for(int i=1; i<=n; ++i) printf("%d\n",A[i]);

	return 0;
}
