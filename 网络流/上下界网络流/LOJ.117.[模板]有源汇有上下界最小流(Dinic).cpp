/*
有源汇有上下界最小流 
Sol1. 首先和无源汇网络流一样建图，求SS->TT最大流；
然后连边(T->S,[0,INF])，再求一遍SS->TT最大流，答案为新添加边的流量 
无解情况: 连边后再求最大流+之前的最大流 != ∑dgr[](dgr>0) 
解释: 第一次最大流已经满足下界，满足下界的情况下能流的边已尽量流满 
那么残量网络的最大流就会尽可能小了 

Sol2. 首先和无源汇网络流一样建图，然后连边(T->S,[0,INF])，求SS->TT的最大流okflow 
然后删去T->S的这条边，求T->S的最大流mn，则答案为okflow-mn 
解释: 第一次是求可行流，使其满足流量下界；
第二次利用 反向弧流量的增加=正向边流量的减少，由T->S的最大流就是S->T最大能减少的流量(满足可行流) 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5e4+9,M=125009+N;
const LL INF=1e14;

int n,m,src,des,Enum,H[N],nxt[M<<1],to[M<<1],lev[N],cur[N],q[N],dgr[N];
LL cap[M<<1];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,LL w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	for(int i=0;i<=n+1;++i) lev[i]=0,cur[i]=H[i];
	lev[src]=1, q[0]=src;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(!lev[to[i]]&&cap[i])
			{
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
				if(to[i]==des) return 1;
			}
	}
	return 0;
}
LL Dinic(int u,LL flow)
{
	if(u==des) return flow;
	LL used=0;
	for(int &i=cur[u];i;i=nxt[i])
		if(lev[to[i]]==lev[u]+1 && cap[i])
		{
			LL delta=Dinic(to[i],std::min(cap[i],flow-used));
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
	n=read(),m=read();int s=read(),t=read(),ss=0,tt=n+1;
	LL low,upp,sum=0,okflow=0;
	for(int u,v,i=1;i<=m;++i)
	{
		u=read(),v=read(),low=read(),upp=read(),
		dgr[u]-=low,dgr[v]+=low, AddEdge(u,v,upp-low);
	}
	for(int i=1;i<=n;++i)
		if(dgr[i]>0) AddEdge(ss,i,dgr[i]),sum+=dgr[i];
		else if(dgr[i]<0) AddEdge(i,tt,-dgr[i]);
	src=ss, des=tt;
	while(BFS()) okflow+=Dinic(src,INF);
	AddEdge(t,s,INF);
	while(BFS()) okflow+=Dinic(src,INF);
	if(okflow==sum) printf("%lld",cap[Enum]);
	else printf("please go home to sleep");

	return 0;
}
