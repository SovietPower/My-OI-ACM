/*
35772kb  1892ms
$Description$
给出一个N个点M条边的无向图，经过一个点的代价是进入和离开这个点的两条边的边权的较大值，求从起点1到点N的最小代价。起点的代价是离开起点的边的边权，终点的代价是进入终点的边的边权。
$Solution$
最直接的方法是把每条边作为一个点，对于连接同一个点的两条边连一条新边，最后把连接1和n的点分别连S、T，跑最短路 
但这样边数是O(m^2)的 
对于路径上相邻两条边(i,j,v1)和(j,k,v2)，v1<v2，考虑如何构图把v1比v2小的部分补上 
那么对于点j拆点，每个点对应一条出边或入边，按边权排序，设相邻两点对应权值为v1,v2(v1<v2)，那么建边(j',j,0),(j,j',v2-v1) 
最后起点处的代价没有被计算，在起点的每条出边加上一个点即可 
复杂度O(mlogm)
很像的边表边很容易写错。。
不会写代码。。
没有边权范围要longlong 
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define pr std::pair<LL,int>
#define mp std::make_pair
typedef long long LL;
const int N=4e5+5,M=4e5+5,MAXIN=3e6;//N:两倍边数 
const LL INF=1ll<<60;

int src,des,n,m,Enum,H[N],nxt[M<<2],to[M<<2],val[M<<2],tmp[M];//边数一直错。。mdzz 开始一共4e5条边 
int num,h[N>>1],tto[M],tnxt[M],tval[M];
LL dis[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
std::priority_queue<pr> q;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline bool cmp(int i,int j) {return tval[i]<tval[j];}
inline void Add(int u,int v,int w){
	tto[++num]=v, tnxt[num]=h[u], tval[num]=w, h[u]=num;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], val[Enum]=w, H[u]=Enum;
}
void Build()
{
	src=1, des=(m+1)<<1;
	for(int i=1; i<=n; ++i)
	{
		int cnt=0;
		for(int j=h[i]; j; j=tnxt[j])
			tmp[++cnt]=j;//存编号就行了 
		std::sort(tmp+1,tmp+1+cnt,cmp);
		for(int now,next,j=1; j<=cnt; ++j)//~
		{
			now=tmp[j], next=tmp[j+1];//直接拿边号来建就可以了 也是建的双向边 
			if(i==1) AddEdge(src,now,tval[now]);//把连向src的边拆出一个点来 
			if(tto[now]==n) AddEdge(now,des,tval[now]);
			AddEdge(now^1,now,tval[now]);//只建一条边 还有另一个点的边 
			if(j<cnt) AddEdge(now,next,tval[next]-tval[now]), AddEdge(next,now,0);
		}
//		if(cnt)	AddEdge(tmp[cnt]^1,tmp[cnt],tval[tmp[cnt]]);//WA!没有上面两个条件特判！ 
	}
}
LL Dijkstra()
{
	for(int i=src+1; i<=des; ++i) dis[i]=INF;
	dis[src]=0, q.push(mp(0,src));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		if(x==des) return dis[x];
		vis[x]=1;
		for(int v,i=H[x]; i; i=nxt[i])
			if(!vis[v=to[i]] && dis[v]>dis[x]+val[i])
				dis[v]=dis[x]+val[i], q.push(mp(-dis[v],v));
	}
	return dis[des];
}

int main()
{
	n=read(),m=read();
	num=1;
	for(int u,v,w,i=1; i<=m; ++i)
		u=read(),v=read(),w=read(),Add(u,v,w),Add(v,u,w);
	Build();
	printf("%lld",Dijkstra());

	return 0;
}
