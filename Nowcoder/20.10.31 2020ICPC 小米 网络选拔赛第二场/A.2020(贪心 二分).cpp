/*
61ms	7288KB
可以发现 $0$和左边最近的未匹配的$2$匹配 比 $0$和第一个未匹配的$2$匹配 优。
那么 $0$和左边最近的未匹配的$2$匹配 后，可以得到若干可能包含但不相交的区间。
区间$i$包含区间$j$ 则$i,j$不能组成$2020$，否则一定可以。而区间不相交可以转化成树：每个区间$i$以最小的包含$i$的区间作为父节点。
这样建树后问题就是：每个点可以和除祖先外的所有点配对，求最大配对数。
设$mxd$为建树后某点的最大深度，$n$为点数，可以发现若$mxd*2\leq n$则全部可以配对，答案为$\frac n2$（每棵子树最多有$\frac n2$个点，足够和其它子树全部匹配）；否则答案为$n-mxd$（一条链$mxd$个点+若干小支链$n-mxd$个点，显然只有$n-mxd$对能匹配）。
so求一个最大深度就ok。
也可以二分答案，贪心配对看是否可行。
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5;

int dep[N];
char s[N];
std::vector<int> e[N];
struct Node
{
	int l,r;
	bool operator <(const Node &x)const
	{
		return l==x.l?r<x.r:l<x.l;
	}
}A[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v)
{
	e[u].push_back(v), e[v].push_back(u);
}
void DFS(int x,int fa)
{
	for(auto v:e[x])
		if(v!=fa) dep[v]=dep[x]+1, DFS(v,x);
}

int main()
{
	static int sk[N];
	int n;
	while(~scanf("%d",&n))
	{
		scanf("%s",s+1);
		int t=0,cnt=0;
		for(int i=1; i<=n; ++i)
			if(s[i]=='2') sk[++t]=i;
			else if(s[i]=='0'&&t) A[++cnt]=(Node){sk[t--],i};
		if(!cnt) {puts("0"); continue;}

		std::sort(A+1,A+1+cnt), A[sk[0]=0].r=2e9;
		for(int i=1,t=0; i<=cnt; ++i)
		{
			while(A[i].l>A[sk[t]].r) --t;
			AE(sk[t],i), sk[++t]=i;
		}
		DFS(0,0);
		int mxd=0;
		for(int i=1; i<=cnt; ++i) mxd=std::max(mxd,dep[i]);
		printf("%d\n",mxd<<1>cnt?cnt-mxd:cnt>>1);
		for(int i=0; i<=cnt; ++i) std::vector<int>().swap(e[i]);
		for(int i=0; i<=cnt; ++i) dep[i]=0;
	}

	return 0;
}
