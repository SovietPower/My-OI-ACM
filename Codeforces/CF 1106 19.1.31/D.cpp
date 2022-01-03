#include <set>
#include <map>
#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define mod 1000000007//998244353
#define Mod(x) x>=mod&&(x-=mod)
#define Add(x,v) (x+=v)>=mod&&(x-=mod)
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	static bool vis[N];
	static std::vector<int> vec[N];
	static std::priority_queue<int,std::vector<int>,std::greater<int> > q;
	int n=read(),m=read();
	for(int i=1,u,v; i<=m; ++i) u=read(),v=read(),vec[u].push_back(v),vec[v].push_back(u);
	vis[1]=1, q.push(1);
	for(int i=1,x; i<=n; ++i)
	{
		printf("%d ",x=q.top()), q.pop();
		for(int i=0,v,l=vec[x].size(); i<l; ++i)
			!vis[v=vec[x][i]]&&(q.push(v),vis[v]=1);
	}

	return 0;
}

