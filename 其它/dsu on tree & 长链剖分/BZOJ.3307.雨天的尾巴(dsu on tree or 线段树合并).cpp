/*
24736kb	4284ms
对修改操作做一下差分放到对应点上，就成了求每个点子树内出现次数最多的颜色，这就和[CF600E](http://codeforces.com/contest/600/problem/E)类似了。直接用$dsu$。
修改某个颜色出现次数的时候，最大值不能$O(1)$求出，得套个$set$，所以复杂度是$O(q\log^2n)$。但常数并不大。
> 关于复杂度，在CF600E中对一个点的修改是$O(1)$的，而本题中可能是$O(q)$（一个点上挂着很多次修改）。但$dsu$的复杂度保证在于，每个点只会被统计$O(\log n)$次，所以不算$set$复杂度依旧是$O(q\log n)$。
一些细节：
计算轻儿子子树贡献的时候必须自叶子向上更新，否则在中间会出现某种颜色出现次数$<0$的情况导致RE...（因为差分的减标记在上面，加标记在底层）；
对子树的DFS可以通过枚举DFS序代替，应该能优化不少常数。
另外BZOJ上z的数据范围其实只有1e5，所以不用离散化233.
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int dep[N],fa[N],sz[N],son[N],top[N],L[N],R[N],A[N],Max,tm[N],cnt[N],Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
std::set<int> st[N];
struct Graph
{
	int Enum,H[N],nxt[N<<2],to[N<<2];
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
	inline void AQ(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
}T,Q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int LCA(int u,int v)
{
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]<dep[v]?u:v;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x])
			fa[v]=x, dep[v]=dep[x]+1, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	static int Index=0;
	A[L[x]=++Index]=x, top[x]=tp;
	if(son[x])
	{
		DFS2(son[x],tp);
		for(int i=T.H[x],v; i; i=T.nxt[i])
			if((v=T.to[i])!=fa[x] && v!=son[x]) DFS2(v,v);
	}
	R[x]=Index;
}
inline void Add(int c)
{
	int t=tm[c]; ++tm[c];
	--cnt[t], ++cnt[t+1], st[t].erase(c), st[t+1].insert(c);
	if(t+1>tm[Max]||(t+1==tm[Max] && c<Max)) Max=c;
}
inline void Subd(int c)
{
	int t=tm[c]; --tm[c];
	--cnt[t], ++cnt[t-1], st[t].erase(c), st[t-1].insert(c);
	if(c==Max) !cnt[t] ? Max=*st[t-1].begin() : Max=*st[t].begin();
}
inline void Upd(int x)
{
	for(int i=Q.H[x]; i; i=Q.nxt[i])
		i&1 ? Add(Q.to[i]) : Subd(Q.to[i]);
}
void Solve(int x,bool keep)
{
	static int Time,vis[N];
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x] && v!=son[x]) Solve(v,0);
	if(son[x]) Solve(son[x],1);

	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa[x] && v!=son[x])
			for(int j=R[v]; j>=L[v]; --j) Upd(A[j]);//要倒序枚举 
	Upd(x), Ans[x]=tm[Max]?Max:0;

	if(!keep)
	{
		Max=0, ++Time;
		for(int u=L[x]; u<=R[x]; ++u)
			for(int i=Q.H[A[u]]; i; i=Q.nxt[i])
			{
				int c=Q.to[i];
				if(vis[c]!=Time) vis[c]=Time, --cnt[tm[c]], st[tm[c]].erase(c), ++cnt[tm[c]=0];//, st[0].insert(c);//erase不存在的元素没有问题 
			}
	}
}

int main()
{
	int n=read(),m=read();
	for(int i=1; i<n; ++i) T.AE(read(),read());
	DFS1(1), DFS2(1,1);
	for(int i=1; i<=m; ++i)
	{
		int x=read(),y=read(),z=read(),w=LCA(x,y);
		Q.AQ(x,z), Q.AQ(w,z), Q.AQ(y,z), Q.AQ(fa[w],z);
	}
	Max=0, cnt[0]=n, Solve(1,1);
	for(int i=1; i<=n; ++i) printf("%d\n",Ans[i]);

	return 0;
}
