/*
857ms	54100KB
$Description$
给定$m$个二元组$(a,b)$，求两个排列$p,q$，使得$\forall i\in[1,m]$，$(p_{a_i}-p_{b_i})(q_{a_i}-q_{b_i})>0$并最大化$\sum_i[p_i\neq q_i]$。
$n,m\leq 5\times 10^5$。
$Solution$
把限制看成边。题意可以化为：给一个无向图，给边定向，使存在两个拓扑序且$p_i=q_i$的点尽量少。（感觉也很抽象，对我没什么用）
考虑什么时候点$x$一定有$p_x=q_x$：和其它所有点相连的点肯定是。所以先将度数为$n-1$的点删掉。
然后每个点至少和一个点没有连边。考虑一个点$x$和一个点集$S$（$k=|S|\geq 1$），满足$x$与$S$中所有点无连边（即$x$与$S$大小关系任意），那么取$p_{x,S_1,S_2,...}=1,2,3,...,k,\ q_{x,S_1,S_2,...}=k,1,2,...,k-1$显然可以使$x,S$合法。
那如果能将图划分成若干个$(x,S)$的结构，因为每个$(x,S)$内部编号连续，$(x,S)$之间的大小关系就不会改变，那么就找到解了。

那我们就模拟这个过程。称上面的与$S$无连边的$x$为关键点。
对于一个尚未考虑的$x$，任取与$x$无连边的点记为$y$。

* 如果$y$也还没考虑过（没加入任何$(x,S)$），那么将$x,y$划分到一个结构中。
* 如果$y$在某个结构中，且是该结构的关键点 或 该结构大小为$2$，那么$y$仍作为关键点，将$x$加入该结构的$S$里。
* 如果$y$在某个结构中但不是该结构的关键点（有$|(x,S)|>2$），那么将$y$从该结构中删掉，将$x,y$划分到一个结构中。

可以发现这个构造只需满足“对任意点存在一个和它没有连边的点”，且最终每个点都属于一个结构且每个结构有一个关键点和$|S|\geq 1$。所以一定有解使所有$i$满足$p_i\neq q_i$。
用`set`维护，复杂度$O(n\log n)$。或者`unordered_map`可以$O(n)$。（不过找一个与$x$无连边的点需要`sort`一下与$x$相连的点，桶排太麻烦所以没必要$O(n)$）

**另一种做法（官方题解）：**
考虑补图，补图里的边即大小关系未定的点对。
只需考虑度数$\leq n-2$的点，它们在补图中度数$\geq 1$，也即至少和一个点未确定大小关系。
考虑一个最小的能调整的结构：菊花图（一个点$x$和一个集合$S$中所有点均有边构成的菊花，$|S|\geq 1$）。调整方式同上。
所以题意变成：给一个图，求一个边集使得每个连通块都是一个菊花图。
那只需对每个连通块求出任意一棵生成树，DFS就可以且一定可以拆出若干菊花图。然后在每个菊花上调整大小关系即可。
DFS是$O(n)$的。但第一种写法好强啊/kel。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=5e5+5;

int bel[N],pnt[N],P[N],Q[N];
std::set<int> st[N];
std::vector<int> e[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Solve()
{
	const int n=read(),m=read();
	for(int i=1,u,v; i<=m; ++i) u=read(),v=read(), e[u].pb(v), e[v].pb(u);
	for(int i=1; i<=n; ++i) std::sort(e[i].begin(),e[i].end());

	int tot=0,now=0;
	for(int x=1; x<=n; ++x)
		if(e[x].size()==n-1) P[x]=Q[x]=++now;
		else if(!bel[x])
		{
			int y=0; e[x].pb(N);
			for(auto v:e[x])
			{
				if(++y==x) ++y;
				if(y!=v) break;
			}
			int bely=bel[y];
			if(!bely)
				bel[x]=bel[y]=++tot, pnt[tot]=x, st[tot].insert(x), st[tot].insert(y);
			else if(pnt[bely]==y||st[bely].size()==2)
				pnt[bely]=y, bel[x]=bely, st[bely].insert(x);
			else
				st[bely].erase(y), bel[x]=bel[y]=++tot, pnt[tot]=x, st[tot].insert(x), st[tot].insert(y);
		}
	for(int i=1; i<=tot; ++i)
	{
		int p=pnt[i]; P[p]=++now;
		for(auto x:st[i])
			if(x!=p) Q[x]=now, P[x]=++now;
		Q[p]=now;
	}
	for(int i=1; i<=n; ++i) printf("%d ",P[i]); pc('\n');
	for(int i=1; i<=n; ++i) printf("%d ",Q[i]); pc('\n');

	for(int i=1; i<=n; ++i) bel[i]=0;
	for(int i=1; i<=tot; ++i) std::set<int>().swap(st[i]);
	for(int i=1; i<=n; ++i) std::vector<int>().swap(e[i]);
}

int main()
{
	for(int T=read(); T--; Solve());
	return 0;
}
