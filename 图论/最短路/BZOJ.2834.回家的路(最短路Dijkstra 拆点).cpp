/*
13028kb	604ms
对于相邻的、处在同在一行或一列的车站连边，然后用dis[x][0/1]（或者拆点）分别表示之前是从横边还是竖边到x的，跑最短路。
我选择拆点。。
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
#define pr std::pair<int,int>
const int N=2e5+7,M=N*3,INF=0x3f3f3f3f;

int Enum,H[N],nxt[M],to[M],len[M];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int x,y,id;
}p[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
bool cmpx(Node a,Node b) {return a.x==b.x?a.y<b.y:a.x<b.x;}
bool cmpy(Node a,Node b) {return a.y==b.y?a.x<b.x:a.y<b.y;}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void Dijkstra(int s,int t,int n)
{
	static int dis[N];
	static bool vis[N];
	static std::priority_queue<pr> q;

	memset(dis,0x3f,sizeof dis);
	dis[s]=dis[s+n]=0, q.push(mp(0,s)), q.push(mp(0,s+n));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+len[i])
				q.push(mp(-(dis[v]=dis[x]+len[i]),v));
	}
	printf("%d\n",dis[t]==INF&&dis[t+n]==INF?-1:std::min(dis[t],dis[t+n]));
}

int main()
{
	int m=read(),n=read();//n
	for(int i=1; i<=n; ++i) p[i]=(Node){read(),read(),i};
	p[++n]=(Node){read(),read(),n}, p[++n]=(Node){read(),read(),n};

	std::sort(p+1,p+1+n,cmpx);
	for(int i=2; i<=n; ++i)
		if(p[i].x==p[i-1].x) AE(p[i].id,p[i-1].id,(p[i].y-p[i-1].y)<<1);
	std::sort(p+1,p+1+n,cmpy);
	for(int i=2; i<=n; ++i)
		if(p[i].y==p[i-1].y) AE(p[i].id+n,p[i-1].id+n,(p[i].x-p[i-1].x)<<1);
	for(int i=1; i<=n; ++i) AE(p[i].id,p[i].id+n,1);

	Dijkstra(n-1,n,n);

	return 0;
}
