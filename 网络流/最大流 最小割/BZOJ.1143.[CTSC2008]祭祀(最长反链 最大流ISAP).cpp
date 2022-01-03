/*
1228kb	80ms
题目是求最长反链，反链指点集内任意两点不能互相到达。
根据Dilworth定理，在DAG中，最长反链 = 最小路径覆盖 = V - 最大匹配数。
用Floyd求一遍传递闭包后，在所有可互相到达的点间连边。求二分图最大匹配。
也可以这么理解: 每一条边表示这两个点不能同时被选中，选出最少的一定不选的点(最小割?)，用总点数减去就是答案了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=203,M=25000;

int n,m,src,des,Enum,cur[N],H[N],nxt[M],fr[M],to[M],cap[M],lev[N],num[N],que[N],pre[N];
bool mp[103][103];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, fr[Enum]=u, cap[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, fr[Enum]=v, cap[Enum]=0;
}
void Floyd()
{
	for(int k=1; k<=n; ++k)
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				mp[i][j]|=(mp[i][k]&&mp[k][j]);
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
void Augment(){
	for(int i=des; i!=src; i=fr[pre[i]])
		--cap[pre[i]], ++cap[pre[i]^1];
}
int ISAP()
{
	if(!BFS()) return 0;
	for(int i=src; i<=des; ++i) ++num[lev[i]],cur[i]=H[i];
	int x=src,res=0;
	while(lev[src]<=des)
	{
		if(x==des) x=src,++res,Augment();
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
	n=read(),m=read(),Enum=1,src=0,des=n<<1|1;
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),mp[u][v]=1;
	Floyd();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			if(mp[i][j]) AddEdge(i,j+n,1);
	for(int i=1; i<=n; ++i) AddEdge(src,i,1),AddEdge(i+n,des,1);
	printf("%d",n-ISAP());

	return 0;
}
