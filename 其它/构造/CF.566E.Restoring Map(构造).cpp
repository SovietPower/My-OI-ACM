/*
296ms	100KB
$Description$
对于一棵树，定义某个点的邻居集合为所有距离它不超过$2$的点的集合（包括它自己）。
给定$n$及$n$个点的邻居集合，要求构造一棵$n$个点的树，使得每个给定的集合都对应一个点。输入保证有解。
$n\leq1000$。
$Solution$
如果两个点的邻居集合大小为$2$，那么交集中的两个点之间一定有边。这样我们就可以$O(\frac{n^3}{w})$确定出非叶节点以及它们之间的连边。
然后考虑叶节点应该挂到哪里。如果一个叶节点的邻居集合，和距离某个非叶节点不超过$1$的点的集合相同，那么这两个点之间有边。对于叶子$x$，所有包含$x$的邻居集合中最小的一定就是$x$的邻居集合。一个点数$\geq3$的树，离某个点距离不超过$1$的点的集合是互不相同的。
需要特判非叶节点只有一个和两个的情况。
官方题解是，找出叶子$x$的邻居集合，如果除去$x$集合大小$\geq3$，那么在集合内度数$>1$的点就是与$x$相邻的。否则集合大小是$2$，这种情况有些难判，但是与$x$相邻的点一定只与一个非叶节点相连。所以我们只需要特判$x-a-b-...$这种情况。
还有种[并查集的写法](http://codeforces.com/contest/566/submission/39085398)，太傻逼了看不懂了QAQ。
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1003;

std::bitset<N> st[N],nle,adj[N];
bool not_leaf[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i)
		for(int T=read(); T--; st[i][read()]=1);
	int m=0;
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			if((st[i]&st[j]).count()==2)
			{
				std::bitset<N> tmp=st[i]&st[j];
				int s=0,t=0;
				for(int k=1; k<=n&&!t; ++k) if(tmp[k]==1) s?t=k:s=k;//可以用_Find_next。但是暴力复杂度也是对的，暴力好咯。
				if(!adj[s][t])
					++m, printf("%d %d\n",s,t), nle[s]=nle[t]=1,
					adj[s][s]=adj[s][t]=1, adj[t][t]=adj[t][s]=1, not_leaf[s]=not_leaf[t]=1;
			}
	if(!m)
	{
		for(int i=2; i<=n; ++i) printf("%d %d\n",1,i);
		return 0;
	}
	if(m==1)
	{
		int s=0,t=0,a=0,b=0;
		for(int i=1; i<=n&&!t; ++i) if(not_leaf[i]) s?t=i:s=i;
		for(int i=1; i<=n; ++i)
			if(st[i].count()!=n)
			{
				for(int j=1; j<=n; ++j) !not_leaf[j]&&printf("%d %d\n",j,st[i][j]?s:t);
				break;
			}
		return 0;
	}
	for(int i=1; i<=n; ++i)
		if(!not_leaf[i])
		{
			int mn=N,p=0;
			for(int j=1; j<=n; ++j) if(st[j][i]&&st[j].count()<mn) mn=st[j].count(), p=j;
			std::bitset<N> tmp=st[p]&nle;
			for(int j=1; j<=n; ++j)
				if(tmp[j]&&tmp==adj[j])
					{printf("%d %d\n",i,j); break;}
		}

	return 0;
}
