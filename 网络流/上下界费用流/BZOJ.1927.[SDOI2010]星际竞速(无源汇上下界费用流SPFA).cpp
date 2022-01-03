/*
每个点i恰好(最少+最多)经过一次->拆点+限制流量上下界(i,i',[1,1],0) 
然后无源汇可行流 不需要源汇。

注: SS只会连i'，求SS->TT的最大流 该走的i->i'是不会不走的 
*/
#include<queue>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define gc() getchar()
const int N=850<<1,M=20000,INF=0x3f3f3f3f;

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
inline void AddEdge(int u,int v,int w,int c)
{
	to[++Enum]=v, nxt[Enum]=H[u], fr[Enum]=u, cap[Enum]=w, cost[Enum]=c, H[u]=Enum;
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
	int mn=INF,res=0;
	for(int i=des;i!=src;i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des;i!=src;i=fr[pre[i]])
		cap[pre[i]]-=mn,cap[pre[i]^1]+=mn,res+=mn*cost[pre[i]];
	return res;
}

int main()
{
	Enum=1;
	n=read(),m=read();int p=n<<1|1/*中转*/,ss=0,tt=n*2+2;
	for(int i=1;i<=n;++i)
	{
		AddEdge(p,i,1,read()), AddEdge(i+n,p,1,0);
//		AddEdge(i,i+n,0,0),//下界-上界后 边cap为0，有没有一样了 
		AddEdge(ss,i+n,1,0), AddEdge(i,tt,1,0);
	}
	for(int u,v,w,i=1;i<=m;++i)
	{
		u=read(),v=read(),w=read();
		if(u>v) std::swap(u,v);
		if(u==v) continue;
		AddEdge(u+n,v,1,w);
	}
	src=ss, des=tt;
	int flow=0;
	while(SPFA()) flow+=MCMF();
	printf("%d",flow);

	return 0;
}
