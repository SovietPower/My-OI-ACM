/*
545ms	33600KB
$Description$
����һ�ô���Ȩ���������ѯ�ʣ�ÿ�θ���������s,t�����S��T�ɻ�õ����Ȩֵ�͡�Ȩֵ����Ϊ�����ĵ�Ȩ(ֻ����һ��)��ȥ�����ı�Ȩ(��ε��Ӽ���)����ÿ�������ֻ�������Ρ�
$Solution$
ps:�����ָ�����ŷ����ߡ�
����ѯ��u->v����w=LCA(u,v)�����Ƿֱ���u->w��w->v�Ĵ𰸡�
�����뵽����sub[x]��ʾ��x������x������������߿ɵõ������Ȩֵ�ͣ���sub[fa[x]]=��max(0,sub[son[x]]-2*val[x->son[x]])��
����u->w����·���ϵı�ֻ����һ�Σ�������sub[]�����ۼӡ����ǿ���ǰ׺�ͣ���� �Ӹ��ڵ㵽�ﵱǰ�ڵ�ǰ������������ڵ������������ߣ��õ������Ȩֵ��sum��
��sum[x]=sum[fa[x]]+sub[fa[x]]-(x��sub[fa[x]]�Ĺ���)-(val[fa[x]->x])��x��sub[fa[x]]�Ĺ��׼�max(0,sub[x]-2*val[fa[x]->x])��Ϊ���������fe[x]=val[fa[x]->x],f[x]=max(0,sub[x]-2*val[fa[x]->x])����sum[x]=sum[fa[x]]+sub[fa[x]]-f[x]-fe[x]��
��������w����������ߣ�������up[x]��ʾ��x��������ߵõ������Ȩֵ�ͣ�up[x]=max(0,up[fa[x]]+sub[fa[x]]-f[x]-2*fe[x])��
��Ans(u,v)=sum[u]+sum[v]-2*sum[w]+sub[u]+sub[v]+up[w]��
��u1,v1�ֱ�Ϊw->u,w->v·����Ҫ���ĵ�һ���㡣sum[w]��û�м���w����������sum[u1],sum[v1]�������ˣ��ҷֱ��ٸ�u1,v1��sum[w]�Ĺ��ף��Ǿ�����������һ��sum[w]�����������ˡ�
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
