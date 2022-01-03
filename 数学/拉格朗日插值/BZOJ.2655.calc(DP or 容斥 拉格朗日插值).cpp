/*
2804kb	160ms
$Description$
�Ϸ������ж���Ϊ������Ϊ$n$��ÿ������$[1,k]$����������ͬ�����м�ֵ����Ϊ�������ĳ˻��������кϷ����еļ�ֵ�͡�ģ$p$��
$n\leq 500,\ k\leq 10^9,\ p\leq 10^9$��Ϊ������
$Solution$
���Ȱ����򻯳�����ѡ�ϸ�������������˸�$n!$��
Ȼ�������뵽��$f_{i,j}$��ʾ����$i$��������ǰѡ����$j$�ļ�ֵ�͡����Ӷ���$O(nA)$�ġ�~~Ȼ����������������������ûǰ;��~~
~~��������������Ҫ$O(A)$��һ��ͣ��о�����������~~

ֱ����$f_{i,j}$��ʾѡ��$i$������ѡ��������$\leq j$�ļ�ֵ�͡�ת��Ϊ��$f_{i,j}=f_{i,j-1}+f_{i-1,j-1}\times j$��
���ӶȻ���$O(nA)$�����Ĵ𰸾���$f_{n,A}$��
���Ժ���������DPҪע�⣩�����~~���ǿ����~~���Է��֣�$f_{i,j}$��һ������$j$��$2i$�εĶ���ʽ��
��$f_{i,j}$չ����ž���������$f_{i,j}=\sum\limits_{k=1}^{j-1}f_{i-1,k}\times(k+1)$����ͻ������ʽ����+1����$k+1$��ʵ���ǳ˵�$x+1$��������������������Զ���ʽ����Ҳ��+1��������$2i$�εġ�
�ǾͿ��Ա���$n^2$DP���$2n+1$��$f_{n,0,1...2n}$��ֵ��Ȼ���������ղ�ֵ�Ϳ��Եõ�$f_{n,A}$�ˡ�
���Ӷ�$O(n^2)$��

�ݳ⣺
��$f_i$��ʾ$n=i$ʱ�Ĵ𰸣�ת�Ƶ�ʱ��ö�٣�ǿ����$j$������$i$ѡ������ͬ���ݳ�һ�£���ô��
$$f_i=\sum\limits_{j=0}^{i-1}(-1)^jA_{i-1}^jf_{i-j-1}g(j+1)$$
����$g(j)=\sum_{i=1}^Ai^j$������ѡ$j$����ͬ���Ĺ��׺͡������ò�Ŭ����/�������ղ�ֵ$O(n^2)$Ԥ����
����Ϊɶ��$A_{i-1}^j$����$C_{i-1}^j$...����ô�����...�����˸�������ˡ�
������DP�ġ�
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
