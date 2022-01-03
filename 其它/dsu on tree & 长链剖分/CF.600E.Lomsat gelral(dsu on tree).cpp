/*
93ms	9100KB
$Description$
给定一棵树，求以每个点为根的子树中，出现次数最多的颜色的和。
$Solution$
dsu on tree.用sum[i]表示出现次数为i的颜色的和，cnt[i]表示出现次数为i的颜色有多少个（其实有个Max表示当前最多的次数，和tm就好了）。
再写一遍dsu on tree大体过程：（设当前点为x）
计算轻儿子子树的答案，并删掉轻儿子的贡献（大多数时候）；
计算重儿子子树的答案，保留重儿子的贡献（有时候不需要？）；
加入x轻儿子子树的贡献；
得到x的答案；
如果x不是重儿子，则删掉它整个子树的贡献（本题直接将Max,Sum清0就好了）。
复杂度证明：每个点会在它上面的每条轻边处暴力统计一次。而每个点到根节点的路径上只有$O(\log n)$条轻边。
可以用DFS序代替DFS减少一些常数。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int skip,Enum,H[N],nxt[N<<1],to[N<<1],Max,col[N],sz[N],son[N],tm[N];
LL Sum,Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x,int fa)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS1(v,x), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
}
void Add(int x,int fa)
{
	if(++tm[col[x]]>Max) Max=tm[col[x]], Sum=col[x];
	else if(tm[col[x]]==Max) Sum+=col[x];
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa && to[i]!=skip) Add(to[i],x);
}
void Del(int x,int fa)
{
	--tm[col[x]];
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa) Del(to[i],x);
}
void Solve(int x,int fa,int keep)
{
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa && to[i]!=son[x]) Solve(to[i],x,0);
	if(son[x]) Solve(son[x],x,1), skip=son[x];
	Add(x,fa), Ans[x]=Sum, skip=0;
	if(!keep) Max=Sum=0, Del(x,fa);
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) col[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1,1), Solve(1,1,1);
	for(int i=1; i<=n; ++i) printf("%I64d ",Ans[i]);

	return 0;
}
