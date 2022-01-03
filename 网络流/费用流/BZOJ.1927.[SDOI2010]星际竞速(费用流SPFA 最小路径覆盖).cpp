/*
每个点可以跳到一个点->即每个点可以到S，再从S重新选择新一条路->好像最小路径覆盖 
对一条路径u->v建边u->v'(->T)，表示可以通过u到过v，但是一共只能经过u一次 
移动可以直接S->u'(->T)，cost=A[u]，表示花费A[u]可以直接走过它 
将每个点拆成i,i'，连边S->i、i'->T，这样求最大流所有点一定都会经过一次 
比上一种方法少2n条边 但比上个..慢些..
cap都是1，优化下 更慢了==
*/
#include<queue>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=850<<1,M=18000,INF=0x3f3f3f3f;

int n,m,A[N],src,des,Enum,H[N],fr[M<<1],to[M<<1],nxt[M<<1],cap[M<<1],cost[M<<1];
int dis[N],pre[N];
bool inq[N];
std::queue<int> q;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int c)
{
	to[++Enum]=v, nxt[Enum]=H[u], fr[Enum]=u, cap[Enum]=1, cost[Enum]=c, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], fr[Enum]=v, cap[Enum]=0, cost[Enum]=-c, H[v]=Enum;
}
bool SPFA()
{
	memset(dis,0x3f,sizeof dis);
	dis[src]=0, q.push(src);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		inq[x]=0;
		for(int i=H[x];i;i=nxt[i])
			if(cap[i] && dis[to[i]]>dis[x]+cost[i])
			{
				dis[to[i]]=dis[x]+cost[i], pre[to[i]]=i;
				if(!inq[to[i]]) inq[to[i]]=1, q.push(to[i]);
			}
	}
	return dis[des]<INF;
}
int MCMF()
{
	int res=0;
//	for(int i=des;i!=src;i=fr[pre[i]])
//		mn=std::min(mn,cap[pre[i]]);
	for(int i=des;i!=src;i=fr[pre[i]])
		cap[pre[i]]^=1,cap[pre[i]^1]^=1,res+=cost[pre[i]];
	return res;
}

int main()
{
	Enum=1;
	n=read(),m=read();
	src=0, des=n<<1|1;
	for(int i=1;i<=n;++i)
		AddEdge(src,i+n,read()), AddEdge(src,i,0), AddEdge(i+n,des,0);
	for(int u,v,w,i=1;i<=m;++i)
	{
		u=read(),v=read(),w=read();
		if(u>v) std::swap(u,v);
		if(u==v) continue;
		AddEdge(u,v+n,w);
	}
	int flow=0;
	while(SPFA()) flow+=MCMF();
	printf("%d",flow);

	return 0;
}
