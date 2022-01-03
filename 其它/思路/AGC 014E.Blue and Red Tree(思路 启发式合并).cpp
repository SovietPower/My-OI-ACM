/*
287ms	25472KB
$Description$
给定两棵$n$个点的树，分别是由$n-1$条蓝边和$n-1$条红边组成的树。求$n-1$次操作后，能否把蓝树变成红树。
每次操作是，选择当前树上一条只由蓝边组成的简单路径$u\to v$，删掉路径上的任意一条蓝边，然后在路径上任选两个点，在这两个点之间加一条红边。
$n\leq10^5$。
$Solution$
模拟一下样例二，就比较容易想到：
考虑能否从红树变回到蓝树。
我们每次要找到当前树上一条蓝边组成的路径$u\to v$，设路径上任意一点是$a$，不在路径上的一个点是$b$。如果当前$a,b$之间有红边相连，而$b$与路径上某点$c$在蓝树上有边，显然这条红边$(a,b)$是可以通过删掉$(b,c)$加入的，也就是现在我们在当前树上删掉边$(a,b)$，加入边$(b,c)$。然后继续找蓝边路径继续扩展。
怎么实现这一过程呢？
对于整条蓝边组成的路径$u\to v$，我们不需要管具体有哪些点，只需要知道$b$与$u\to v$之间既有一条红边，也有一条蓝边（不会有两条红边/蓝边啊，因为每次操作后也是一棵树），然后我们可以删掉这条红边，加入这条蓝边。边具体是哪条也不需要管，我们只需要知道$b$被加入了路径$u\to v$。
所以就可以用并查集实现。$b$被合并到路径$u\to v$前，要把与$b$相连的所有边连到路径$u\to v$（的代表点）上去，可以用启发式合并。
同时有红边和蓝边与路径相连，就是这条边出现了两次。所以我们把出现两次的边拿出来扩展就好了。
能扩展$n-1$次则可行，否则不行。
启发式合并然后用set维护出边，复杂度$O(n\log^2n)$。出边可以hash点对$(u,v)$来维护，少一个$\log$，懒得写了。。
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int fa[N];
std::set<int> st[N];
std::pair<int,int> q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	const int n=read();
	int h=0,t=0;
	for(int i=n-1<<1; i; --i)
	{
		int u=read(),v=read();
//		if(u>v) std::swap(u,v);
		if(!st[u].count(v)) st[u].insert(v), st[v].insert(u);
		else q[t++]=std::make_pair(u,v);
	}
	for(int i=1; i<=n; ++i) fa[i]=i;
	while(h<t)
	{
		int x=Find(q[h].first),y=Find(q[h++].second);
		if(st[x].size()<st[y].size()) std::swap(x,y);//x<-y
		for(std::set<int>::iterator it=st[y].begin(); it!=st[y].end(); ++it)
			if(*it!=x)
			{
				int u=x,v=*it;
				st[v].erase(y);
//				if(u>v) std::swap(u,v);
				if(!st[u].count(v)) st[u].insert(v), st[v].insert(u);
				else q[t++]=std::make_pair(u,v);		
			}
		st[x].erase(y), fa[y]=x;
	}
	puts(t==n-1?"YES":"NO");

	return 0;
}
