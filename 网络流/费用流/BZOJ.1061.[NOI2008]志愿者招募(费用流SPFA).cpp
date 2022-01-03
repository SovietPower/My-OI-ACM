//1592kb	164ms
//https://www.cnblogs.com/SovietPower/p/9362857.html#_label1
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1007,M=11007<<1,INF=0x3f3f3f3f;

int src,des,n,m,Enum,H[N],nxt[M],fr[M],to[M],cap[M],cost[M],pre[N],dis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w,int c)
{
	fr[++Enum]=u, to[Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, cost[Enum]=c;
	fr[++Enum]=v, to[Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	static std::queue<int> q;
	static bool inq[N];
	memset(dis,0x3f,sizeof dis);
	dis[src]=0, q.push(src);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(int v,i=H[x]; i; i=nxt[i])
			if(cap[i] && dis[v=to[i]]>dis[x]+cost[i])
			{
				dis[v]=dis[x]+cost[i], pre[v]=i;
				if(!inq[v]) inq[v]=1, q.push(v);
			}
	}
	return dis[des]<INF;
}
int MCMF()
{
	int res=0, mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des,v=pre[i]; i!=src; i=fr[v],v=pre[i])
		res+=mn*cost[v], cap[v]-=mn, cap[v^1]+=mn;
	return res;
}

int main()
{
	n=read(), m=read(), Enum=1, src=1, des=n+2;
	for(int i=1; i<=n; ++i) AddEdge(i,i+1,INF-read(),0);
	for(int i=1,l,r; i<=m; ++i) l=read(),r=read(),AddEdge(l,r+1,INF,read());
	AddEdge(n+1,des,INF,0);
	int res=0;
	while(SPFA()) res+=MCMF();
	printf("%d\n",res);

	return 0;
}
