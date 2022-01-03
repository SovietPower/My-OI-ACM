/*
枚举时间 
每一个时间点 对于每个之前的位置像当前位置连边，表示这一时刻可待在原地 
每艘船 之前时刻位置向当前时刻连边 
注意别漏了0时刻src连向earth的边 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
const int T=501,N=17*T,M=25*T,INF=1e7;

int n,m,k,src,des,v[25],num[25],pos[25][20];
int Enum,H[N],nxt[M<<1],to[M<<1],cap[M<<1],q[N],lev[N],cur[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
}
bool BFS(int mx)//这个上界别搞错。。
{
	for(int i=0;i<=mx;++i) lev[i]=0,cur[i]=H[i];
	lev[des]=0;//, cur[des]=H[des];
	lev[src]=1, q[0]=src;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(!lev[to[i]] && cap[i])
			{
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
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
		if(lev[to[i]]==lev[u]+1 && cap[i])
		{
			int delta=Dinic(to[i],std::min(cap[i],flow-used));
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
	n=read()+2,m=read(),k=read();
	Enum=1, src=0, des=7501;
	for(int i=1;i<=m;++i)
	{
		v[i]=read(), num[i]=read();
		for(int j=0;j<num[i];++j)
		{
			pos[i][j]=read();
			if(!pos[i][j]) pos[i][j]=n-1;
			else if(pos[i][j]==-1) pos[i][j]=n;
		}
	}
	int res=0,tot=0;
	AddEdge(src,n-1,INF);//,AddEdge(n,des,INF);
	while(++res<500)
	{
		AddEdge(src,res*n+n-1,INF), AddEdge(res*n+n,des,INF);
		for(int i=1;i<n;++i)
			AddEdge((res-1)*n+i,res*n+i,INF);
		for(int i=1;i<=m;++i)
			AddEdge((res-1)*n+pos[i][(res-1)%num[i]],res*n+pos[i][res%num[i]],v[i]);
		while(BFS((res+1)*n)) tot+=Dinic(src,INF);
		if(tot>=k) break;
	}
	if(res==500) putchar('0');
	else printf("%d",res);

    return 0;
}
