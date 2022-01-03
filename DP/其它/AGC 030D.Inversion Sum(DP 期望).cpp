/*
310ms	35456KB
$Description$
������Ϊ$n$������$A_i$��$q$�β���$(x,y)$������ÿ�β���$(x,y)$������ѡ�񽻻�$A_x,A_y$��������Ҳ����ѡ�񲻽��в�����������$2^q$������У�����Ը���֮�͡�
$n,q\leq3000$��
$Solution$
��ȥֱ����ͣ�������$q$�β���������Ե�������������������$2^q$���Ǵ𰸡�
������$f[t][i][j]$��ʾ��$t$�β�����$A_i<A_j$�ĸ��ʡ�
$f[0][i][j]$�����ɳ�ʼ���еõ���Ȼ����Դ�$f[t-1][i][j]$ת�Ƶ�$f[t][i][j]$��������������$O(n^2q)$�ģ�
����ÿ�β���$(x,y)$��ֻ��Ӱ��$i$��$j$����$x$��$y$ʱ��$f[t][i][j]$�������Ķ�����䡣����ֻ��Ҫ�޸���$O(n)$��ֵ�Ϳ����ˡ�������$f[i][x]$��$a_i<a_x$�ĸ��ʣ�����$\frac12$����$a_i<a_y$�ĸ��ʣ���$f[i][x]=\frac{f[i][x]+f[i][y]}{2}$��$f[i][y]$ͬ��
���Ӷ�$O(n^2+qn)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define inv2 500000004ll
typedef long long LL;
const int N=3005;

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
	static int A[N],f[N][N];
	const int n=read(),q=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) f[i][j]=A[i]<A[j];
	for(int i=1; i<=q; ++i)
	{
		int x=read(),y=read();
		f[x][y]=f[y][x]=inv2*(f[x][y]+f[y][x])%mod;
		for(int j=1; j<=n; ++j)
			if(j!=x && j!=y)
				f[j][x]=f[j][y]=inv2*(f[j][x]+f[j][y])%mod,
				f[x][j]=f[y][j]=inv2*(f[x][j]+f[y][j])%mod;
	}
	LL ans=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<i; ++j) ans+=f[i][j];
	printf("%lld\n",ans%mod*FP(2,q)%mod);

	return 0;
}
