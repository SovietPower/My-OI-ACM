/*
33844kb	4868ms
$Description$
给定一棵$n$个点的树和$K$，边权为$1$。对于每个点$x$，求$S(x)=\sum_{i=1}^ndis(x,i)^K$。
$n\leq50000,\ k\leq150$。

$Solution$
和其它求$x^k$的题一样，依旧用第二类斯特林数展开。（[二项式定理](https://35178.blog.luogu.org/solution-p4827)依旧可以得到部分分，依旧不想看=-=）
$$\begin{aligned}S(x)&=\sum_{i=1}^ndis(x,i)^K\\&=\sum_{i=1}^n\sum_{k=0}^{dis(x,i)}S(K,k)\cdot k!\cdot \binom{dis(x,i)}{k}\\&=\sum_{i=1}^n\sum_{k=0}^KS(K,k)\cdot k!\cdot \binom{dis(x,i)}{k}\\&=\sum_{k=0}^KS(K,k)\cdot k!\cdot\sum_{i=1}^n\binom{dis(x,i)}{k}\end{aligned}$$

考虑这个$\sum_{i=1}^n\binom{dis(x,i)}{k}$怎么算。用阶乘公式拆还是一样没法算，尝试用这个公式拆：$\binom nm=\binom{n-1}m\times\binom{n-1}{m-1}$：
$$\sum_{i=1}^n\binom{dis(x,i)}{k}=\sum_{i=1}^n\binom{dis(x,i)-1}{k}+\sum_{i=1}^n\binom{dis(x,i)-1}{k-1}$$

记$f[x][k]=\sum_{i=1}^n\binom{dis(x,i)}{k}$，那么可以由$x$的相邻点$v$的$f[v][k]+f[v][k-1]$转移来（$x$和$v$与其它点的$dis$正好差$1$）。
具体就是两遍树形DP，第一次自底向上求出子树内的点到$x$的$dis$的贡献，即$f[x][i]=\sum_{v\in son[x]}f[v][i]+f[v][i-1]$；第二次从上往下更新子树外的点到$v=son[x]$的$dis$的贡献，记为$g[v][i]=g[x][i]+g[x][i-1]+(f[x][i]-f[v][i]-f[v][i-1])+(f[x][i-1]-f[v][i-1]-f[v][i-2])$。
然后统计一下就OK了。复杂度$O(nk+k^2)$。

明明取模优化的不少啊，怎么就这么慢呢=-=
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
	f[x][0]=1;//这个初始化...C(dis(x,x),0)=1？有点小懵逼=-=
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
