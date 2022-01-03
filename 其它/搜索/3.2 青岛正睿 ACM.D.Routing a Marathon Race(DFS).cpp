/*
1ms 2704kb
$Description$
����һ��$n$����$m$���ߵ�����ͼ��ÿ������һ��Ȩֵ����һ����$1$��$n$��·����ʹ�ô�����С�������С���ۡ�
һ��·���Ĵ��۶���Ϊ��·�������е��Լ�����Щ�����ڵ����е��Ȩֵ�͡�
$n\leq40,\ m\leq\frac{n(n-1)}{2}$��
$Solution$
���׷��֣����ѡ���$u$�ߵ�$v$����ôһ�������ٻص�$u$���������ڽڵ㣨����ֱ���߹�ȥ����
�����ӵ�$u$���ѵĻ���ÿ���ƶ�����ɾ��$dgr_u$���㡣
��ô���Ӷ��ǣ�$T(n)=c\times T(n-c)$������������$c=3$�����Ӷ�Լ��$3^{\frac n3}$��
ע�������$N\times N$������$2$��������mdzz��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=45,M=N*N;

int n,Ans,Enum,H[N],nxt[M],to[M],A[N],ban[N];

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
void DFS(int x,int cost)
{
	if(x==n)
	{
		for(int i=H[x]; i; i=nxt[i]) !ban[to[i]]&&(cost+=A[to[i]]);//!
		Ans=std::min(Ans,cost);
		return;
	}
	for(int i=H[x]; i; i=nxt[i]) !ban[to[i]]&&(cost+=A[to[i]]), ++ban[to[i]];
	for(int i=H[x]; i; i=nxt[i]) if(ban[to[i]]==1) DFS(to[i],cost);
	for(int i=H[x]; i; i=nxt[i]) --ban[to[i]];
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=m; ++i) AE(read(),read());
	::n=n, Ans=2e9, ban[1]=1, DFS(1,A[1]), printf("%d\n",Ans);

	return 0;
}
