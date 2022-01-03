/*
1240K	735MS
$Description$
有$n$个人在一条直线上跑步，每个人的起点 $Si$、终点 $Ei$ 已知；每个点可以放一个广告牌，一个人$i$能看到的广告牌数量为 $Ei-Si+1$。
要求使每个人看到的广告牌数量不小于 $k$ (若 $Ei-Si+1<k$ 则应看到 $Ei-Si+1$)。输出最少需要多少广告牌及方案。
$Solution$
设 $Sum_i$ 表示在 $[1,i]$ 广告牌总数，那么由题意有 $Sum_{Ei}-Sum_{Si-1}>=k$，这是对于 $Ei-Si+1>=k$ 的 
设 $C=Ei-Si+1$，若C<k，则 $Sum_{Ei}-Sum_{Si-1}=C$，拆成两个式子 
同时每个位置的限制 $0<=Sum_i-Sum_{i-1}<=1$
以 $Sum_i$ 为点建边，求 $Sum_0$ -> $Sum_n$ 的最长路即为最少需要数量 
输出方案: 若$i$处建了广告牌，则有 $dis_i-dis_{i-1}=1$ 

注意，Dijkstra不能用来求最长路 
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=10005,M=60005,INF=0x3f3f3f3f;

int n,K,Enum,H[N<<1],nxt[M],to[M],val[M],dis[N<<1];
bool vis[N<<1];
//std::priority_queue<pr> q;
std::queue<int> que;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
}
//int Dijkstra(int mn,int mx)
//{
//	for(int i=mn+1; i<=mx; ++i) dis[i]=-INF;
//	q.push(mp(0,mn));
//	while(!q.empty())
//	{
//		int x=q.top().second;q.pop();
//		if(vis[x]) continue;
//		vis[x]=1;
//		for(int i=H[x]; i; i=nxt[i])
//			if(dis[to[i]]<dis[x]+val[i])
//			{
//				dis[to[i]]=dis[x]+val[i];
//				if(!vis[to[i]]) q.push(mp(dis[to[i]],to[i]));
//			}
//	}
//	return dis[mx];
//}
int SPFA(int mn,int mx)
{
	for(int i=mn+1; i<=mx; ++i) dis[i]=-INF;
	que.push(mn);
	while(!que.empty())
	{
		int x=que.front();que.pop();
		vis[x]=0;
		for(int i=H[x]; i; i=nxt[i])
			if(dis[to[i]]<dis[x]+val[i])
			{
				dis[to[i]]=dis[x]+val[i];
				if(!vis[to[i]]) que.push(to[i]),vis[to[i]]=1;
			}
	}
	return dis[mx];
}

int main()
{
	K=read(),n=read();
	int mx=0,mn=N<<1;
	for(int st,ed,t,i=1; i<=n; ++i)
	{
		st=read()+N, ed=read()+N;
		if(st>ed) std::swap(st,ed);
		mn=std::min(mn,--st), mx=std::max(mx,ed);
		if((t=ed-st)<K) AddEdge(st,ed,t),AddEdge(ed,st,-t);
		else AddEdge(st,ed,K);
	}
	mn-=2;
	for(int i=mn; i<=mx; ++i) AddEdge(i-1,i,0),AddEdge(i,i-1,-1);
	printf("%d\n",SPFA(mn,mx));
	for(int i=mn; i<=mx; ++i)
		if(dis[i]==dis[i-1]+1) printf("%d\n",i-N);
	return 0;
}
