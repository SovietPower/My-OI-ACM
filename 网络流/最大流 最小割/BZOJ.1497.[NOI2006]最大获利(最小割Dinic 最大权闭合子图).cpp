//裸最大权闭合子图...
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int N=55005,M=N<<2,INF=1e8;

int n,m,src,des;
int Enum,H[N],nxt[M<<1],to[M<<1],cap[M<<1],q[N],lev[N],cur[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
}
bool BFS()
{
	for(int i=0;i<=des;++i) lev[i]=0,cur[i]=H[i];
	lev[src]=1, q[0]=src;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(!lev[to[i]] && cap[i])
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
		if(lev[to[i]]==lev[u]+1 && cap[i])
		{
			int delta=Dinic(to[i],std::min(cap[i],flow-used));
			if(delta)
			{
				cap[i]-=delta, cap[i^1]+=delta, used+=delta;
				if(used==flow) return flow;
			}
		}
	lev[u]=0;
	return used;
}

int main()
{
	Enum=1;
	n=read(),m=read(),src=0,des=n+m+1;
	int sum=0;
	for(int c,i=1;i<=n;++i) c=read(),AddEdge(m+i,des,c);
	for(int a,b,c,i=1;i<=m;++i)
		a=read(),b=read(),sum+=(c=read()),
		AddEdge(i,m+a,INF),AddEdge(i,m+b,INF),AddEdge(src,i,c);
	while(BFS()) sum-=Dinic(src,INF);
	printf("%d",sum);

    return 0;
}
