/*
576ms	9300KB
$Description$
给定一张图，走1距离花费1时间。H在1号点有一家披萨店。有$k$个订单，每个订单有收到订单时间$s_i$，需送到的位置$u_i$，披萨被做好的时间$t_i$。
披萨$i$在$t_i$时间在1号店做好后，H才能在1号店拿起任意多披萨去送。每一时刻H可以带任意多的披萨，但必须严格按照订单顺序送披萨。
最小化 每个订单得到披萨所需的等待时间的最大值。
$Solution$
因为严格按照顺序送披萨，所以可以$f[i]$表示送完前$i$个披萨并还留在$u_i$位置所需的最短时间。
但怎么使最大值最小化呢。。二分答案$x$，设送到时间为$p_i$，满足$x-s_i\geq p_i$，即$x-p_i\geq s_i$则可以转移。
设$d_{i,j}$为$i$到$j$距离。然后考虑一次拿起$i+1~j$的披萨去送，花的时间是$d_{1,i}+\max_{k=i+1~j}t_k+d_{i+1,i+1}+...+d_{j-1,j}$，对每个$l∈[i+1,j]$要有$x-(f[i]+d_{1,i}+\max_{k=i+1~l}t_k+d_{i+1,i+1}+...+d_{l-1,l})-s_i\geq 0$。
发现只要拿$f[i]$去依次更新$f[j](j>i)$时可以维护几个量，保证满足条件。所以转移就好了。。（具体不想写了。。）
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define pc putchar
#define pr std::pair<LL,LL>
using namespace std;
typedef long long LL;
const int N=1005,M=1e5+6;
const LL INF=1e16;

int Enum,H[N],nxt[M],to[M],val[M],u[N],s[N],t[N];
LL d[N][N],dis[N],f[N];
bool vis[N];
std::priority_queue<pr> q;

inline int read()
{
	int now=0; char c=gc();
	for(; !isdigit(c); c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void Dijkstra(int s)
{
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof dis);
	dis[s]=0, q.push(pr{0,s});
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=H[x],v; i; i=nxt[i])
			if(dis[v=to[i]]>dis[x]+val[i])
				dis[v]=dis[x]+val[i], q.push(pr{-dis[v],v});
	}
}
bool Check(LL x,int n)
{
	if(x+s[1]-(t[1]+d[1][u[1]])<0) return 0;
	f[0]=0;
	for(int i=1; i<=n; ++i) f[i]=INF;
	for(int i=0; i<n; ++i)
	{
		if(f[i]==INF) continue;
		int maxt=0,pi=u[i];
		LL sum=0,now=INF,nowmax=0,tmp=f[i]+d[1][pi];
		for(int j=i+1; j<=n; ++j)
		{
			int pj=u[j];
			if(j!=i+1) sum+=d[u[j-1]][pj];
			else sum+=d[1][pj];
			maxt=std::max(maxt,t[j]);
			now=std::min(now,x+s[j]-tmp-sum);
			nowmax=std::max(nowmax,std::max(maxt-tmp,0ll));
			if(now<nowmax) break;
			if((x+s[j])-(tmp+sum+std::max(maxt-tmp,0ll))>=0)
				f[j]=std::min(f[j],f[i]+d[1][pi]+sum+std::max(maxt-(f[i]+d[1][pi]),0ll));
		}
		
	}
	return f[n]<INF;
}

int main()
{
	int n=read(),m=read();
	for(int i=1,u,v; i<=m; ++i) u=read(),v=read(),AE(u,v,read());
	for(int i=1; i<=n; ++i)
	{
		Dijkstra(i);
		for(int j=1; j<=n; ++j) d[i][j]=dis[j];
	}
	for(int i=1; i<=n; ++i) d[0][i]=d[i][0]=0;
	int k=read();
	for(int i=1; i<=k; ++i) s[i]=read(), u[i]=read(), t[i]=read();
	LL l=0,r=INF,mid;
	while(l<r)
	{
		if(Check(mid=l+r>>1,k)) r=mid;
		else l=mid+1; 
	}
	printf("%lld\n",l);

	return 0;
}
