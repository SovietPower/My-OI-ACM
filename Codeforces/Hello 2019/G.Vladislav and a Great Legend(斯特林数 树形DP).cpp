/*
467ms	90200KB
$Description$
����һ��$n$���������������$k$������$f(s)$��ʾʹ�㼯$s$�еĵ���ͨ��������ٱ�������$\sum_{s\neq\varnothing}f(s)^k$��
$n\leq10^5,\ k\leq200$��

$Solution$
������·����$f(s)^k$�õڶ���˹��������$m^n=\sum_{k=0}^mC_m^kS(n,k)k!$��չ����
$$\begin{aligned}Ans&=\sum_{s\neq\varnothing}\sum_{i=0}^kC_{f(s)}^iS(k,i)i!\\&=\sum_{i=0}^kS(k,i)i!\sum_{s\neq\varnothing}C_{f(s)}^i\end{aligned}$$

�����$\sum_{s\neq\varnothing}C_{f(s)}^i$ʵ�ʾ�����ѡ$i$���ߣ���Ӧ���ٸ��㼯��������DPȥ�㡣
��$f[i][j]$��ʾѡ�е����е��$LCA$Ϊ$i$ʱ������Щ��������ѡ��$j$���߶�Ӧ�ĵ㼯�ж��ٸ�������������$i\to fa[i]$�����ߣ���Ϊ�������ʱ����������ߺ��񲻺���...��ʾ���ᣩ��
ÿ�����ʼ��$f[x][0]=2$��������Ҳ���Բ��ڵ㼯�У����ϲ�������ʱ��������α�����$f'[x][i+j]=\sum_{v=son[x]}f[x][i]*f[v][j]$��
�ϲ��������Ĺ��׺�������$x\to fa[x]$�����ߵĹ��ף����ܳ����ڱ߼��У�����$f[x][i]$+=$f[x][i-1]$��
��ʱ���в��Ϸ��������$x$������û��ѡ�㣬��ѡ��$x\to fa[x]$�����ߡ�
��ȥ�ϲ���������ʱ��$f$�Ĺ��׾����ˣ���$Ans_i$-=$f[x][i-1]$��
����Ҫע��$f[x][0]$�ǰ����ռ���һ������ģ���ѡ�κε㣩�������ֲ���ֱ��ȥ����ֱ��--$f[x][0]$������ϵ�ʱ������õ���
��������$f[x][0]$��������ֵʱע����������ȥ����$Ans_1$�ټ������$1$����$x\to fa[x]$�ı߸��º��$f[x][1]$Ҫ�������$1$��

�����԰�$i!$�˽�ȥ���ͳ���[ά���½���](https://blog.csdn.net/Dream_Lolita/article/details/86428795)�������뿴�ˡ���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 1000000007
#define gc() getchar()
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
typedef long long LL;
const int N=1e5+5;

int K,Enum,H[N],nxt[N<<1],to[N<<1],f[N][203],Ans[N];

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
void DFS(int x,int fa)
{
	static int sz[N],g[N];
	f[x][0]=2, sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x);
			for(int a=0,l=std::min(sz[x]-1,K); a<=l; ++a)
				for(int b=0; b<=sz[v]&&a+b<=K; ++b)//ע�����ﲻ�ǵ�sz[v]-1������v->fa[v]�����ߣ�
					Add(g[a+b],1ll*f[x][a]*f[v][b]%mod);
			sz[x]+=sz[v];
			for(int j=0,l=std::min(sz[x]-1,K); j<=l; ++j) f[x][j]=g[j], g[j]=0;
		}
	if(x!=1)
	{
		for(int i=1,l=std::min(sz[x],K); i<=l; ++i) Add(Ans[i],mod-f[x][i-1]);//ע������Ҳ����sz[x]-1��������д���ȡmin������һЩ��
		++Ans[1];
	}
	else for(int i=0,l=std::min(sz[1]-1,K); i<=K; ++i) Add(Ans[i],f[1][i]);
	for(int i=std::min(sz[x],K); i; --i) Add(f[x][i],f[x][i-1]);
	Add(f[x][1],mod-1);
}

int main()
{
	static int S[203][203];
	const int n=read(),K=read(); ::K=K;
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS(1,1);
	S[0][0]=1;
	for(int i=1; i<=K; ++i)
		for(int j=1; j<=i; ++j) S[i][j]=S[i-1][j-1]+1ll*S[i-1][j]*j%mod, Mod(S[i][j]);
	LL ans=0;
	for(int i=0,fac=1; i<=K; ++i) ans+=1ll*S[K][i]*fac%mod*Ans[i]%mod, fac=1ll*fac*(i+1)%mod;
	printf("%I64d\n",ans%mod);

	return 0;
}
