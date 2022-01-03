/*
101ms	97920KB
$Description$
����һ��$n$�������������$n$����������ԣ�����ÿһ�Ե�����·��Ⱦɫ�����ж�������Է���ʹ�����б߶����ٱ�Ⱦɫһ�Ρ�
$n\leq5000$��
$Solution$
�����ݳ⡣��߼�$E$���Ӽ�$S\in E$��$f(S)$��ʾʹ��$S$�����б߶�����Ⱦɫ����Է���������������⣩����$Ans=\sum_{S\in E}(-1)^{|S|}f(S)$��
���ȷ���߼�$S$�����ǿ�����$f(S)$����$S$�����ֳ��˴�С�ֱ�Ϊ$a_1,a_2,...,a_{|S|+1}$����ͨ�飬��ÿһ��ͨ���ڵĵ����������ԣ�$f(S)=\prod_{i=1}^{|S|+1}g(a_i)$��
$g(n)$��$n$��������������Եķ�������$g(n)=[2\mid n](n-1)\times(n-3)\times...\times3\times1=[2\mid n](n-1)!!$��˫�׳ˣ���
����DP������$f(S)$��$f[i][j]$��ʾ��ǰΪ$i$����������ͨ���СΪ$j$�ķ�������ת�ƾ������ϱ�����
�����$f[i][0]=\sum_{j=1}^{sz[i]}-1\times f[i][j]\times g(j)$��$-1$���߼�$S$����һ���ߣ���һ���ݳ�ϵ����
���Ӷ�$O(n^2)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=5005;

int Enum,H[N],nxt[N<<1],to[N<<1],f[N][N],sz[N],g[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int fa)
{
	static int tmp[N];

	sz[x]=1;
	int *fx=f[x]; fx[1]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x);
			for(int j=0,sv=sz[v]; j<=sz[x]; ++j)
				for(int k=0; k<=sv; ++k)
					tmp[j+k]+=1ll*fx[j]*f[v][k]%mod, Mod(tmp[j+k]);
			for(int j=0,l=sz[x]+sz[v]; j<=l; ++j)
				fx[j]=tmp[j], tmp[j]=0;
			sz[x]+=sz[v];
		}
	LL t=0;
	for(int i=1; i<=sz[x]; ++i) t+=mod-1ll*fx[i]*g[i]%mod;
	fx[0]=t%mod;
}

int main()
{
	int n=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	g[0]=1;
	for(int i=2; i<=n; i+=2) g[i]=1ll*g[i-2]*(i-1)%mod;
	DFS(1,1), printf("%d\n",mod-f[1][0]);

	return 0;
}
