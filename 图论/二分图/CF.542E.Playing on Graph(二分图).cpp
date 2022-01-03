//1980ms	3600KB 好慢啊。。
//http://www.cnblogs.com/SovietPower/p/8502993.html
/*
$Description$
给出一个n个点m条边的无向图。
你每次需要选择两个没有边相连的点，将它们合并为一个新点，直到这张图变成了一条链。
最大化这条链的长度，或输出无解。
n<=1000，m<=10000
$Solution$
不难发现无解当且仅当存在奇环。
> 归纳证明：有一个奇环，若与环外一个点合并，这个奇环仍存在；若环内两个点合并，合并两点两边的边数是奇数，合并之后还是至少会有一边边数是奇数，是一个奇环（最后变成一个三角形）。这样怎么合并都会剩下一个奇环。
![](https://images2018.cnblogs.com/blog/1143196/201803/1143196-20180303205446785-1055437104.png)

若不存在奇环，则这是一张二分图（一定有解，直接左右分别合成一定可以形成一个长度为2的链）。

先考虑一些特殊情况
对于一棵树显然答案是直径，然后挂在直径边的点直接合并上去。
对于一个偶环，则找的是对称的两个点，答案应是n/2+1.
![](https://images2018.cnblogs.com/blog/1143196/201803/1143196-20180303205454232-466142059.png)

树是因为两点间的距离固定，所以找一个最长的；
而环是找了最短路最长的一对点。

假设一个点对(a,b)的最短路为x，缩点(相等于添边)x只会变短，那么合并完 (a,b)的距离y一定<=x。这相当于找到一个ans的上界，想办法把答案构出来。

考虑枚举一个点作为链的一端，求出其它点到它的距离di。
因为是个二分图，所以距离某个点距离相等的点一定在二分图的同一侧。
直接把di相同的点合到一起就可以了，会得到一条长度为max{di}的链，并且肯定不存在更长的链。
时间复杂度O(nm)(BFS是必须的 用DFS求最终答案是错的！)

注: 若图不是连通的，则ans=D1+D2+…+Dk(Di为每个连通块的max{di})
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define gc() getchar()
const int N=1e3+5,M=1e5+5;

int n,m,Enum,H[N],nxt[M<<1],to[M<<1],vis[N],cnt,bel[N],ans_b[N],dis[N],q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f)
{
	bel[x]=cnt;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=f && !vis[v]) vis[v]=vis[x]^1, DFS(v,x);
		else if(/*v!=f*/vis[v]==vis[x]) {printf("-1"); exit(0);}
}
int BFS(int now)
{
	memset(dis,0,sizeof dis);
	int h=0,t=1,res=0; q[0]=now, dis[now]=1;
	while(h<t)
	{
		int x=q[h++];
		for(int i=H[x]; i; i=nxt[i])
			if(!dis[to[i]])
				res=std::max(res,dis[to[i]]=dis[x]+1),q[t++]=to[i];
	}
	return res-1;
}

int main()
{
	n=read(),m=read();
	for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v);
	for(int i=1; i<=n; ++i)
		if(!vis[i]) ++cnt,vis[i]=2,DFS(i,i);
	for(int i=1; i<=n; ++i)
		ans_b[bel[i]]=std::max(ans_b[bel[i]],BFS(i));
	int res=0;
	for(int i=1; i<=cnt; ++i) res+=ans_b[i];
	printf("%d",res);

	return 0;
}
