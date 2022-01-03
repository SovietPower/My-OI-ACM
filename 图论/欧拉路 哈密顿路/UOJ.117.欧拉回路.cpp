/*
$Description$
求图的欧拉回路（找一个环使每条边恰好出现一次）。若$t=1$该图为无向图，否则为有向图。
$n\leq 10^5,\ m\leq 2\times 10^5$。
$Solution$
这数据。。简直了 
有自环和重边，有些点可能没有连边(并查集不好使 就DFS吧) 
因为重边+自环可能非常多，同一个点可能经过n次，所以必须要重置表头H[x](类似当前弧优化) 
另外是找欧拉**回路**不是欧拉路径，判断不要错 
无向图: 所有点度数都为偶数(这就不需要什么入度出度之分了) 
有向图: 所有点入度=出度(dgr = indgr-outdgr = 0) 
*/
#include <cstdio>
#include <cctype>
#include <cstdlib>
#define gc() getchar()
const int N=1e5+5,M=2e5+5;

int n,m,dgr[N],Enum,H[N],nxt[M<<1],to[M<<1],ans[M],cnt;
bool vis[M<<1];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS_u(int x)
{
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[i])
		{
			H[x]=i/*对于重复多次的点 之前的边直接跳过*/, vis[i]=vis[i^1]=1, DFS_u(to[i]),
			ans[++cnt]=i>>1, i&1?ans[cnt]*=-1:0;
			i=H[x];//i为后续点更新之后的表头 
		}
}
void Undirect()
{
	n=read(),m=read(), Enum=1;
	for(int u,v,i=1; i<=m; ++i)
	{
		u=read(),v=read(),AddEdge(u,v),AddEdge(v,u);
		++dgr[u], ++dgr[v];
	}
	for(int i=1; i<=n; ++i)
		if(dgr[i]&1) {printf("NO"); return;}//所有点度数都为偶数 
	for(int i=1; i<=n; ++i)
		if(dgr[i]) {DFS_u(i); break;}//任找一(与图连通的)点 
	if(cnt<m) printf("NO");
	else{
		puts("YES");
		for(int i=cnt; i; --i) printf("%d ",ans[i]);
	}
}
void DFS_d(int x)
{
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[i])
			H[x]=i, vis[i]=1, DFS_d(to[i]), ans[++cnt]=i, i=H[x];
}
void Direct()
{
	n=read(),m=read();
	int u=0,v;
	for(int i=1; i<=m; ++i)
	{
		u=read(),v=read(),AddEdge(u,v);
		--dgr[u], ++dgr[v];
	}
	int s=u;
	for(int i=1; i<=n; ++i)
		if(dgr[i]) {printf("NO"); return;}//所有点入度=出度 
//		if(dgr[i]&1 && ++t>2) {printf("NO"); return;}//WA: 这是欧拉路 
//	for(int i=1; i<=n; ++i)//WA: 所有点已经度数都为0了。。
//		if(dgr[i]) {DFS_d(i); break;}
	DFS_d(s);
	if(cnt<m) printf("NO");
	else{
		puts("YES");
		for(int i=cnt; i; --i) printf("%d ",ans[i]);
	}
}

int main()
{
	int t=read();
	t==1 ? Undirect() : Direct();
	return 0;
}
