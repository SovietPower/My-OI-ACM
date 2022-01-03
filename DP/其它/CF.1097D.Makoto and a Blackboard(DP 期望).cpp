/*
217ms	0KB
$Description$
����$n,k$��ÿ��$n$��ȸ��ʵر���Լ���һ��Լ��������$1,n$������仯$k$�κ�$n$�����Ƕ��١�
$n\leq10^{15},\ k\leq10^4$��
$Solution$
��$n$�������ֽ⣬$n=p_1^{a_1}p_2^{a_2}...p_k^{a_k}$��ÿ�α仯��ÿ�������ӵĴ���$a_i$��������$0\sim a_i$�е�һ��������ÿ��$a_i$�ı仯�Ƕ����ġ�
���Կ��Զ�ÿ�������ӷֱ��������������������
��$f[i][j]$��ʾ$i$�α仯��$a$���$j$�ĸ��ʣ�$f[0][a]=1$��
ת�ƾ���$f[i][j]=\sum_{k=j}^a\frac{f[i-1][k]}{k+1}$��
����������������һ�飬�������ͺ��ˡ�
�����Ӹ�������������$\log$����ģ���ʵ������Ҳ��$\log$���𣿣������Ը��Ӷ���$O(k\log^2n)$����ʵҲ����$O(k\log n)$�������ټ��Ϸֽ�������$O(\sqrt{n})$��

�Ҿ�Ȼ����Ԫ��ɽ׳���Ԫ��Ȼ�����ʮ����= =��Ҳ�����ˡ�
*/
#include <cstdio>
#include <algorithm>
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=52;

int inv[N];

int Solve(int x,int K,int a)
{
	static int sum[N];
	for(int i=0; i<a;++i) sum[i]=0;
	sum[a]=1, sum[a+1]=0;
	for(int i=1; i<=K; ++i)
		for(int j=a; ~j; --j)
			sum[j]=sum[j+1]+1ll*sum[j]*inv[j+1]%mod, Mod(sum[j]);
	LL ans=0;
	for(int i=0,t=1; i<=a; ++i) ans+=1ll*t*sum[i]%mod, t=1ll*t*x%mod;
	return ans%mod;
}

int main()
{
	inv[1]=1;
	for(int i=2; i<N; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;

	LL n,ans=1; int K; scanf("%I64d%d",&n,&K);
	for(int i=2; 1ll*i*i<=n; ++i)//���ö��ò�ƿ����Ż���ÿ��+=6����
		if(!(n%i))
		{
			int a=1; n/=i;
			while(!(n%i)) ++a, n/=i;
			ans=ans*Solve(i,K,a)%mod;
		}
	if(n!=1) ans=ans*Solve(n%mod,K,1)%mod;//n���ܴܺ� ����ȡģ��
	printf("%I64d\n",ans);

	return 0;
}
