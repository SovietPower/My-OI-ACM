/*
令bi=n/xi，那么题意就是完全背包，用任意多个xi构成n-1并输出方案。
同[墨墨的等式]，取最小的因子作为模数，然后跑最短路，最短路的时候记录路径。
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
const int N=5e5+5,INF=0x3f3f3f3f;

int A[N],dis[N],pre[N],pree[N];
std::priority_queue<pr> q;
pr Ans[N];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Dijkstra(int n,int mod)
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
				pre[v]=x, pree[v]=A[i], q.push(mp(-(dis[v]=dis[x]+A[i]),v));
	}
}

int main()
{
	int n=read(),cnt=0,x=n;
	for(int i=2; 1ll*i*i<=x; ++i)
		if(!(x%i)) A[++cnt]=i, i!=x/i&&(A[++cnt]=x/i);
	if(!cnt) return puts("NO"),0;
	std::sort(A+1,A+1+cnt);

	int mod=A[1]; Dijkstra(cnt,mod);
	x=(n-1)%mod;
	if(dis[x]>=INF) return puts("NO"),0;
	puts("YES");
	int tot=0;// x=dis[x];
	Ans[++tot]=mp((n-dis[x])/mod,n/mod);
	while(x) Ans[++tot]=mp(1,n/pree[x]), x=pre[x];
	printf("%d\n",tot);
	for(int i=1; i<=tot; ++i)
	{
		int a=Ans[i].first,b=Ans[i].second;
		while(a>=b) printf("%d %d\n",b-1,b), a-=b-1;//好像没用 
		if(a) printf("%d %d\n",a,b);
	}

	return 0;
}
