/*
545ms	33600KB
$Description$
给定一棵带边权的树。多次询问，每次给出两个点s,t，求从S到T可获得的最大权值和。权值定义为经过的点权(只计算一次)减去经过的边权(多次叠加计算)，且每条边最多只能走两次。
$Solution$
ps:随便走指按最优方案走。
对于询问u->v，令w=LCA(u,v)，我们分别求u->w和w->v的答案。
可以想到，令sub[x]表示从x出发在x的子树中随便走可得到的最大权值和，则sub[fa[x]]=∑max(0,sub[son[x]]-2*val[x->son[x]])。
对于u->w，简单路径上的边只能走一次，上面点的sub[]可以累加。于是考虑前缀和，求个 从根节点到达当前节点前，可以在任意节点的子树中随便走，得到的最大权值和sum。
则sum[x]=sum[fa[x]]+sub[fa[x]]-(x对sub[fa[x]]的贡献)-(val[fa[x]->x])。x对sub[fa[x]]的贡献即max(0,sub[x]-2*val[fa[x]->x])，为方便可以令fe[x]=val[fa[x]->x],f[x]=max(0,sub[x]-2*val[fa[x]->x])。则sum[x]=sum[fa[x]]+sub[fa[x]]-f[x]-fe[x]。
还可以在w的上面随便走，所以令up[x]表示由x向上随便走得到的最大权值和，up[x]=max(0,up[fa[x]]+sub[fa[x]]-f[x]-2*fe[x])。
则Ans(u,v)=sum[u]+sum[v]-2*sum[w]+sub[u]+sub[v]+up[w]？
设u1,v1分别为w->u,w->v路径上要到的第一个点。sum[w]还没有计算w的子树，但sum[u1],sum[v1]都计算了，且分别少个u1,v1对sum[w]的贡献，那就正好算重了一个sum[w]。减掉就行了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

int n,Q,A[N],Enum,H[N],to[N<<1],nxt[N<<1],val[N<<1],sz[N],son[N],fa[N],dep[N],top[N];
LL f[N],fe[N],sub[N],sum[N],up[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], val[Enum]=w, H[v]=Enum;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1, sub[x]=A[x];
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, fe[v]=val[i], DFS1(v), sz[x]+=sz[v], sub[x]+=f[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
	f[x]=std::max(0ll,sub[x]-2ll*fe[x]);
}
void DFS2(int x,int tp)
{
	top[x]=tp;
	sum[x]=sub[fa[x]]-f[x]-fe[x];
	up[x]=std::max(0ll,up[fa[x]]+sum[x]-fe[x]);//up[fa[x]]+sub[fa[x]]-f[x]-2*fe[x]
	sum[x]+=sum[fa[x]];
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x]&&to[i]!=son[x]) DFS2(to[i],to[i]);
	}
}

int main()
{
	n=read(), Q=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read(),read());
	DFS1(1), DFS2(1,1);
	for(int u,v,w,i=1; i<=Q; ++i)
		u=read(), v=read(), w=LCA(u,v), printf("%I64d\n",sum[u]+sum[v]-(sum[w]<<1)+sub[u]+sub[v]-sub[w]+up[w]);
	return 0;
}
