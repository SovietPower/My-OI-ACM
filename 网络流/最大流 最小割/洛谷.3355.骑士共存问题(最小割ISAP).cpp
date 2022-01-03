/*
一个很暴力的想法：每个点拆点，向不能同时存在的连边 
但是这样边太多了，而且会有很多重复。~~我不会说我还写了还没过样例~~ 
我们实际就是在做一个最大匹配。考虑原图，同在黄/红格里的骑士是互不攻击的，即不会连边。
那么拿这两部分建二分图，分别连向S,T。障碍直接不参与连边。这样边数也少 也直观好写。 
原问题尽可能保留多等价于尽可能移走少。求最小割即可。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define ID(x,y) (((x)-1)*n+(y))
const int N=40010,M=N<<3,INF=0x3f3f3f3f,MAXIN=1e5;

int n,m,src,des,Enum,cur[N],H[N],nxt[M<<1],fr[M<<1],to[M<<1],cap[M<<1],q[N],lev[N],num[N],pre[N],id[N][N];
bool Map[203][203],cant[N];
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
	if(!cant[u] && !cant[v])
		to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], cap[Enum]=w, H[u]=Enum,
		to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], cap[Enum]=0, H[v]=Enum;
}
bool BFS()
{
	for(int i=src; i<=des; ++i) lev[i]=des+1;
	lev[des]=0, q[0]=des;
	int h=0,t=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(cap[i^1] && lev[to[i]]==des+1)
				lev[to[i]]=lev[x]+1, q[t++]=to[i];
	}
	return lev[src]<=des;
}
int Augment()
{
	for(int i=des; i!=src; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1];
	return 1;
}
int ISAP()
{
	if(!BFS()) return 0;
	for(int i=src; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int res=0,x=src;
	while(lev[src]<=des)
	{
		if(x==des) res+=Augment(),x=src;
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
			++num[lev[x]=mn+1];
			cur[x]=H[x];
			if(x!=src) x=fr[pre[x]];
		}
	}
	return res;
}

int main()
{
	n=read(),m=read();
	Enum=1, src=0, des=n*n+1;
	for(int u,v,i=1; i<=m; ++i)
		u=read(),v=read(),Map[u][v]=cant[ID(u,v)]=1;
	for(int now,i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			if(!Map[i][j])
				if((i+j)&1)//红格 
					AddEdge(ID(i,j),des,1);
				else
				{
					now=ID(i,j), AddEdge(src,now,1);
					if(i>2){//用for写？无所谓了~~其实是我忘了~~ 
						if(j>1) AddEdge(now,ID(i-2,j-1),INF);
						if(j<n) AddEdge(now,ID(i-2,j+1),INF);
					}
					if(i>1){
						if(j>2) AddEdge(now,ID(i-1,j-2),INF);
						if(j+1<n) AddEdge(now,ID(i-1,j+2),INF);
					}
					if(i+1<n){
						if(j>1) AddEdge(now,ID(i+2,j-1),INF);
						if(j<n) AddEdge(now,ID(i+2,j+1),INF);
					}
					if(i<n){
						if(j>2) AddEdge(now,ID(i+1,j-2),INF);
						if(j+1<n) AddEdge(now,ID(i+1,j+2),INF);
					}
				}
	printf("%d",n*n-m-ISAP());
	return 0;
}
