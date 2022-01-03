/*
9068kb	10588ms
题目的限制即：给定一棵树，只能任选一个连通块然后做背包，且每个点上的物品至少取一个。求花费为$m$时最大价值。
令$f[i][j]$表示在点$i$，已用体积为$j$的最大价值。
如果物品数量为$1$，那就是一个树形依赖背包（选儿子必须选父亲），用DFS序优化转移：$f[i][j]=\max(f[i+1][j-v_i]+w_i,\ f[i+sz_i][j])$（选该节点就可以从上一个点，即子树内转移，否则只能从另一棵子树转移），复杂度$O(nm)$。
物品数量不为$1$，$\max$的前半部分再做一次[单调队列优化多重背包]就行了。。复杂度也是$O(nm)$。（注意依赖关系，当前节点至少取一个，判一下转移位置即可）

然后如果枚举每棵子树暴力转移，复杂度是$O(n^2m)$的。
枚举所有连通块，可以套个点分治；或者$dsu\ on\ tree$，保留重儿子的DP数组。（不写$dsu$了，但貌似常数比点分治小很多！）
然后就是$O(nm\log n)$了。

单调队列因为常数问题，在数据随机情况下比复杂度$O(nm\log num)$的二进制优化多重背包慢一些。。
（而且这题$num$才$100$，数据随机不随机影响也不大了...所以这题单调队列就是慢很多很多了）
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=505,M=4005;

int n,m,Ans,W[N],V[N],num[N],Enum,H[N],nxt[N<<1],to[N<<1],Min,root,sz[N],cnt,A[N],f[N][M];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void FindRoot(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=fa)
			FindRoot(v,x,tot), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v]);
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void MultiplePack(int *f,int *g,int val,int v,int num)
{
	static int qn[M],qv[M];
	const int m=::m;
	for(int r=0; r<v; ++r)//余数r 
		for(int now=r,k=0,h=1,t=0; now<=m; now+=v,++k)
		{
			if(qn[h]+num<k) ++h;
			if(h<=t) f[now]=std::max(f[now],qv[h]+k*val);//h<t时转移 就可以保证强制至少选一个了啊 
			int tmp=g[now]-k*val;//更新完f[now]再用g[now]更新队尾啊 要不有最优的会给弹掉了 
			while(h<=t && qv[t]<=tmp) --t;
			qv[++t]=tmp, qn[t]=k;
		}
}
void DP(const int cnt)
{
	for(int i=cnt; i; --i)
	{
		int x=A[i];
		for(int j=1,s=sz[x]; j<=m; ++j) f[i][j]=f[i+s][j];
		MultiplePack(f[i],f[i+1],W[x],V[x],num[x]);
	}
	for(int i=1; i<=m; ++i) Ans=std::max(Ans,f[1][i]);
	for(int i=1,s=m+1<<2; i<=cnt; ++i) memset(f[i],0,s);
}
void DFS(int x,int fa)
{
	sz[x]=1, A[++cnt]=x;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=fa) DFS(v,x), sz[x]+=sz[v];
}
void Solve(int x)
{
	vis[x]=1, cnt=0, DFS(x,0), DP(cnt);
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) Min=N, FindRoot(to[i],x,sz[to[i]]), Solve(root);
}

int main()
{
	for(int T=read(); T--; )
	{
		n=read(),m=read();
		for(int i=1; i<=n; ++i) W[i]=read();
		for(int i=1; i<=n; ++i) V[i]=read();
		for(int i=1; i<=n; ++i) num[i]=read();
		for(int i=1; i<n; ++i) AE(read(),read());
		Ans=0, Min=N, FindRoot(1,1,n), Solve(root);
		printf("%d\n",Ans);
		Enum=0, memset(H,0,n+1<<2), memset(vis,0,n+1);//bool!
	}
	return 0;
}
