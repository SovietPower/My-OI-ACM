/*
33844kb	4868ms
$Description$
����һ��$n$���������$K$����ȨΪ$1$������ÿ����$x$����$S(x)=\sum_{i=1}^ndis(x,i)^K$��
$n\leq50000,\ k\leq150$��

$Solution$
��������$x^k$����һ���������õڶ���˹������չ������[����ʽ����](https://35178.blog.luogu.org/solution-p4827)���ɿ��Եõ����ַ֣����ɲ��뿴=-=��
$$\begin{aligned}S(x)&=\sum_{i=1}^ndis(x,i)^K\\&=\sum_{i=1}^n\sum_{k=0}^{dis(x,i)}S(K,k)\cdot k!\cdot \binom{dis(x,i)}{k}\\&=\sum_{i=1}^n\sum_{k=0}^KS(K,k)\cdot k!\cdot \binom{dis(x,i)}{k}\\&=\sum_{k=0}^KS(K,k)\cdot k!\cdot\sum_{i=1}^n\binom{dis(x,i)}{k}\end{aligned}$$

�������$\sum_{i=1}^n\binom{dis(x,i)}{k}$��ô�㡣�ý׳˹�ʽ����һ��û���㣬�����������ʽ��$\binom nm=\binom{n-1}m\times\binom{n-1}{m-1}$��
$$\sum_{i=1}^n\binom{dis(x,i)}{k}=\sum_{i=1}^n\binom{dis(x,i)-1}{k}+\sum_{i=1}^n\binom{dis(x,i)-1}{k-1}$$

��$f[x][k]=\sum_{i=1}^n\binom{dis(x,i)}{k}$����ô������$x$�����ڵ�$v$��$f[v][k]+f[v][k-1]$ת������$x$��$v$���������$dis$���ò�$1$����
���������������DP����һ���Ե�������������ڵĵ㵽$x$��$dis$�Ĺ��ף���$f[x][i]=\sum_{v\in son[x]}f[v][i]+f[v][i-1]$���ڶ��δ������¸���������ĵ㵽$v=son[x]$��$dis$�Ĺ��ף���Ϊ$g[v][i]=g[x][i]+g[x][i-1]+(f[x][i]-f[v][i]-f[v][i-1])+(f[x][i-1]-f[v][i-1]-f[v][i-2])$��
Ȼ��ͳ��һ�¾�OK�ˡ����Ӷ�$O(nk+k^2)$��

����ȡģ�Ż��Ĳ��ٰ�����ô����ô����=-=
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 10007
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=50003,M=153;

int K,Enum,H[N],nxt[N<<1],to[N<<1],f[N][M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x,int fa)
{
	f[x][0]=1;//�����ʼ��...C(dis(x,x),0)=1���е�С�±�=-=
	int K=::K;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS1(v,x), f[x][0]+=f[v][0];
			for(int j=1; j<=K; ++j) f[x][j]+=f[v][j]+f[v][j-1];
		}
	for(int i=0; i<=K; ++i) f[x][i]%=mod;
}
void DFS2(int x,int fa)
{
	static int g[N];
	int K=::K;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			g[0]=f[x][0]+mod-f[v][0];
			for(int j=1; j<=K; ++j) g[j]=f[x][j]+mod-f[v][j]+mod-f[v][j-1];//g[j] = g[x][j]+f[x][j]-f[v][j]-f[v][j-1]
			f[v][0]=(f[v][0]+g[0])%mod;
			for(int j=1; j<=K; ++j) f[v][j]=(f[v][j]+g[j]+g[j-1])%mod;
			DFS2(v,x);
		}
}

int main()
{
	static int S[M][M];
	const int n=read(),K=read(); ::K=K;
//	for(int i=1; i<n; ++i) AE(read(),read());
	for(int L=read(),now=read(),A=read(),B=read(),Q=read(),i=1; i<n; ++i)
		now=(now*A+B)%Q, AE(i-now%(i<L?i:L),i+1);

	DFS1(1,1), DFS2(1,1), S[0][0]=1;
	for(int i=1; i<=K; ++i)
		for(int j=1; j<=i; ++j) S[i][j]=(S[i-1][j-1]+S[i-1][j]*j)%mod;
	for(int x=1; x<=n; ++x)
	{
		LL ans=0;
		for(int i=0,fac=1; i<=K; ++i) ans+=1ll*S[K][i]*fac*f[x][i]%mod, fac=fac*(i+1)%mod;
		printf("%d\n",(int)(ans%mod));
	}

	return 0;
}
