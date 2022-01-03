/*
17660kb	1932ms
需要判断一条边是否是所有直径都经过的边 
可以证明(想象)，树上的多条直径一定是从某个(些)点出发，中间经过同一条链(为方便把链上的边叫做关键边好了)，再于某个(些)点结束。
只需要判断当前求出直径上的所有边是否为关键边。如果一条边(u->v)不是关键边，那么说明它(直径)的前驱u，除了v之外还有u->v'可以满足最长(得到直径)，于是对每个点记录子节点的最远(直径)、次远距离(非严格，在另一棵子树上)就好了。
如果是从R1出发，这样我们可以判掉R2那边的非关键边，从R2倒着再一遍即可判掉R1，得到中间那条链。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;
const LL INF=1e10;

int n,Ans,root,Enum,H[N],to[N<<1],nxt[N<<1],fa[N];
LL Max,dis[N],mx[N],s_mx[N],val[N<<1];
bool is_d[N],Mark[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void pre_DFS(int x,LL d)
{
	if(d>Max) Max=d, root=x;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x]) fa[to[i]]=x,pre_DFS(to[i],d+val[i]);
}
void DFS(int x,int f)
{
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=f)
		{
			DFS(v,x);
			if(mx[x]<val[i]+mx[v]) mx[x]=val[i]+mx[v];
			else if(s_mx[x]<val[i]+mx[v]) s_mx[x]=val[i]+mx[v];
		}
}
void DFS_for_Ans(int x,int f,LL d)
{
	for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=f&&is_d[to[i]])
				if(s_mx[x]+d>=Max) {Mark[x]=1/*在此断开*/; return;}
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f&&is_d[to[i]])
			DFS_for_Ans(to[i],x,d+val[i]);
}

int main()
{
//	freopen("diameter.in","r",stdin);
//	freopen("diameter.out","w",stdout);

	n=read();
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	Max=-INF, pre_DFS(1,0);
	int u=root,v;
	Max=-INF, fa[u]=0, pre_DFS(u,0), v=root;
	while(root!=u) is_d[root]=1,root=fa[root];
	is_d[root]=1;

	DFS(u,-1), DFS_for_Ans(u,-1,0);
	memset(mx,0,sizeof mx), memset(s_mx,0,sizeof s_mx);
	DFS(v,-1), DFS_for_Ans(v,-1,0);
	for(bool f=0; v!=u; v=fa[v],Ans+=f)
		if(Mark[v]) f^=1;
	printf("%lld\n%d",Max,Ans);

	return 0;
}
