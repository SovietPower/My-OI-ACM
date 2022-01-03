/*
TLE
$Description$
n个点m条边的无向图，每个点有点权。对于任意一个三元环(i,j,k),i<j<k，其贡献为max{ai,aj,ak}。求所有三元环的贡献和。
$Solution$
给定n个点m条边的图，对于每一条边，枚举两个端点中度数较少的端点的邻接点，判断是否构成三元环。这种做法的判断次数在m条边形成一个完全图时达到最大，即O(m*sqrt(m))。
对于任意两条边，我们可以直接枚举度数较小的。
然而这样写怎么TLE了。。本身复杂度不小加每次一定带个set的log？
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5,M=250005;

int n,m,val[N],Link[N],dgr[N];
std::set<int> s[N];
std::vector<int> vec[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	++dgr[u], vec[u].push_back(v), s[u].insert(v);
}
long long Calc(int x,int y)
{
	const std::vector<int> &X=vec[x];
	long long res=0; int v=std::max(val[x],val[y]);
	for(int i=0,l=X.size(); i<l; ++i) if(s[y].count(X[i])) res+=std::max(v,val[X[i]]);
	return res;
}

int main()
{
	n=read(), m=read();
	for(int i=1; i<=n; ++i) val[i]=read();
	for(int i=1,u,v; i<=m; ++i)
		u=read(), v=read(), val[u]>val[v]?AddEdge(u,v):AddEdge(v,u);//不建有向图的话答案/3就行了 
	long long ans=0;
	for(int x=1; x<=n; ++x)
	{
		const std::vector<int> &X=vec[x];
		for(int j=0,l=X.size(); j<l; ++j)
			ans+=dgr[x]<dgr[X[j]]?Calc(x,X[j]):Calc(X[j],x);
	}
	printf("%lld",ans);

	return 0;
}
