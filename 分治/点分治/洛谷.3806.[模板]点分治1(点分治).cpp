/*
题意: 给定一棵有n个点的树，多次询问树上距离为k的点对是否存在。k<=1e7。
依旧点分治。注意到k的大小是可以开数组的，对于所有出现的路径长度用sum[]记录下来，容斥去重时可以直接减掉。
但是如果像上面那样记录的话，复杂度是O(n^2)的。(数据弱还是能过)
注意到询问只有100个，每次Calc()可以对每个询问更新答案，即对于每个询问q[i]看是否有dep[q[i]-dep[j]]出现。
为了不让当前点的同子树的路径重复更新答案，每次得到一棵子树的D[]时，将其与之前子树得到的D[](记为s[])更新答案，更新完后再加入s[]。
注意初始s[0]=1(另外数据有0边，所以应该是在每次计算前s[0]=1).
当然仍然可以用之前的方法做，不过是二分有多少条路径长度等于Q[j]-dep[i]。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=10005,MAXIN=5e4;

int n,m,root,Min,Q[105],dep[N],D[N],sz[N],Enum,H[N],nxt[N<<1],to[N<<1],val[N<<1],q[N]/*清空状态*//*,sum[10000003]*/;
bool vis[N],Ans[105],s[10000003];
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
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void Get_Root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=f)
		{
			Get_Root(v,x,tot), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx,root=x;
}
void DFS(int x,int f)
{
	D[++D[0]]=dep[x];
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]&&to[i]!=f)
			dep[to[i]]=dep[x]+val[i], DFS(to[i],x);
}
void Calc(int x,int v)
{
	D[0]=0, dep[x]=v, DFS(x,-1);
	for(int i=1; i<=D[0]; ++i)
		for(int j=1; j<=m; ++j)
			if(Q[j]>=D[i]) Ans[j]|=s[Q[j]-D[i]];
	for(int i=1; i<=D[0]; ++i) s[D[i]]=1,q[++q[0]]=D[i];
//	for(int i=1; i<D[0]; ++i)
//		for(int j=i+1; j<=D[0]; ++j)
//			sum[D[i]+D[j]]+=delta;
}
void Solve(int x)
{
	vis[x]=1, q[0]=0, s[0]=1; 
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
			Calc(to[i],val[i]);//处理完当前节点后再处理其它节点 
	for(int i=1; i<=q[0]; ++i) s[q[i]]=0;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])
			Min=N, Get_Root(to[i],x,sz[to[i]]), Solve(root);
}

int main()
{
	n=read(),m=read();
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	for(int i=1; i<=m; ++i) Q[i]=read();
	Min=N, Get_Root(1,-1,n), Solve(root);
	for(int i=1; i<=m; ++i) puts(Ans[i]?"AYE":"NAY");

	return 0;
}
