/*
将房间、菜放在人的两边建边，这样每条流就是一个决策 
中间表示人的点一定要拆点，只能有一次 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=105,M=N*N*2+N*3;

int n,p,q,src,des,Enum,H[N*4],cur[N*4],lev[N*4],que[N*4],to[M<<1],nxt[M<<1],cap[M<<1];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
		if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}

bool BFS()
{
	for(int i=src;i<=des;++i) cur[i]=H[i],lev[i]=0;
	int h=0,t=1;
	que[0]=src, lev[src]=1;
	while(h<t)
	{
		int x=que[h++];
		for(int i=H[x];i;i=nxt[i])
			if(cap[i] && !lev[to[i]])
			{
				lev[to[i]]=lev[x]+1, que[t++]=to[i];
				if(to[i]==des) return 1;
			}
	}
	return 0;
}
int Dinic(int u,int flow)
{
	if(u==des) return flow;
	int used=0;
	for(int &i=cur[u];i;i=nxt[i])
		if(cap[i] && lev[to[i]]==lev[u]+1)
		{
			int delta=Dinic(to[i],min(cap[i],flow-used));
			if(delta)
			{
				cap[i]-=delta, cap[i^1]+=delta, used+=delta;
				if(used==flow) return flow;
			}
		}
	lev[u]=0;
	return used;
}

int main()
{
	Enum=1;
	n=read(),p=read(),q=read(),src=0,des=n+n+p+q+1;
	for(int tmp,i=1;i<=n;++i)
		for(int j=1;j<=p;++j)
		{
			tmp=read();
			if(tmp) AddEdge(j,i+p,1);
		}
	for(int tmp,i=1;i<=n;++i)
		for(int j=1;j<=q;++j)
		{
			tmp=read();
			if(tmp) AddEdge(i+p+n,j+p+n+n,1);
		}
	for(int i=1;i<=p;++i) AddEdge(src,i,1);
	for(int i=p+1;i<=p+n;++i) AddEdge(i,i+n,1);
	for(int i=p+n+n+1;i<des;++i) AddEdge(i,des,1);
	int res=0;
	while(BFS()) res+=Dinic(src,1e9);
	printf("%d",res);

	return 0;
}
