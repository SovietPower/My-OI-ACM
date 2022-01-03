/*
5804kb	18088ms
$Description$
给定$n\times m$的带边权网格图。$Q$次询问从点$(x_i,y_i)$到点$(x_j,y_j)$的最短路。
$n\times m\leq 20000,\ Q\leq 10^5$。
$Solution$
对分治线上的每个点进行一次Dijkstra。若该区域点数（面积）为S，则分治线如果选择较短的一边，其上点的个数$\leq\sqrt S$。每次选较短的分治复杂度$O(S\sqrt S\log S)$，若不这样复杂度$O(S\sqrt S\log^2 S)$。
若一次询问的$(x,y)$在分治线两侧，则可以枚举分治线上的点$i$用$\min\{dis_{i,x}+dis_{i,y}\}$更新答案，然后删掉这个询问；若$(x,y)$在分治线同侧，则也用$\min\{dis_{i,x}+dis_{i,y}\}$更新一次答案，继续分治。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 400000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define ID(x,y) ((x-1)*m+y)
#define mp std::make_pair
#define pr std::pair<int,int>
const int N=2e4+5,M=1e5+5,Way[5]={0,-1,0,1,0};

int n,m,val[N][4],dis[N],Ans[M],seq[M],tmp[M],X[N],Y[N];//0:left 1:up 2:right 3:down
char IN[MAXIN],*SS=IN,*TT=IN;
struct Queries
{
	int xa,xb,ya,yb,x,y,id;
}q[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Dijkstra(int s,int xa,int ya,int xb,int yb)
{
	static int Time,vis[N],upd[N];
	static std::priority_queue<pr> q;

	upd[s]=++Time, q.push(mp(dis[s]=0,s));
	while(!q.empty())
	{
		int now=q.top().second;
		q.pop();
		if(vis[now]==Time) continue;
		vis[now]=Time;
//		int x=(now-1)/m+1, y=now%m; if(!y) y=m;
		int x=X[now], y=Y[now];
		for(int v,xn,yn,i=0; i<4; ++i)
		{
			if((xn=x+Way[i])<xa||xn>xb||(yn=y+Way[i+1])<ya||yn>yb) continue;
			if((upd[v=ID(xn,yn)]!=Time&&(upd[v]=Time))/*初始值INF*/||dis[v]>dis[now]+val[now][i])
				q.push(mp(-(dis[v]=dis[now]+val[now][i]),v));
		}
	}
}
void Solve(int xa,int ya,int xb,int yb,int l,int r)
{
	if(xa>xb||ya>yb||l>r) return;
	if(xb-xa<=yb-ya)
	{
		int mid=ya+yb>>1;
		for(int i=xa; i<=xb; ++i)
		{
			Dijkstra(ID(i,mid),xa,ya,xb,yb);
			for(int id,j=l; j<=r; ++j)
				id=seq[j], Ans[q[id].id]=std::min(Ans[q[id].id],dis[q[id].x]+dis[q[id].y]);
		}
		int nowl=l, nowr=r;
		for(int id,i=l; i<=r; ++i)
			if(q[id=seq[i]].ya<mid && q[id].yb<mid) tmp[nowl++]=id;
			else if(q[id].ya>mid && q[id].yb>mid) tmp[nowr--]=id;
		for(int i=l; i<nowl; ++i) seq[i]=tmp[i];
		for(int i=nowr+1; i<=r; ++i) seq[i]=tmp[i];
		Solve(xa,ya,xb,mid-1,l,nowl-1), Solve(xa,mid+1,xb,yb,nowr+1,r);
	}
	else
	{
		int mid=xa+xb>>1;
		for(int i=ya; i<=yb; ++i)
		{
			Dijkstra(ID(mid,i),xa,ya,xb,yb);
			for(int id,j=l; j<=r; ++j)
				id=seq[j], Ans[q[id].id]=std::min(Ans[q[id].id],dis[q[id].x]+dis[q[id].y]);
		}
		int nowl=l, nowr=r;
		for(int id,i=l; i<=r; ++i)
			if(q[id=seq[i]].xa<mid && q[id].xb<mid) tmp[nowl++]=id;
			else if(q[id].xa>mid && q[id].xb>mid) tmp[nowr--]=id;
		for(int i=l; i<nowl; ++i) seq[i]=tmp[i];
		for(int i=nowr+1; i<=r; ++i) seq[i]=tmp[i];
		Solve(xa,ya,mid-1,yb,l,nowl-1), Solve(mid+1,ya,xb,yb,nowr+1,r);
	}
}

int main()
{
	n=read(), m=read();
	for(int i=1,tot=1; i<=n; ++i,++tot)
		for(int j=1; j<m; ++j,++tot) val[tot][2]=val[tot+1][0]=read();
	for(int i=1,tot=1; i<n; ++i)
		for(int j=1; j<=m; ++j,++tot) val[tot][3]=val[tot+m][1]=read();
	for(int i=1,tot=1; i<=n; ++i)
		for(int j=1; j<=m; ++j,++tot) X[tot]=i, Y[tot]=j;
	memset(Ans,0x3f,sizeof Ans);
	int Q=read();
	for(int i=1,xa,ya,xb,yb; i<=Q; ++i)
	{
		xa=read(), ya=read(), xb=read(), yb=read();
//		if(xa==xb && ya==yb) Ans[i]=0;
		seq[i]=i, q[i]=(Queries){xa,xb,ya,yb,ID(xa,ya),ID(xb,yb),i};
	}
	Solve(1,1,n,m,1,Q);
	for(int i=1; i<=Q; ++i) printf("%d\n",Ans[i]);

	return 0;
}
