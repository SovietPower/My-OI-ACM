/*
952kb	2796ms
第一问拓扑排序即可。
第二问，即让一个元素在拓扑序中尽量靠前，好像不好做。
但是可以让一个元素出现尽量靠后。给它分配一个小的权值，把队列换成优先队列即可（优先弹同一层但是权值大的）。
这题可以直接判队列为空时（或者当前最晚的飞机已晚于当前时间），令它此时起飞。
所以我们建反图，跑$n$次拓扑排序即可。（第一问直接用反图求拓扑序就行）
复杂度$O(nm\log n)$。
这样用堆做虽然能过 但还是有些暴力。。我们按时间排序，模拟一波即可。就不写了。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=2005,M=1e4+5;

int n,tm[N],Enum,H[N],nxt[M],to[M],indgr[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	++indgr[v], to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void Solve1()
{
	static int dgr[N],ans[N];
	std::priority_queue<pr> q;
	memcpy(dgr,indgr,sizeof dgr);

	for(int i=1; i<=n; ++i) if(!dgr[i]) q.push(mp(tm[i],i));
	for(int t=n,x; t; --t)
	{
		ans[t]=x=q.top().second, q.pop();
		for(int i=H[x]; i; i=nxt[i])
			if(!--dgr[to[i]]) q.push(mp(tm[to[i]],to[i]));
	}
	for(int i=1; i<=n; ++i) printf("%d ",ans[i]);
	putchar('\n');
}
int Solve2(int s)
{
	static int dgr[N];
	std::priority_queue<pr> q;
	memcpy(dgr,indgr,sizeof dgr);

	for(int i=1; i<=n; ++i) if(!dgr[i]&&i!=s) q.push(mp(tm[i],i));
	for(int t=n,x; t; --t)
	{
		if(q.empty()) return t;
		x=q.top().second, q.pop();
		if(t>tm[x]) return t;//既然有解那就能保证这样也有解啊 不满足就return了。
		for(int i=H[x]; i; i=nxt[i])
			if(to[i]!=s && !--dgr[to[i]]) q.push(mp(tm[to[i]],to[i]));
	}
	return 1;
}

int main()
{
	n=read(); int m=read();
	for(int i=1; i<=n; ++i) tm[i]=read();
	while(m--) AE(read(),read());
	Solve1();
	for(int i=1; i<=n; ++i) printf("%d ",Solve2(i));

	return 0;
}
