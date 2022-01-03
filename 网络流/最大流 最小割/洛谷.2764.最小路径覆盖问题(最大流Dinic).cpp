/*
最小路径覆盖：是在图中找尽量少的路径，使得每个结点恰好在一条路径上（不同的路径不能有公共点）。注意，单独的结点也可以作为一条路径。 
(DAG)最小路径覆盖数 = 点数n - 最大匹配数m 
证明：因为匹配和路径覆盖意义相对应，对于路径覆盖中的每一条简单路径，除了最后一个“结尾节点”外都有唯一的后继与其对应(即匹配节点) 
所以匹配就是非结尾节点的个数(准确的话匹配数要分奇偶性讨论 并不明白) 
当匹配 即非结尾节点数越多时，结尾节点数就越少，路径条数就越少 
故转为求二分图最大匹配 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
const int N=155*2,M=155*158,INF=1e5;

int n,m,src,des,Link[N],Enum,cur[N],H[N],nxt[M<<1],to[M<<1],cap[M<<1],lev[N],q[N];
bool Mark[N];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
}

bool BFS()
{
	for(int i=src;i<=des;++i) cur[i]=H[i],lev[i]=0;
	lev[src]=1, q[0]=src;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(cap[i] && !lev[to[i]])
			{
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
				if(to[i]==des) return 1;
			}
	}
	return 0;
}
int Dinic(int u,int flow)
{
	if(u==des) return flow;
	int used=0;
	for(int &i=cur[u];i;i=nxt[i])
		if(cap[i] && lev[to[i]]==lev[u]+1)
		{
			int delta=Dinic(to[i],std::min(flow-used,cap[i]));
			if(delta)
			{
				if(to[i]>n) Link[u]=to[i], Mark[to[i]]=1;
				used+=delta, cap[i]-=delta, cap[i^1]+=delta;
				if(used==flow) return flow;
			}
		}
	lev[u]=0;
	return used;
}

int main()
{
	n=read(),m=read(),src=0,des=n+n+1;
	int u,v;
	while(m--)
		u=read(),v=read(),AddEdge(u+n,v,1);
	for(int i=1;i<=n;++i) AddEdge(src,i,INF);
	for(int i=n+1;i<des;++i) AddEdge(i,des,INF);
	int res=n;
	while(BFS()) res-=Dinic(src,INF);
	for(int i=n+1;i<des;++i)
	{
		if(Mark[i]) continue;
		int k=i-n;
		while(k)
			printf("%d ",k),k=Link[k]-n;
		putchar('\n');
	}
	printf("%d",res);

	return 0;
}
