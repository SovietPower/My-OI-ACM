/*
78ms	1100KB
$Description$
����$v_i,a_i$��ÿ�ο�����$a_i$��ɾ��һ���Ӷ�$[l,r]$���������㣺$|a_i-a_{i+1}|=1,\ 2a_i\geq a_{i+1}+a_{i-1}$��
ɾ���󽫸��Ӷ�ɾ���������$v_{r+l-1}$�����档���Բ�ɾ�ꡣ��������档
$n\leq 400$��
$Solution$
�Ϸ���������ֻ������������������ݼ���ǰ�벿�ֵ���Ȼ��һֱ�ݼ�����ȥ�˾Ͳ�������ȥ�ˣ�����Ȼ��Ҫ������$|a_{i+1}-a_i|=1$����
�����뵽����DP��$f[i][j]$��ʾ������$[i,j]$ȫ��ɾ����������棬����Ҫ$g[i][j]$��ʾ������$[i,j]$ɾ������������һ�Σ�$a_i\sim a_j$����������棬$h[i][j]$��ʾ������$[i,j]$ɾ�������½���һ�Σ�$a_i\sim a_j$����������档
��ô$g[i][j]$��Ԫ�ظ�������$a_j-a_i+1$��$h[i][j]$��Ԫ�ظ���Ϊ$a_i-a_j+1$���ϲ�$g[i][k],h[k][j]$���Ԫ�ظ�������$2a_k-a_i-a_j+2-1$������1��$a_k$����
��ô
$$f[i][j]=\max\{f[i][k]+f[k+1][j],\ g[i][k]+h[k][j]+v[2a_k-a_i-a_j+1]\}$$
��ʵ$g,h$��һ������Ϳ����ˣ���Ϊֻ��Ҫ�ж�һ��$a_i,a_j$�Ĵ�С��ϵ����֪�����������л����½������ˡ�
���Ĵ𰸾���$f$������Ӷκ͡�$n^2$��������ɡ�
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=405,INF=0x3f3f3f3f;

int A[N],val[N],f[N][N],g[N][N],dp[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) val[i]=read();
	for(int i=1; i<=n; ++i) A[i]=read();

	for(int i=1; i<=n; ++i)
	{
		f[i][i]=val[1], g[i][i]=0;
		for(int j=i+1; j<=n; ++j) f[i][j]=g[i][j]=-INF;
	}

	for(int len=1; len<n; ++len)
		for(int i=1; i+len<=n; ++i)
		{
			int j=i+len;
			for(int k=i; k<j; ++k)
			{
				f[i][j]=std::max(f[i][j],f[i][k]+f[k+1][j]);
				if((A[i]<A[j] && A[j]==A[k]+1)||(A[i]>A[j] && A[j]==A[k]-1))
					g[i][j]=std::max(g[i][j],g[i][k]+f[k+1][j-1]);
			}
			for(int k=i; k<=j; ++k)
				if(A[k]>=A[i] && A[k]>=A[j] && 2*A[k]-A[i]-A[j]+1<=n)//�ⶫ����Ȼ����<=0�� 
					f[i][j]=std::max(f[i][j],g[i][k]+g[k][j]+val[2*A[k]-A[i]-A[j]+1]);
		}
	for(int i=1; i<=n; ++i)
	{
		dp[i]=dp[i-1];
		for(int j=1; j<=i; ++j) dp[i]=std::max(dp[i],dp[j-1]+f[j][i]);
	}
	printf("%d\n",dp[n]);

	return 0;
}
