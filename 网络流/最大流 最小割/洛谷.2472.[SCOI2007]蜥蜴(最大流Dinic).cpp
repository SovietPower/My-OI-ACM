/*
有石柱的石块看做一个点，连向能到的其它石柱；能直接走出边界的直接连到des；有蜥蜴的连到src 
注意有些需要拆点 
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
const int N=22*22*2,M=22,E=802*27+3*402,way[5]={1,0,-1,0,1},INF=1e9;

int r,c,d,src,des,tot,id[M][M],val[M][M],Enum,H[N],cur[N],to[E<<1],nxt[E<<1],cap[E<<1],q[N],lev[N];
bool vis[N][N];

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
	to[++Enum]=v, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
//	printf("%d->%d:%d\n",u,v,w);
}

void Add(int x,int y,int fr,int las,int s)
{
	if(!s) return;
//	printf("x:%d y:%d fr:%d s:%d\n",x,y,fr,s);
//	if(x<=d||y<=d||r-x+1<=d||c-y+1<=d)
	int xn,yn;
	for(int i=0;i<4;++i)
		if(i!=las && (xn=x+way[i]) && xn<=r && (yn=y+way[i+1]) && yn<=c && !vis[fr][id[xn][yn]])
		{
			if(val[xn][yn]) vis[fr][id[xn][yn]]=1, AddEdge(fr,id[xn][yn],INF);//,printf("%d->%d\n",fr,id[xn][yn]);
			Add(xn,yn,fr,(i+2)%4,s-1);
		}
}

bool BFS()
{
	for(int i=src;i<=des;++i) cur[i]=H[i],lev[i]=0;
	lev[src]=1, q[0]=src;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x];i;i=nxt[i])
			if(cap[i] && !lev[to[i]])
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
		if(cap[i] && lev[to[i]]==lev[u]+1)
		{
			int delta=Dinic(to[i],std::min(flow-used,cap[i]));
			if(delta)
			{
				used+=delta, cap[i]-=delta, cap[i^1]+=delta;
				if(used==flow) return flow;
			}
		}
	lev[u]=0;
	return used;
}

int main()
{
//	freopen("2472.in","r",stdin);

	Enum=1;
	r=read(),c=read(),d=read();
	char tmp[66];
	for(int i=1;i<=r;++i)
	{
		scanf("%s",tmp+1);
		for(int j=1;j<=c;++j)
			if(val[i][j]=tmp[j]-'0')
				id[i][j]=++tot;
	}
	int n=0;
	for(int i=1;i<=r;++i)
	{
		scanf("%s",tmp+1);
		for(int j=1;j<=c;++j)
			if(tmp[j]=='L')
			{
				if(!id[i][j]) id[i][j]=++tot;
				AddEdge(src,id[i][j],1), ++n;
			}
	}
	src=0,des=tot+tot+1;
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j)
		{
			if(!val[i][j]) continue;
			if(i<=d||j<=d||r-i+1<=d||c-j+1<=d) AddEdge(id[i][j],des,val[i][j]);
			else AddEdge(id[i][j],id[i][j]+tot,val[i][j]),Add(i,j,id[i][j]+tot,-1,d);
		}
	int res=0;
	while(BFS()) res+=Dinic(src,1e9);
	printf("%d",n-res);

	return 0;
}
