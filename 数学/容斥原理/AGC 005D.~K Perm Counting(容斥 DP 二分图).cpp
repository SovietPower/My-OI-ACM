/*
20ms	256KB
$Description$
����$n,k$���� �����������$i$��$|a_i-i|\neq k$�����еĸ�����
$2\leq n\leq 2000,\quad 1\leq k\leq n-1$��
$Solution$
�ݳ⡣��$Ans=\sum_{i=0}^n(-1)^ig(i)(n-i)!$������$g(i)$Ϊ������$i$��λ������$|a_i-i|=k$����������
������μ���$g(x)$��ÿ��$i$��$i+k$��$i-k$���ߣ����Եõ�һ�Ŷ���ͼ��$g(x)$���������Ŷ���ͼ��ѡ$x$��ƥ��ķ�������
���ǻ����Է��֣�ͼ�е�ƥ���γ���$2k$�������ཻ��������ÿ�����ϵ���ģ$k$��ͬ��Ҳ����ģ$k$��ͬ�����ǻ���Ӱ��ģ�����ö��ģ���Ϳ��Եõ��������ˣ���
���ֻ��һ����$l$��������ô���Ƕ�$l-1$����DP��$f[i][j][0/1]$��ʾ��ǰ��$i$���㣬�Ѿ�ѡ��$j$��ƥ�䣬�����ѡ��ѡ�������ѡҪ����һ����ûѡ����
����$2k$����Ҳ��һ���ģ�ֻҪ����֮���һ���㣬��ǿ��������ѡ��$f[i][j][1]=0$�����Ϳ��԰���Щ������һ��DP����
�������Ӷ�$O(n^2)$��Ȼ���ö�dalao��NTT$n\log n$������orz��
*/
#include <cstdio>
#include <algorithm>
#define mod 924844033
typedef long long LL;
const int N=4005;//2n

int ban[N],f[2][N][2],fac[N];

int main()
{
	int n,K,cnt=0; scanf("%d%d",&n,&K);
	for(int i=1; i<=K; ++i)
	{
		ban[++cnt]=1;
		for(int j=i+K; j<=n; j+=K) ban[++cnt]=0;
		ban[++cnt]=1;//������������ 
		for(int j=i+K; j<=n; j+=K) ban[++cnt]=0;
	}
	int p=0; f[p][0][0]=1;
	for(int i=0; i<cnt; ++i,p^=1)
		for(int j=0; j<=i; ++j)
		{
			f[p^1][j][0]=(f[p][j][0]+f[p][j][1])%mod;
			if(!ban[i+1]) f[p^1][j+1][1]=f[p][j][0];
			f[p][j][0]=f[p][j][1]=0;
		}
	fac[0]=1;
	for(int i=1; i<=n; ++i) fac[i]=1ll*fac[i-1]*i%mod;
	LL ans=0;
	for(int i=0; i<=n; ++i)
		ans+=i&1?mod-1ll*fac[n-i]*(f[p][i][0]+f[p][i][1])%mod:1ll*fac[n-i]*(f[p][i][0]+f[p][i][1])%mod;
	printf("%lld\n",ans%mod);

	return 0;
}
