/*
27376kb	9684ms
��Ȼ����������ƣ���ôӦ��ѡ���ľ����ܵĴ��$k-1$�š�
Ȼ������˵���������ǳ��ܷ�������ģ�����������ĺ͡�Ȼ��$w_i$ͳһ��$A_i$��ʾ�ˡ�

$Sol1$
���Կ���ö�����ճ鵽�˼��������ơ���ô����Ҫ�㣺$F(n,m)$��ʾ�鵽$n$�Ź����ƣ��������$m$�ŵ������˺���$G(n,m)$��ʾ�鵽$n$�������ƣ��������$m$�ŵ�����������
������ô��$F(n,m)$������ö�ٹ�����С��������ʲô��Ҳ���ǰѹ����ƴӴ�С����$f[i][j]$��ʾ��ǰ$i$����ѡ$j$�ŵ������˺������е�$i$��һ��ȡ��ת�ƾ���ö��һ�´�С�ģ�$f[i][j]=C_{i-1}^{j-1}A_i+\sum\limits_{k=j-1}^{i-1}f[k][j-1]$��
$G(n,m)$ͬ����$g[i][j]$��ʾ��ǰ$i$�����������ѡ$j$�ŵ��������������е�$i$��һ��ȡ��$g[i][j]=A_i\sum\limits_{k=j-1}^{i-1}g[k][j-1]$��
����DP������ǰ׺���Ż������Ը��Ӷ���$O(n^2)$�ġ�

��ô$F,G$��ת��ͬ��ö��ѡ��������С�����ţ�$F(n,m)=\sum\limits_{i=m}^{N}C_{N-i}^{n-m}f[i][m]$��$G(n,m)=\sum\limits_{i=m}^{N}C_{N-i}^{n-m}g[i][m]$�����ڵ���$F/G(n,m)$�ļ�����$O(n)$�ġ�
Ȼ��$Ans=\sum\limits_{i=1}^{k-1}G(i,i)F(m-i,k-i)+\sum\limits_{i=k}^NG(i,k-1)F(m-i,1)$������ֻ���õ�$O(n)$��$F/G$��ֵ������һ�¼��ɣ��ܸ��Ӷ���$O(n^2)$�ġ�

Ϊ�˷���Ӧ�ð�$f/g$��һ��ά������=-=��

$Sol2$
��$f[i][j]$��ʾ������ǰ$i$���ƣ��鵽��$j$�Ź����Ƶ������˺����϶���ѡ�����������Ŵ�������ƴ�С��������Ȼ�����$j$ȷ��������ѡ��ѡ����$$f[i][j]=f[i-1][j]+C_{i-1}^{j-1}A_i+\begin{cases}0,&m-j\geq k-1\\f[i-1][j-1],&m-j<k-1\end{cases}$$

����$i$�Ĺ��ף�$m-j\geq k-1$ʱ��ֻ��ȡһ�Ź����ƣ���ȡ$i$���ܱ�֤��������������ţ�����ȡ��$i$֮�󻹿�����ȡ$j-1$�ŵ������Ȼ����ͳ������ǰ��ֻ����$i-1$����ʱ��$f[i-1][j]$��ע�����=-=����
$g[i][j]$��ʾ������ǰ$i$���ƣ��鵽��$j$�������Ƶ�������������Ϊ��ѡ����$\min(k-1,\ j)$�Ŵ�������԰������ƴӴ�С������$$g[i][j]=g[i-1][j]+\begin{cases}g[i-1][j-1]*A_i,&j<k\\g[i-1][j-1],&j\geq k\end{cases}$$

����$j<k$ʱ��$A_i$������鵽$A_i$Ҳ���á�
��ô�𰸾���$\sum_{i=0}^mf[n][i]g[n][m-i]$����
���Ӷ�Ҳ��$O(n^2)$����������Ҫ��С��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <functional>
#define mod 998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define gc() getchar()
typedef long long LL;
const int N=1505;

int A[N],B[N],f[N][N],g[N][N],C[N][N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int F(int n,int m,int N)
{
	LL ans=0; int *f=::f[m];
	for(int i=m; i<=N; ++i) ans+=1ll*C[N-i][n-m]*f[i]%mod;
	return ans%mod;
}
int G(int n,int m,int N)
{
	LL ans=0; int *g=::g[m];
	for(int i=m; i<=N; ++i) ans+=1ll*C[N-i][n-m]*g[i]%mod;
	return ans%mod;
}

int main()
{
	C[0][0]=1;
	for(int Ts=read(),mx=0; Ts--; )
	{
		int n=read(),m=read(),K=read();
		if(mx<n)
		{
			for(int i=mx+1; i<=n; ++i)
			{
				C[i][i]=C[i][0]=1;
				for(int j=1; j<i; ++j) C[i][j]=C[i-1][j-1]+C[i-1][j], Mod(C[i][j]);
			}
			mx=n;
		}
		for(int i=1; i<=n; ++i) A[i]=read();
		for(int i=1; i<=n; ++i) B[i]=read();
		std::sort(A+1,A+1+n,std::greater<int>()), std::sort(B+1,B+1+n,std::greater<int>());

		g[0][0]=1;//!! K=1ʱ���õ���=-= 
		for(int i=1; i<=n; ++i) f[1][i]=B[i], g[1][i]=A[i];//or not
		for(int i=2,lim=std::min(n,m); i<=lim; ++i)
		{
			int sf=0,sg=0;
			for(int j=i; j<=n; ++j)
				Add(sf,f[i-1][j-1]), f[i][j]=(1ll*C[j-1][i-1]*B[j]+sf)%mod,
				Add(sg,g[i-1][j-1]), g[i][j]=1ll*A[j]*sg%mod;
		}
		LL ans=0;
		for(int i=std::max(0,m-n); i<=n&&i<=m; ++i)//m-i<=n ö�ٵ��������� ������0��=v= 
			if(i<K) ans+=1ll*G(i,i,n)*F(m-i,K-i,n)%mod;
			else ans+=1ll*G(i,K-1,n)*F(m-i,1,n)%mod;
		printf("%lld\n",ans%mod);
	}

	return 0;
}
