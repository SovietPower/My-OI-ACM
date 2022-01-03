/*
17604kb	5528ms
$Description$
给定一棵树，$n$个点每个点有点权。每次询问一条路径，任路径上若干点使异或和最大。$n\leq2\times10^4,q\leq2\times10^5$。
$Solution$
线性基可以$O(\log^2)$暴力合并。然后又是树上路径问题，考虑点分治。
对于每个点$i$求解 $LCA(u,v)=i$时的询问$(u,v)$，只需求出这个点到其它点的线性基后，暴力合并。
但LCA不能直接求。。因为点分治时树形态在变。
于是Get一种新点分治方法：$q[x]$存路径在$x$这棵子树中的询问。处理询问时先找到当前子树的$root$，处理$LCA=root$的询问（即从$root$开始DFS，记一下每个点属于哪棵子子树；再枚举这棵子树的询问$q[x]$，如果LCA是$root$则查询，否则在同一棵子子树的话就把询问分给那棵子树）。
注意这样的话处理的是$root$而不是当前节点$x$；$x$可能还会再访问，so记得清空$x$的询问。btw处理$x$这棵子树前要存下询问后再清空，因为还会有给x的询问。。不能直接清了！ 
注意没有询问时剪个枝。
复杂度$O(60n\log n+60^2q)$。
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 60
typedef long long LL;
const int N=2e4+5,Qs=2e5+5;

int n,Q,Enum,tmp[Qs],H[N],nxt[N<<1],to[N<<1],sz[N],bel[N],X[Qs],Y[Qs],Min,root;
bool vis[N];
LL A[N],Ans[Qs];
std::vector<int> q[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Base
{
	LL b[61];
	inline void Clear() {memset(b,0,sizeof b);}
	inline void Insert(LL x)
	{
		for(int i=Bit; ~i; --i)
			if(x>>i & 1)
				if(b[i]) x^=b[i];
				else {b[i]=x; break;}
	}
	inline void Merge(const Base &x)
	{
		for(int i=Bit; ~i; --i)
			if(x.b[i]) Insert(x.b[i]);
	}
	inline LL Query()
	{
		LL ans=0;
		for(int i=Bit; ~i; --i) ans=std::max(ans,ans^b[i]);
		return ans;
	}
}base[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void Get_root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=f)
		{
			Get_root(v,x,tot), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int f,int Bel)
{
	bel[x]=Bel, base[x]=base[f], base[x].Insert(A[x]);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f&&!vis[to[i]]) DFS(to[i],x,Bel);
}
void Solve(int x)
{
	if(!q[x].size()) return;//!
	Min=N, Get_root(x,x,sz[x]);
	vis[root]=1, bel[root]=root,/*!*/ base[root].Clear(), base[root].Insert(A[root]);
	for(int i=H[root]; i; i=nxt[i]) if(!vis[to[i]]) DFS(to[i],root,to[i]);
	int cnt=q[x].size();
	for(int i=0; i<=cnt; ++i) tmp[i]=q[x][i];//!
	q[x].clear();//! 
	Base b;
	for(int i=0,id; i<cnt; ++i)
		if(bel[X[id=tmp[i]]]==bel[Y[id]]) q[bel[X[id]]].push_back(id);
		else b=base[X[id]], b.Merge(base[Y[id]]), Ans[id]=b.Query();
	for(int i=H[root]; i; i=nxt[i]) if(!vis[to[i]]) Solve(to[i]);
}

int main()
{
	n=read(), Q=read();
	for(int i=1; i<=n; ++i) A[i]=readll();
	for(int i=1; i<n; ++i) AddEdge(read(),read());
	for(int i=1; i<=Q; ++i)
	{
		X[i]=read(), Y[i]=read();
		if(X[i]!=Y[i]) q[1].push_back(i);
		else Ans[i]=A[X[i]];
	}
	sz[1]=n, Solve(1);
	for(int i=1; i<=Q; ++i) printf("%lld\n",Ans[i]);

	return 0;
}
