/*
2524kb	656ms
题意: 计算树上距离<=K的点对数 
我们知道树上一条路径要么经过根节点，要么在同一棵子树中。
于是对一个点x我们可以这样统计: 计算出所有点到它的距离dep[]，排序后可以O(n)求得<=K的点对数量。
但画个图后我们可以发现，对于在同一棵子树中的路径被重复计算过了。于是我们Ans-=Calc(v)，减去一棵子树中的路径答案，但是这并不是之前x到它们的路径，于是给v的dep[]设一个初始值为w(x->v路径权值)。
这样x的答案就计算完了，将这一过程记作Solve(x)。
考虑如何计算所有点。DFS的效率是和树深有关的。计算x->v时，我们选取v子树上的重心作为下次Solve()的参数。
选取重心每次都会使树的节点个数减半，因此递归深度最坏(链)是logn的。
这样便可O(nlog^2n)解决该题。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=40005,MAXIN=1e5;

int n,K,root,Min,Ans,Enum,H[N],nxt[N<<1],to[N<<1],val[N<<1],dep[N],sz[N],D[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;	
}
void Get_Root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[to[i]] && to[i]!=f)
		{
			Get_Root(v=to[i],x,tot), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int f)
{
	D[++D[0]]=dep[x];
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]&&to[i]!=f)
			dep[to[i]]=dep[x]+val[i], DFS(to[i],x);
}
int Calc(int x,int v)
{
	D[0]=0, dep[x]=v, DFS(x,-1);
	std::sort(D+1,D+1+D[0]);
	int l=1,r=D[0],res=0;
	while(l<r)
		if(D[l]+D[r]<=K) res+=r-l,++l;
		else --r;
	return res;
}
void Solve(int x)
{
	Ans+=Calc(x,0), vis[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
		{
			Ans-=Calc(v=to[i],val[i]);
			Min=N, Get_Root(v,x,sz[v]), Solve(root);
		}
}

int main()
{
	n=read();
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	K=read();
	Min=N, Get_Root(1,-1,n), Solve(root);
	printf("%d",Ans);

	return 0;
}
