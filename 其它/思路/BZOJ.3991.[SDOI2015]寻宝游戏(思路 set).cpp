/*
15412KB	5240MS(Rank8...)
从哪个点出发最短路径都是一样的（最后都要回来）。
脑补一下，最短路应该是按照DFS的顺序，依次访问、回溯遍历所有点，然后再回到起点。
即按DFS序排序后，Ans=dis(p1,p2)+dis(p2,p3)+...+dis(pk,p1)。每次修改一个点，用set维护即可。
int dis[]一分没有啊。。
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int n,Q,Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],ref[N],dfn[N],Index,dep[N],fa[N],top[N],sz[N],son[N];
LL Ans,dis[N];
std::set<int> st;
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
	to[++Enum]=v, nxt[Enum]=H[u], len[Enum]=w, H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], len[Enum]=w, H[v]=Enum;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, dep[v]=dep[x]+1, dis[v]=dis[x]+(LL)len[i], DFS1(v), sz[x]+=sz[v];
			if(mx<sz[v]) mx=sz[v], son[x]=v;
		}
}
void DFS2(int x,int tp)
{
	ref[dfn[x]=++Index]=x, top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=fa[x]&&to[i]!=son[x]) DFS2(to[i],to[i]);
	}
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]<dep[v]?u:v;
}
inline LL Dis(int u,int v){
	return dis[u]+dis[v]-(dis[LCA(u,v)]<<1);
}

int main()
{
	n=read(), Q=read();
	for(int u,v,i=1; i<n; ++i) u=read(),v=read(),AddEdge(u,v,read());
	DFS1(1), DFS2(1,1);
	st.insert(0), st.insert(N-1), ref[0]=0, ref[N-1]=N;
	int p,las,nxt,pos; LL f;
	std::set<int>::iterator it;
	while(Q--)
	{
		p=read();
		if((it=st.find(dfn[p]))!=st.end()) f=-1ll;
		else f=1ll, st.insert(dfn[p]), it=st.find(dfn[p]);
		las=ref[*(--it)], nxt=ref[*(++++it)];

		if(las)
			if(nxt!=N) Ans+=f*(Dis(p,las)+Dis(p,nxt)-Dis(las,nxt));
			else pos=ref[*(++st.begin())], Ans+=f*(Dis(p,las)+Dis(p,pos)-Dis(las,pos));
		else
			if(nxt!=N) pos=ref[*(++st.rbegin())], Ans+=f*(Dis(p,nxt)+Dis(p,pos)-Dis(nxt,pos));
			else ;
		if(f==-1ll) st.erase(dfn[p]);

		printf("%lld\n",Ans);
	}
	return 0;
}
