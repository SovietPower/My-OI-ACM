/*
5872kb	184ms
~~容易想到~~最小费用最大流分配度数。
因为水管形态固定，每个点还是要拆成4个点，分别当前格子表示向上右下左方向。
然后能比较容易地得到每种状态向其它状态转移的费用（比如原向上的可以流到向下）。注意比如向左向上的L，左连右，上连下，没有上连右(日常zz)。
解决旋转的问题后，还要处理流量从哪里产生、结束。
因为是网格图，容易想到黑白染色。题目中"没有漏水水管"即格子的断头两两匹配，而匹配只发生在黑白格之间。so源点向所有白格子连边，所有黑格子向汇点连边。
因为匹配关系是确定的，所以即使相邻不一定有水管相连，匹配边还是要连的。
多路增广好快啊。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define OK(i,j) (1<=(i)&&(i)<=n&&1<=(j)&&(j)<=m)
const int N=1e4+5,M=N*30;

int n,m,src,des,Enum,H[N],cur[N],nxt[M],to[M],cap[M],cost[M],dis[N],Cost;
std::queue<int> q;
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int c,bool flag)
{
	if(flag) std::swap(u,v);//黑→白 把边反向 
	to[++Enum]=v, nxt[Enum]=H[u], cost[Enum]=c, cap[Enum]=1, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], cost[Enum]=-c, cap[Enum]=0, H[v]=Enum;
}
bool SPFA()
{
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof dis);
	dis[src]=0, q.push(src);
	while(!q.empty())
	{
		int x=q.front();
		q.pop(), vis[x]=0;
		for(int v,i=H[x]; i; i=nxt[i])
			if(cap[i] && dis[v=to[i]]>dis[x]+cost[i])
				dis[v]=dis[x]+cost[i], !vis[v]&&(q.push(v),vis[v]=1);
	}
	return dis[des]<0x3f3f3f3f;
}
int DFS(int x/*int f*/)
{
	if(x==des) return 1;
	vis[x]=1;
	for(int &i=cur[x]; i; i=nxt[i])
		if(!vis[to[i]] && cap[i] && dis[to[i]]==dis[x]+cost[i])
			if(DFS(to[i]))
				return --cap[i], ++cap[i^1], Cost+=cost[i], 1;
	return 0;
}
int MCMF()
{
	int flow=0;
	while(SPFA())
	{
		for(int i=src; i<=des; ++i) cur[i]=H[i];
		while(DFS(src)) ++flow;
	}
	return flow;
}

int main()
{
	n=read(),m=read(); int tot=0;
	int id[n+1][m+1][4];
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			for(int k=0; k<4; ++k) id[i][j][k]=++tot;
	Enum=1, src=0, des=++tot;
	bool f; int flow=0;
	for(int i=1; i<=n; ++i)
		for(int j=1,s; j<=m; ++j)//0上 1右 2下 3左
		{//左 下 右 上 
			s=read(), f=(i+j)&1;
			int u=f?des:src,up=id[i][j][0],ri=id[i][j][1],down=id[i][j][2],le=id[i][j][3];
			if(s&1) AE(u,up,0,f), flow+=f^1;
			if(s&2) AE(u,ri,0,f), flow+=f^1;
			if(s&4) AE(u,down,0,f), flow+=f^1;
			if(s&8) AE(u,le,0,f), flow+=f^1;
//			if(!f)
//				for(int k=0; k<4; ++k)
//					if(s>>k&1) AE(src,id[i][j][k],0,0), ++flow;
//					else ;//else!
//			else for(int k=0; k<4; ++k) if(s>>k&1) AE(id[i][j][k],des,0,0);
			if(!f)
			{
				if(OK(i-1,j)) AE(up,id[i-1][j][2],0,0);
				if(OK(i,j-1)) AE(le,id[i][j-1][1],0,0);
				if(OK(i+1,j)) AE(down,id[i+1][j][0],0,0);
				if(OK(i,j+1)) AE(ri,id[i][j+1][3],0,0);
			}
			switch(s)
			{
				case 0: break;
				case 1: AE(up,le,1,f), AE(up,ri,1,f), AE(up,down,2,f); break;
				case 2: AE(ri,up,1,f), AE(ri,down,1,f), AE(ri,le,2,f); break;
				case 3: AE(up,down,1,f), AE(ri,le,1,f); break;
				case 4: AE(down,le,1,f), AE(down,ri,1,f), AE(down,up,2,f); break;
				case 5: break;
				case 6: AE(ri,le,1,f), AE(down,up,1,f); break;
				case 7: AE(up,le,1,f), AE(down,le,1,f), AE(ri,le,2,f); break;
				case 8: AE(le,up,1,f), AE(le,down,1,f), AE(le,ri,2,f); break;
				case 9: AE(le,ri,1,f), AE(up,down,1,f); break;
				case 10: break;
				case 11: AE(le,down,1,f), AE(ri,down,1,f), AE(up,down,2,f); break;
				case 12: AE(le,ri,1,f), AE(down,up,1,f); break;
				case 13: AE(up,ri,1,f), AE(down,ri,1,f), AE(le,ri,2,f); break;
				case 14: AE(le,up,1,f), AE(ri,up,1,f), AE(down,up,2,f); break;
				case 15: break;
			}
		}
	if(MCMF()==flow) printf("%d\n",Cost);
	else puts("-1");

	return 0;
}
