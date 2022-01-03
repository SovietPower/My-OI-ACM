/*
964kb	76ms
建边不说了。对于议案'?'的输出用拓扑不好判断，直接对每个议案的结果DFS，看是否会出现矛盾 
Tarjan也用不到 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2005,M=16005;

int n,m,Enum,H[N],nxt[M],to[M],conf[N];//conflict
bool vis[N];
char ans[N];

inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
bool DFS(int x)
{
//	if(vis[x+delta*n]) return 0;//WA:由i+n集合会到j集合 我怎么想的。。
	if(vis[conf[x]]) return 0;
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
			if(!DFS(to[i])) return 0;
	return 1;
}
//void dfs(int x)//slow
//{
//	vis[x]=1;
//	for(int i=H[x]; i; i=nxt[i])
//		if(!vis[to[i]]) dfs(to[i]);
//}
//bool DFS(int x,int delta)
//{
//	dfs(x);
//	for(int i=1; i<=n; ++i)
//		if(vis[i]&&vis[i+n]) return 0;
//	return 1;
//}

int main()
{
	scanf("%d%d",&n,&m);
	int a,c; char b[3],d[3];
	for(int i=1; i<=m; ++i)
	{
		scanf("%d%s%d%s",&a,b,&c,d);
		if(b[0]=='Y')//i:false(N) i+n:true(Y)
			if(d[0]=='Y') AddEdge(a,c+n),AddEdge(c,a+n);
			else AddEdge(a,c),AddEdge(c+n,a+n);
		else if(b[0]=='N')
			if(d[0]=='Y') AddEdge(a+n,c+n),AddEdge(c,a);
			else AddEdge(a+n,c),AddEdge(c+n,a);
	}
	for(int i=1; i<=n; ++i) conf[i]=i+n,conf[i+n]=i;
	for(int r1,r2,i=1; i<=n; ++i)
	{
		memset(vis,0,sizeof vis), r1=DFS(i);
		memset(vis,0,sizeof vis), r2=DFS(i+n);
		if(!r1&&!r2) {printf("IMPOSSIBLE"); return 0;}
		else if(r1&&r2) ans[i]='?';
		else if(r1) ans[i]='N';
		else ans[i]='Y';
	}
	ans[n+1]='\0', printf("%s",ans+1);

	return 0;
}
