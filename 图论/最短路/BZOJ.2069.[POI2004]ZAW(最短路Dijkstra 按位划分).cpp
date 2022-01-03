/*
1364kb	140ms
$Description$
给定一张带权图（边是双向的，但不同方向长度不同）。求从1出发，至少经过除1外的一个点，再回到1的最短路。点和边不能重复经过。
n≤5000，m≤10000。
$Solution$
最短路自然是从1走到一个点，然后从这个点通过最短路到达另一个点，再回到1。
我们把与1相邻的点都标记为关键点，然后把1从图中删去，就成了求任意一对关键点之间的最短路。
显然不能枚举每个点跑最短路。我们把点划分成两个集合$x,y$，$x$中的点初始dis为len(1,x)，从这些点开始跑最短路。
最后用$y$中的点的dis+len(y,1)更新答案。
当然这其实就是根据划分保留1的某些出边（选择从某些点出去），从1跑最短路。
怎么划分集合呢。枚举每一位，对这一位是0/1的点分别作为$x,y$集合求一遍。
因为两个点至少有一位不同，所以每对点至少被求了一次。当然直接枚举下标的二进制也可以。
所以只需要logn次最短路，复杂度$O(n\log^2n)$。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=5005,M=20005,INF=0x3f3f3f3f;

int A[N],Enum,H[N],nxt[M],to[M],len[M],dis[N],df[N],dt[N];
std::priority_queue<pr> q;
bool exist[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
}
void Dijkstra()
{
	static bool vis[N];

	memset(vis,0,sizeof vis);
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int v,i=H[x]; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i]) q.push(mp(-(dis[v]=dis[x]+len[i]),v));
	}
}

int main()
{
	int n=read(),m=read(),cnt=0;
	memset(df,0x3f,sizeof df), memset(dt,0x3f,sizeof dt);
	for(int u,v; m--; )
	{
		u=read(),v=read();
		if(u==1) df[v]=read(),dt[v]=read(),!exist[v]&&(A[++cnt]=v,exist[v]=1);
		else if(v==1) dt[u]=read(),df[u]=read(),!exist[u]&&(A[++cnt]=u,exist[u]=1);
		else AE(u,v,read()),AE(v,u,read());
	}
	int ans=INF;
	for(int bit=1; bit<=cnt; bit<<=1)//不需要>>1&bit...
	{//直接枚举下标的二进制好了 
		memset(dis,0x3f,sizeof dis);
		for(int i=1,x; i<=cnt; ++i)
			if(i&bit) x=A[i], q.push(mp(-(dis[x]=df[x]),x));
		Dijkstra();
		for(int i=1,x; i<=cnt; ++i)
			if(!(i&bit)) x=A[i], ans=std::min(ans,dis[x]+dt[x]);

		memset(dis,0x3f,sizeof dis);
		for(int i=1,x; i<=cnt; ++i)
			if(!(i&bit)) x=A[i], q.push(mp(-(dis[x]=df[x]),x));
		Dijkstra();
		for(int i=1,x; i<=cnt; ++i)
			if(i&bit) x=A[i], ans=std::min(ans,dis[x]+dt[x]);
	}
	printf("%d\n",ans);

	return 0;
}
