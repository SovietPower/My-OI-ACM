/*
892kb	64ms
一条边不变其它边减少可以看做一条边增加其它边不变。
假设要加的边lab为(A->B,v)，那么肯定是要使除这条边外，A->B的每条路径上的最小权值都>v，这样在连通A,B时(即Kruskal中Union())才一定会选择这条边。
要求路径上最小边的权值>v，即要求在路径上有任意一边权值<=v时不连通。于是求最小割(使它不连通)，割掉一条边的代价即v[lab]-v[i]+1。
无向图建双向边。
ISAP lev[]的上限是n不是des。。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=505,M=3215;

int n,m,lab,s[805],t[805],v[805];
int src,des,Enum,cur[N],H[N],nxt[M],fr[M],to[M],cap[M],pre[N],lev[N],que[N],num[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, fr[Enum]=u, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w;
	to[++Enum]=u, fr[Enum]=v, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0;
}
bool BFS()
{
	for(int i=1; i<=n; ++i) lev[i]=n+1;
	lev[des]=0, que[0]=des; int h=0,t=1;
	while(h<t)
	{
		int x=que[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(lev[to[i]]==n+1 && cap[i^1])
				lev[to[i]]=lev[x]+1, que[t++]=to[i];
	}
	return lev[src]<=n;
}
int Augment()
{
	int mn=1e9;
	for(int i=des; i!=src; i=fr[pre[i]])
		mn=std::min(mn,cap[pre[i]]);
	for(int i=des; i!=src; i=fr[pre[i]])
		cap[pre[i]]-=mn, cap[pre[i]^1]+=mn;
	return mn;
}
int ISAP()
{
	if(!BFS()) return 0;
	for(int i=1; i<=n; ++i) ++num[lev[i]],cur[i]=H[i];
	int x=src,res=0;
	while(lev[src]<=n)
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
			int mn=n;
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
	n=read(),m=read(),lab=read(),Enum=1;
	for(int i=1; i<=m; ++i) s[i]=read(),t[i]=read(),v[i]=read();
	src=s[lab], des=t[lab];
	for(int i=1; i<=m; ++i)
		if(i!=lab&&v[i]<=v[lab]) AddEdge(s[i],t[i],v[lab]-v[i]+1),AddEdge(t[i],s[i],v[lab]-v[i]+1);
	printf("%d",ISAP());

	return 0;
}
