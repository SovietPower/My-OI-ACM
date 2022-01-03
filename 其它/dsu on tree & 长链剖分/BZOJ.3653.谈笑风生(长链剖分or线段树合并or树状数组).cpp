/*
36944kb	3808ms
$Description$
����һ������ÿ��ѯ�ʸ���$p,k$��������$p,a$����$b$�����ȣ���$p,a$���벻����$k$����Ԫ��$p,a,b$������
$n,q\leq3\times10^5$��
$Solution$
$p,a,b$����һ�����ϡ�
��ô���$a$��$p$�����ȣ��𰸾���$\min(dep[p],\ k)*(sz[p]-1)$������$O(1)$���㡣
���$a$��$p$�������У��𰸾���$\sum_{dis(a,p)\leq k}sz[a]-1$��
���ڵڶ��������ʵ�ʾ��Ƕ������$dep[p]\sim dep[p]+k$�Ҵ���$p$�����ڵĵ��$size$��͡�
��$dep$Ϊ�±꣬���Ƕ�$p$������������ˡ�������ϯ��/�߶����ϲ���ʱ�ո��Ӷ�$O(n\log n)$��

Ҳ��������״����ά�����Ϊ$x$�����е��$size$�͡��������찮�ܲ����ڽ���һ������ʱ��$Ans$��ȥ$sum(dep[p],dep[p]+k)$���뿪�������ʱ��$Ans$�ټ���$sum(dep[p],dep[p]+k)$���Ϳ��Եõ���������Ĵ�$Ans$�ˡ�
ʱ�临�Ӷ�$O(n\log n)$��

�õ��������±�����ȣ����Կ������³����ʷ֡�ͬ��$f[x][i]$��ʾ��$x$Ϊ�����Ϊ$i$�ĵ��$size$�͡�
�����ʷ�ÿ�μ̳��ض���Ҫ���������һλ��������Ҫ������ͣ�����ǰ׺�;Ͳ���ά���ˡ��������ǿ���ά����׺�͡�
���Ӷ�$O(n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int sz[N],dep[N],mxd[N],son[N],pos[N];
LL Ans[N],f[N];//f:��׺�� //LL!
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int Enum,H[N],nxt[N<<1],to[N<<1];
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
}T;
struct Quries
{
	int Enum,H[N],nxt[N],id[N],k[N];
	inline void AE(int ID,int K,int u)
	{
		id[++Enum]=ID, k[Enum]=K, nxt[Enum]=H[u], H[u]=Enum;
	}
}Q;


inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void DFS1(int x,int fa)
{
	int mx=-1;/*-1!*/ sz[x]=1;
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa)
			dep[v]=dep[x]+1, DFS1(v,x), sz[x]+=sz[v], mxd[v]>mx&&(mx=mxd[v],son[x]=v);
	mxd[x]=mx+1;
}
void DFS2(int x,int fa)
{
	static int Index=0;
	int px=pos[x]=++Index;// f[px]=sz[x]-1;
	if(!son[x]) return;
	DFS2(son[x],x), f[px]+=f[px+1];
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa && v!=son[x])
		{
			DFS2(v,x); int pv=pos[v];
			for(int j=0,lim=mxd[v]; j<lim; ++j) f[px+j+1]+=f[pv+j];
			f[px]+=f[pv];
		}
	LL sum=f[px];
	for(int i=Q.H[x],mx=mxd[x]; i; i=Q.nxt[i])
	{
		int k=Q.k[i],id=Q.id[i];
		Ans[id]=1ll*std::min(dep[x],k)*(sz[x]-1)+sum-(k>=mx?0:f[px+k+1]);
	}
	f[px]+=sz[x]-1;
}

int main()
{
	int n=read(),q=read();
	for(int i=1; i<n; ++i) T.AE(read(),read());
	for(int i=1; i<=q; ++i) Q.AE(i,read(),read());
	DFS1(1,1), DFS2(1,1);
	for(int i=1; i<=q; ++i) printf("%lld\n",Ans[i]);

	return 0;
}
