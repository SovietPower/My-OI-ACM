#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAX (200000)
const int N=2e5+5,M=N<<1;

int n,K,root,Min,que[N],Enum,H[N],nxt[M],to[M],val[N],dis[N],num[N],sz[N],exist[1000005];
long long Ans[N];
bool vis[N];
 
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
void Get_dis(int x,int f,int d)
{
	int v=gcd(d,val[x]);
	dis[++dis[0]]=v;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]&&to[i]!=f) Get_dis(to[i],x,v);
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
	que[t=1]=val[x], ++Ans[val[x]];
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
		{
			dis[0]=0, Get_dis(to[i],-1,val[x]);
			for(int j=1; j<=dis[0]; ++j)
				for(int k=1; k<=t; ++k)
					++Ans[gcd(dis[j],que[k])];
			for(int j=1; j<=dis[0]; ++j)
				que[++t]=dis[j];
		}
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
			Min=M, Get_root(to[i],x,sz[to[i]]), Solve(root);
}
 
int main()
{
	n=read();
	for(int i=1; i<=n; ++i) val[i]=read();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	Min=M, Get_root(1,-1,n), Solve(root);
	for(int i=1; i<=MAX; ++i) if(Ans[i]) printf("%d %I64d\n",i,Ans[i]);
 
	return 0;
}
