/*
824kb	16ms
$Description$
����$n$�����ڷ���$x\oplus 3x=2x$���������
1. �ж���$x\leq n$���������⡣
2. �ж���$x\leq 2^n$���������⣬ģ1e9+7��
$n\leq 10^{18}, 1000$�����ݡ�
$Solution$
`x^3x=2x -> x^2x=3x`
��Ϊ`a^b + ((a&b)<<1)=a+b`��`x^2x = x+2x`������x��2x�Ķ����Ʊ�ʾ�в��������ڵ�1��
�����ߣ���Ϊ`x+2x=3x`������`x^2x`û�е����κε�1������x��2xû�����ڵ�1��
��ô��һ����λDP���ڶ����Ͻ�Ϊ$2^n$����λDP�����ˡ�
$f[i]$��ʾ����$i$λ�ķ�������ÿλҪô��$0$Ҫô��$1$������$f[i]=f[i-1]+f[i-2]$������쳲��������У���쳲�������ʾ��Ҳ�ܿ��������DP�����ƣ���
����$f[n+1]$��$2^n$��$n+1$λ����==��

�����һ���������ƶ����Ʋ�ֵķ���O(64)����https://blog.csdn.net/jr_mz/article/details/50351557 �����뿴�ˡ�
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
