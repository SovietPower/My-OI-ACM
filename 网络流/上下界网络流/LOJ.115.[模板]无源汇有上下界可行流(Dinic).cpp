//输出一条边的流量 即输出它反向边上的流量与下界之和 
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
typedef long long LL;
const int N=205,M=10205+N;
const LL INF=1e12;

int n,m,srcc,dess,lev[N],q[N],Enum,cur[N],H[N],nxt[M<<1],to[M<<1];
LL dgr[N],cap[M<<1],low[M],upp;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,LL w)
{
	to[++Enum]=v, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
}
bool BFS()
{
	for(int i=srcc;i<=dess;++i) cur[i]=H[i],lev[i]=0;
	lev[srcc]=1, q[0]=srcc;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(!lev[to[i]] && cap[i])
			{
				lev[to[i]]=lev[x]+1,q[t++]=to[i];
				if(to[i]==dess) return 1;
			}
	}
	return 0;
}
LL Dinic(int u,LL flow)
{
	if(u==dess) return flow;
	LL used=0,delta;
	for(int &i=cur[u];i;i=nxt[i])
		if(lev[to[i]]==lev[u]+1 && cap[i])
		{
			delta=Dinic(to[i],std::min(flow-used,cap[i]));
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
	n=read(),m=read();
	Enum=1, srcc=0, dess=n+1;
	LL tmp=0;
	for(int u,v,i=1;i<=m;++i)
	{
		u=read(),v=read(),low[i]=read(),upp=read(),
		dgr[u]-=low[i], dgr[v]+=low[i], AddEdge(u,v,upp-low[i]);
	}
	for(int i=1;i<=n;++i)
		if(dgr[i]>0) AddEdge(srcc,i,dgr[i]),dgr[srcc]+=dgr[i];
		else if(dgr[i]<0) AddEdge(i,dess,-dgr[i]);
	while(BFS()) tmp+=Dinic(srcc,INF);
	if(tmp==dgr[srcc])
	{
		puts("YES");
		for(int i=2;i<=m<<1;i+=2) printf("%lld\n",cap[i^1]+low[i>>1]);
	}
	else puts("NO");
	return 0;
}
