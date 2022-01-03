/*
912kb	592ms
$Description$
��$n$���ˣ�$m$�ſΣ�ÿ������ÿ�ſεĵ÷���һ��$[1,u_i ]$֮���������
��֪���Լ���ÿ�ſε�����$r_i$������$r_i-1$���˵÷ָ����㣬$n-r_i$���˵÷ֲ������㣨�����Լ�����
����ǡ����ѹk���˵ķ�������a��ѹb�ĺ���Ϊaÿ�ſεĵ÷ֶ�������b�ĵ÷֡�
$n,m\leq 100,u_i \leq 10^{9}$��
$Solution$
�󷽰���������DP...
$f[i][j]$��ʾ����$i$�ſΣ�����$j$�˻ᱻ��ѹ�ķ�������
��ô$$f[i][j]=\sum_{k=j}^{n-1}f[i-1][k]\times C_k^{k-j}\times C_{n-1-k}^{R_i-1-(k-j)}\times g[i]$$

�����ȴ�$k$����ѡ��$k-j$��$i$���ſα�B��÷ָߣ�Ȼ���ٴ�ʣ��$n-1-k$������ѡ$R_i-1-(k-j)$����B��÷ָߵġ�
�����������ƣ�$g[i]$��ʾ��$i$���ſη���÷�ʹ����$R_i-1$���˵÷ֱ�B��ߵķ�������ֱ��ö��һ��B��÷֣�$$g[i]=\sum_{j=1}^{U_i}j^{n-R_i}(U_i-j)^{R_i-1}$$

���ѿ�������һ������$U_i$��$n$�εĶ���ʽ���������ղ�ֵ��һ�¾ͺ��ˡ�������Ϊɶ��$n$�εĲ���$n-1$�εİ�QAQ��·��dalao���QAQ��

���Ӷ�$O(n^3\log n)$��
��Ϊ��$g$��ĳ���ֵ��ʱ��Ҫ$n$�ο����ݡ������˰������Ҳû������ô�Ż�������������и��õ�������[here](http://www.cnblogs.com/wangyurzee7/p/5479494.html) or [here](https://blog.csdn.net/aarongzk/article/details/51760818)����$n^3$�ġ�
�����˷������$\log$Ҳ����
���ݳ���Ҳ���ԣ�ƿ��Ҳ��������$g$����
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=105;

int ifac[N],y[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int FP(int x,int k)
{
	int t=1;
	for(; k; k>>=1,x=1ll*x*x%mod)
		if(k&1) t=1ll*t*x%mod;
	return t;
}
int Lagrange(int *y,const int n,const int x)
{
	static int pre[N],suf[N];
	pre[0]=x, suf[n+1]=1;
	for(int i=n; i; --i) suf[i]=1ll*suf[i+1]*(x+mod-i)%mod;
	for(int i=1; i<n; ++i) pre[i]=1ll*pre[i-1]*(x+mod-i)%mod;
	LL ans=0;
	for(int i=0,up,down; i<=n; ++i)
	{
		if(i) up=1ll*pre[i-1]*suf[i+1]%mod*y[i]%mod;
		else up=1ll*suf[i+1]*y[i]%mod;
		down=(n-i)&1?mod-1ll*ifac[i]*ifac[n-i]%mod:1ll*ifac[i]*ifac[n-i]%mod;
		ans+=1ll*up*down%mod;
	}
	return ans%mod;
}

int main()
{
	static int C[N][N],f[N][N],U[N],R[N];

	int n=read(),m=read(),K=read(),fac=1;
	for(int i=2; i<=n; ++i) fac=1ll*fac*i%mod;
	ifac[n]=FP(fac,mod-2);
	for(int i=n; i; --i) ifac[i-1]=1ll*ifac[i]*i%mod;
	C[0][0]=1;//!
	for(int i=1; i<=n; ++i)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; ++j) C[i][j]=C[i-1][j-1]+C[i-1][j], Mod(C[i][j]);
	}
	for(int i=1; i<=m; ++i) U[i]=read();
	for(int i=1; i<=m; ++i) R[i]=read();

	f[0][n-1]=1;
	for(int i=1; i<=m; ++i)
	{
		int Ri=R[i];
		for(int x=1; x<=n; ++x)
		{
			LL tmp=0;
			for(int j=1; j<=x; ++j) tmp+=1ll*FP(j,n-Ri)*FP(x-j,Ri-1)%mod;//����jҪö�ٵ�x����Ϊ0^0=1��...
			y[x]=tmp%mod;
		}
		int g=Lagrange(y,n,U[i]);
		for(int j=K; Ri+j<=n; ++j)
		{
			LL tmp=0;
			for(int k=j; k<n; ++k)
				if(k-j<Ri) tmp+=1ll*f[i-1][k]*C[k][j]%mod*C[n-1-k][Ri-1-k+j]%mod;
				else break;
			f[i][j]=tmp%mod*g%mod;
		}
	}
	printf("%d\n",f[m][K]);

	return 0;
}
