//25884kb	11000ms
//用1e6的数组记录当前路径长度的最少边数 
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5,M=N<<1;

int n,K,Ans=M,root,Min,que[N],Enum,H[N],nxt[M],to[M],val[M],dis[N],num[N],sz[N],exist[1000005];
bool vis[N];

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
void Get_dis(int x,int f,int d,int l)
{
	if(d==K) Ans=std::min(Ans,l);//剪枝! 
	if(d>=K) return;
	dis[++dis[0]]=d, num[dis[0]]=l;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]&&to[i]!=f) Get_dis(to[i],x,d+val[i],l+1);
}
void Get_root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=f)
		{
			Get_root(v,x,tot), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-mx);
	if(mx<Min) Min=mx, root=x;
}
void Solve(int x)
{
	int t=0; vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
		{
			dis[0]=0, Get_dis(to[i],-1,val[i],1);
			for(int i=1; i<=dis[0]; ++i)
				if(/*K-dis[i]>=0 && */exist[K-dis[i]]!=M) Ans=std::min(Ans,num[i]+exist[K-dis[i]]);
			for(int i=1; i<=dis[0]; ++i)//不剪枝的话这别忘if() 
				que[++t]=dis[i], exist[dis[i]]=std::min(exist[dis[i]],num[i]);//2 神tm漏了que清空还能75。。 
		}
	for(int i=1; i<=t; ++i) exist[que[i]]=M;//3 2.3都可以通过再DFS一遍实现 没必要了 
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
			Min=M, Get_root(to[i],x,sz[to[i]]), Solve(root);
}

int main()
{
	n=read(),K=read();
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	for(int i=0; i<=1000000; ++i) exist[i]=M;
	Min=M, Get_root(0,-1,n), Solve(root);
	printf("%d",Ans==M?-1:Ans);

	return 0;
}
