#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mpr std::make_pair
#define pr std::pair<int,int>
#define Turn(i,j) (((i)-1)*m+(j))
const int N=3200,M=100000,INF=0x3f3f3f3f;

int n,m,K,src,des,mp[40][40],C[M<<1],Enum,H[N],nxt[M<<1],to[M<<1],cap[M<<1],cost[M<<1],fr[M<<1],pre[N],dis[N];
bool inq[N];
std::queue<int> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w,int c)
{
//	printf("Edge:%d->%d cap:%d cost:%d\n",u,v,w,c);
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, C[Enum]=cap[Enum]=w, cost[Enum]=c;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, C[Enum]=cap[Enum]=0, cost[Enum]=-c;
}
bool SPFA()
{
	memset(dis,0x3f,sizeof dis);
	dis[src]=0, q.push(src);
	while(!q.empty())
	{
		int x=q.front(); q.pop(), inq[x]=0;
		for(int i=H[x]; i; i=nxt[i])
			if(cap[i] && dis[to[i]]>dis[x]+cost[i])
			{
				dis[to[i]]=dis[x]+cost[i], pre[to[i]]=i;
				if(!inq[to[i]]) q.push(to[i]),inq[to[i]]=1;
			}
	}
	return dis[des]<INF;
}
int MCMF()
{
	int res=0,f=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		f=std::min(f,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=f, cap[pre[i]^1]+=f, res+=f*cost[pre[i]];
//		--cap[pre[i]], ++cap[pre[i]^1], ++res;
//	printf("MCMF:%d\n",res);
	return res;
}
void BFS()
{
	int h=0,t=1; pr que[N];
	que[0]=mpr(n,m);
	memset(pre,0,sizeof pre);
	while(h<t)
	{
		int x=que[h].first,y=que[h++].second;
		if(x>1 && mp[x-1][y]) pre[Turn(x-1,y)]=Turn(x,y),que[t++]=mpr(x-1,y);
		if(y>1 && mp[x][y-1]) pre[Turn(x,y-1)]=Turn(x,y),que[t++]=mpr(x,y-1);
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	K=read(),m=read(),n=read();
	int lim=n*m; Enum=1, src=0, des=lim<<1|1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) mp[i][j]=read()-1;
	for(int i=1; i<n; ++i)
		for(int j=1; j<m; ++j)
			if(mp[i][j]) AddEdge(Turn(i,j)+lim,Turn(i+1,j),INF,0),AddEdge(Turn(i,j)+lim,Turn(i,j+1),INF,0);
	for(int i=1; i<n; ++i)
		if(mp[i][m]) AddEdge(Turn(i,m)+lim,Turn(i+1,m),INF,0);
	for(int i=1; i<m; ++i)
		if(mp[n][i]) AddEdge(Turn(n,i)+lim,Turn(n,i+1),INF,0);
	for(int i=1; i<=n; ++i)
		for(int id,j=1; j<=m; ++j)
			if(mp[i][j])
			{
				id=Turn(i,j);
				if(mp[i][j]==1) AddEdge(id,id+lim,1,-1);
				AddEdge(id,id+lim,INF,0);
			}
	AddEdge(src,1,K,0), AddEdge(lim,des,K,0);
	int cnt=1;
	while(SPFA())
	{
		if(MCMF()<0)
		{
			for(int x=1,y=1; x<n||y<m; )
				for(int i=H[Turn(x,y)+lim]; i; i=nxt[i])
					if(to[i]!=Turn(x,y) && C[i]!=cap[i])
					{
						C[i]=cap[i];
						if(to[i]==Turn(x+1,y)) ++x,printf("%d %d\n",cnt,0);
						else ++y,printf("%d %d\n",cnt,1);
						break;
					}
			++cnt;
		}
		else
		{
			BFS();
			for(int i=cnt; i<=K; ++i)
			{
				for(int x=1,y=1; x<n||y<m; )
					if(pre[Turn(x,y)]==Turn(x+1,y)) printf("%d %d\n",i,0),++x;
					else printf("%d %d\n",i,1),++y;
			}
			break;
		}
	}
	return 0;
}
