/*
9480kb	1792ms
题意可以看做，用$a_1,a_2,...,a_n$，能组成多少个$[L,R]$中的数。
（40分就是个完全背包）
如果k*ai+x可以组成，那么(k+1)*ai+x自然也可以组成(k>=0,0<=x<ai)。 
即我们选取一个ai做模数，若d=x(mod ai)，则d+ai=x(mod ai)，那么对于当前余数x我们可以算出[0,R]中有多少个数模ai为x（只能由d每次加ai）。对于所有余数算一次就能得到答案。
另外这个d要是满足模ai为x的最小的数（用n个数组合得到）。考虑如何对每个余数求这个$d$。
因为每次是枚举n个数转移（加上再取模），且状态可以用数组存，要求最小，联想到最短路。
dis[x]表示满足模ai为x的能组成的最小的数。那么余数为0的最小的数自然是0，即dis[0]=0。然后SPFA或Dijkstra。
至于ai，取最小的吧。这样图中的点数自然最少。（当然取哪个是任意的，因为最后统计答案时的ai也是这个ai）
如果物品有下限限制，可以把边界先减掉，再这么求。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<LL,int>
typedef long long LL;
const int N=5e5+5;

int n,mod,A[N];
LL dis[N];
std::priority_queue<pr> q;

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Dijkstra()
{
	static bool vis[N];

	memset(dis,0x3f,sizeof dis);
	dis[0]=0, q.push(mp(0,0));
	while(!q.empty())
	{
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=1,v; i<=n; ++i)
			if(dis[v=(x+A[i])%mod]>dis[x]+A[i])
				q.push(mp(-(dis[v]=dis[x]+A[i]),v));
	}
}
inline LL Calc(LL x)
{
	LL ans=0;
	for(int i=0; i<mod; ++i)
		if(dis[i]<=x) ans+=(x-dis[i])/mod+1;//还有个dis[i] 
	return ans;
}

int main()
{
	n=read(); LL L=read(),R=read();
	int cnt=0; mod=N;
	for(int i=1; i<=n; ++i)
		if(!(A[++cnt]=read())) --cnt;//忽略0 
		else mod=std::min(mod,A[cnt]);
	n=cnt, Dijkstra();
	printf("%lld\n",Calc(R)-Calc(L-1));

	return 0;
}
