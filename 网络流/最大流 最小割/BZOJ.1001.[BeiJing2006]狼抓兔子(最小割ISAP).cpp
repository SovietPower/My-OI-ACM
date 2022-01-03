//119968kb	544ms
//路不是有向的，所以要建四条边。。既然如此就直接将反向边的流量设为w了。(or MLE...)
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define MAXIN 2000000
#define Turn(x,y) (((x)-1)*m+(y))
const int N=1e6+5,M=6e6+5,INF=0x3f3f3f3f;

int n,m,src,des,Enum,cur[N],H[N],to[M],nxt[M],fr[M],cap[M],pre[N],que[N],lev[N],num[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], cap[Enum]=w, fr[Enum]=u, H[u]=Enum;
//	to[++Enum]=u, nxt[Enum]=H[v], cap[Enum]=0, fr[Enum]=v, H[v]=Enum;//no need
	to[++Enum]=u, nxt[Enum]=H[v], cap[Enum]=w, fr[Enum]=v, H[v]=Enum;
//	to[++Enum]=v, nxt[Enum]=H[u], cap[Enum]=0, fr[Enum]=u, H[u]=Enum； 
}
bool BFS()
{
	for(int i=src; i<des; ++i) lev[i]=des+1;
	lev[des]=0, que[0]=des; int h=0,t=1;
	while(h<t)
	{
		int x=que[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==des+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, que[t++]=to[i];
	}
	return lev[src]<=des;
}
int Augment()
{
	int mn=INF;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	if(!BFS()) return 0;
	for(int i=src; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int x=src,res=0;
	while(lev[src]<=des)
	{
		if(x==des) x=src,res+=Augment();
		bool can=0;
		for(int i=cur[x]; i; i=nxt[i])
			if(lev[to[i]]==lev[x]-1 && cap[i])
			{
				can=1, cur[x]=i, pre[x=to[i]]=i;
				break;
			}
		if(!can)
		{
			int mn=des;
			for(int i=H[x]; i; i=nxt[i])
				if(cap[i]) mn=std::min(mn,lev[to[i]]);
			if(!--num[lev[x]]) break;
			++num[lev[x]=mn+1], cur[x]=H[x];
			if(x!=src) x=fr[pre[x]];
		}
	}
	return res;
}

int main()
{
	n=read(),m=read(),Enum=1,src=1,des=n*m;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<m; ++j)
			AddEdge(Turn(i,j),Turn(i,j+1),read());
	for(int i=1; i<n; ++i)
		for(int j=1; j<=m; ++j)
			AddEdge(Turn(i,j),Turn(i+1,j),read());
	for(int i=1; i<n; ++i)
		for(int j=1; j<m; ++j)
			AddEdge(Turn(i,j),Turn(i+1,j+1),read());
	printf("%d",ISAP());

	return 0;
}
