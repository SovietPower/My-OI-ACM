/*
53ms	4992KB
$Description$
给定$n$，要求构造一个$n\times n$的矩阵，矩阵内的元素两两不同，且任意相邻的两个元素$x,y$，满足$\max(x,y)\ \mathbb{mod}\ \min(x,y)$等于一个非零常数。
$n\leq500,\ 1\leq 矩阵中的元素\leq10^{15}$。

$Solution$
考虑没有元素互不相同的限制，那么就直接填$x,x+1,x,x+1...$，即对矩阵黑白染色，黑格子填$x$，白格子填$x+1$。
如果有限制，依旧可以先黑白染色，然后令白格子比周围四个黑格子都大。就令$\max(x,y)\ \mathbb{mod}\ \min(x,y)=1$好了，这样白格子的权值等于周围四个黑格子的$LCM+1$。
但是这样直接随便给黑格子赋权值，元素是会超过$10^{15}$的。
因为是求$LCM$，不妨令黑格子根据对角线设成两个数的乘积。即，对于左上-右下和左下-右上这$2n$条对角线（只考虑黑格子），分别给它一个数。那一个黑格子的它所在的两条对角线上的数的乘积。
要保证任意元素互不相同，所以考虑把这$2n$个数设成$2n$个质数。
那么对于最大的白格子，权值是$第499个质数\times第500个质数\times第999个质数\times第1000个质数<8\times10^{14}$。那么就OK啦。

$n=2$时不对，要特判。
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=505,M=8100;

int P[1005];
LL A[N][N];

void Init()
{
	static bool notP[M];
	for(int cnt=0,i=2; cnt<1000; ++i)
	{
		if(!notP[i]) P[++cnt]=i;
		for(int j=1,v; j<=cnt&&(v=i*P[j])<M; ++j)
		{
			notP[v]=1;
			if(!(i%P[j])) break;
		}
	}
}
inline LL LCM(LL x,LL y)//longlong
{
	return x/std::__gcd(x,y)*y;
}

int main()
{
	Init();
	int n; scanf("%d",&n);
	if(n==2) return printf("4 7\n23 10\n"),0;
	for(int i=0; i<=n+1; ++i) A[0][i]=1, A[n+1][i]=1, A[i][n+1]=A[i][0]=1;
	for(int i=1; i<=n; ++i)
		for(int j=i&1?1:2; j<=n; j+=2)
			/*if(!(i+j&1))*/ A[i][j]=P[i+j>>1]*P[(i-j+n+1)/2+n];
	for(int i=1; i<=n; ++i)
		for(int j=i&1?2:1; j<=n; j+=2)
			/*if(i+j&1)*/ A[i][j]=LCM(LCM(A[i-1][j],A[i][j-1]),LCM(A[i+1][j],A[i][j+1]))+1;
	for(int i=1; i<=n; ++i,putchar('\n'))
		for(int j=1; j<=n; ++j) printf("%lld ",A[i][j]);

	return 0;
}
