/*
129ms	14336KB
$Description$
给定一棵$n$个点的树。在每个点$i$你可以补充$g_i$的油量，经过一条边需要花费边长的油量。你可以选择从任意一个点出发，任意在树上走直到油量耗尽或不能走（不能重复经过同一个点）。求最多能经过多少个点。
$n\leq10^5$。
$Solution$
点分治。对每个分治重心$rt$，求出从$rt$到子树内某个点至少需要多少初始油量、从子树内某个点到$rt$，会剩下多少油量。然后`sort`一下合并即可。注意不要合并来自同一棵子树内的路径，记两个来自不同子树的最大值就行了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 400000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,INF=1<<30;

int Ans,Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],A[N],Min,root,sz[N],cnt1,cnt2;
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int s,dep,bel;
	bool operator <(const Node &x)const
	{
		return s<x.s;//按s排序啊（我怎么按dep了mdzz）
	}
}f[N],g[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void FindRoot(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa) FindRoot(v,x,tot), sz[x]+=sz[v], mx=std::max(mx,sz[v]);
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int fa,int need,int need2,int sum,int dep,int anc)
{//need:v->x当前点至少需要要有多少油量 rest:v->x会剩下多少油量 need2:x->v最少需要多少起始油量 sum:x->v一共多少油量 rest=A[root]+sum
	g[++cnt2]=(Node){need2,dep,anc}, sum+=A[x];
	if(A[x]>=need) f[++cnt1]=(Node){sum,dep+1,anc};
	for(int i=H[x],v,w; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa)
			w=len[i], DFS(v,x,w+std::max(0,need-A[x]),std::max(need2,w-sum),sum-w,dep+1,anc);
}
void Solve(int x)
{
	vis[x]=1, cnt1=cnt2=1, f[1]=(Node){0,1,0}, g[1]=(Node){0,0,0};
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) DFS(v,x,len[i],len[i],-len[i],1,v);
	for(int i=1,a=A[x]; i<=cnt1; ++i) f[i].s+=a;
	std::sort(f+1,f+1+cnt1), std::sort(g+1,g+1+cnt2);
	Node a=(Node){0,0,0},b=a;
	int res=0; g[cnt2+1].s=INF;
	for(int i=1,j=1; i<=cnt1; ++i)
	{
		while(g[j].s<=f[i].s)
		{
			if(g[j].dep>a.dep)
				if(g[j].bel!=a.bel) b=a, a=g[j];
				else a=g[j];
			else if(g[j].dep>b.dep && g[j].bel!=a.bel) b=g[j];
			++j;
		}
		if(f[i].bel!=a.bel) res=std::max(res,f[i].dep+a.dep);
		else res=std::max(res,f[i].dep+b.dep);
	}
	Ans=std::max(Ans,res);
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) Min=N, FindRoot(v,x,sz[v]), Solve(root);
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read(),read());
	Ans=1, Min=N, FindRoot(1,1,n), Solve(root), printf("%d\n",Ans);

	return 0;
}
