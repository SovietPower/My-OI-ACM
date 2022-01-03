/*
62ms	101900KB
$Description$
����$n,r,s$����ʾ��$n$���ˣ���ÿ���˵ĵ÷��ǷǸ�����$a_i$����֪��һ���˵ĵ÷�$a_1\geq r$�������˵ĵ÷�֮��$\sum a_i=s$���÷���ߵ�һ���˻�ʤ�����ж���˵÷���ߣ������һ���˻�ʤ��
�������п�������£���һ���˻�ʤ�ĸ��ʡ�
$n\leq100,\ 0\leq r\leq s\leq5000$��

$Solution$
��Χ���Ǻܴ��ȿ���ö�ٵ�һ���˵ĵ÷�$x$��
Ȼ��ö����$i$���˵ĵ÷ֺ͵�һ������ͬ����������ʱ�򲻷����ϵ�һ���ˡ�
����������֪��$i$���˵÷�Ϊ$x$��Ҫ��ʣ��$n-i$���˵ķ�����$\sum a_j\leq s-i\times x$����$a_j<x$��
���û���Ͻ����ƣ����Ǿ����������⣨���̷Ǹ�������������
�����Ͻ�����ƣ������ݳ⣬ö���ж����˷����ﵽ$x$����$$\sum_{j=0}^{n-i}(-1)^jC_{n-i}^jf(n-i,s-(i+j)\times x)$$

����$f(n,m)$��$\sum_{i=1}^na_i=m$�ķǸ�������������$C_{n+m-1}^{m}$��
�������𰸾���$$\sum_{x=r}^s\sum_{i=1}^n\frac{C_{n-1}^{i-1}}{i}\sum_{j=0}^{n-i}(-1)^jC_{n-i}^jC_{n-i+s-(i+j)x-1}^{n-i-1}$$

����ٳ����ܷ�����$f(n,s-r)$��
���Ӷ�$O(n^2s)$��
*/
#include <cstdio>
#include <algorithm>
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=5107;

int inv[105],C[N][N];

inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
inline void Init(int n,int s)
{
	C[0][0]=1;
	for(int i=1; i<=s; ++i)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; ++j) C[i][j]=C[i-1][j-1]+C[i-1][j], Mod(C[i][j]);
	}
	inv[1]=1;
	for(int i=2; i<=n; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}

int main()
{
	int n,s,r; scanf("%d%d%d",&n,&s,&r);
	Init(n,n+s);
	LL ans=0;
	for(int x=r; x<=s; ++x)
		for(int i=1; i<=n; ++i)
		{
			if(i==n)
			{
				ans+=(x*n==s)*inv[n];
				continue;
			}
			if(i*x+(n-i)*(x-1)<s||i*x>s) continue;//���еļ�֦�������һ����0.
			LL tmp=0;
			for(int j=0; j<=n-i&&(i+j)*x<=s; ++j)
			{
				#define v 1ll*C[n-i][j]*C[n-i-1+s-(i+j)*x][n-i-1]%mod
				tmp+=j&1?mod-v:v;
			}
			ans+=tmp%mod*C[n-1][i-1]%mod*inv[i]%mod;
		}
	printf("%I64d\n",ans%mod*FP(C[n+s-r-1][n-1],mod-2)%mod);

	return 0;
}
