/*
16232kb	456ms
想一下能猜出，最优解中海拔只有0和1，且海拔相同的点都在且只在1个连通块中。
这就是个平面图最小割。~~也可以转~~必须转对偶图最短路，不然只能T到90分了。。边的方向看着定就行。
不能忽略回去的边，因为最小割的形状可能很奇怪。
平面图点数就是(n-1)^2了。但是边数不是4(n-1)^2，是4n(n-1)！。。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<LL,int>
#define ID(x,y) ((x-1)*nn+y)
typedef long long LL;
const int N=500*500+5,M=4*500*501+5;

int n,nn,Enum,H[N],nxt[M],to[M],len[M];
bool vis[N];
LL dis[N];
std::priority_queue<pr> q;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define AddEdge(u,v) to[++Enum]=v,nxt[Enum]=H[u],H[u]=Enum,len[Enum]=read()
LL Dijkstra(int S,int T)
{
	memset(dis,0x3f,sizeof dis);
	dis[S]=0, q.push(mp(0,S));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=H[x]; i; i=nxt[i])
			if(dis[to[i]]>dis[x]+len[i])
				q.push(mp(-(dis[to[i]]=dis[x]+len[i]),to[i]));
	}
	return dis[T];
}

int main()
{
	n=read()+1, nn=n-1; int S=0, T=nn*nn+1;

	for(int j=1; j<n; ++j) AddEdge(S,ID(1,j));//i==1
	for(int i=2; i<n; ++i)
		for(int j=1; j<n; ++j) AddEdge(ID(i-1,j),ID(i,j));
	for(int j=1; j<n; ++j) AddEdge(ID(nn,j),T);//i==n

	for(int i=1; i<n; ++i)
	{
		AddEdge(ID(i,1),T);//j==1
		for(int j=2; j<n; ++j) AddEdge(ID(i,j),ID(i,j-1));
		AddEdge(S,ID(i,nn));//j==n
	}

	for(int j=1; j<n; ++j) AddEdge(ID(1,j),S);
	for(int i=2; i<n; ++i)
		for(int j=1; j<n; ++j) AddEdge(ID(i,j),ID(i-1,j));
	for(int j=1; j<n; ++j) AddEdge(T,ID(nn,j));

	for(int i=1; i<n; ++i)
	{
		AddEdge(T,ID(i,1));
		for(int j=2; j<n; ++j) AddEdge(ID(i,j-1),ID(i,j));
		AddEdge(ID(i,nn),S);
	}

	printf("%lld\n",Dijkstra(S,T));

	return 0;
}
