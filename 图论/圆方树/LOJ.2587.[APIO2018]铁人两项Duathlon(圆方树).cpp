/*
$Description$
给定一张无向图，求有多少种选点$(s,x,t)$的方案，使得图中存在一条$s\to x\to t$的不会走重复点的路径。
$n\leq 10^5,\ m\leq 2\times 10^5$。
$Solution$
先对这张图建圆方树。
对于S->T这条(些)路径，其对答案的贡献为可能经过的所有点数，那么我们把方点权值设为联通分量的大小，求树上路径权值和就行了。
因为两方点之间的圆点会计算两次，所以圆点权值设为-1就好了。
那么现在有n^2个点对，求每个点对之间的路径上点的权值和。
那对每个点计算一下被计算次数就可以了。这个路径次数计算注意考虑全。。
另外点对是圆点的，所以方点初始sz[]为0，圆点才是1。
方点其实建一条边就可以了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=100005<<1,M=4e5+7;//2N!→_→

int n,m,tot,sk[N],top,dfn[N],low[N],Index,fa[N],sz[N],val[N];
long long Ans;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Graph
{
	int H[N],Enum,to[M],nxt[M];
	inline void Add_E(int u,int v){
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	}
	inline void AddEdge(int u,int v){
		Add_E(u,v), Add_E(v,u);
	}
}G,T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++Index, sk[++top]=x, val[x]=-1;
	for(int v,i=G.H[x]; i; i=G.nxt[i])
		if(!dfn[v=G.to[i]])
		{
			fa[v]=x, Tarjan(v), low[x]=std::min(low[x],low[v]);
			if(dfn[x]<=low[v])
			{
				T.Add_E(x,++tot), val[tot]=1;
				do{
					T.Add_E(tot,sk[top--]), ++val[tot];
				}while(sk[top+1]!=v);//别在这把x弹掉。。x可能是多个环的根节点。
			}
		}
		else low[x]=std::min(low[x],dfn[v]);
}
void pre_DFS(int x,int f)
{
	if(x<=n) sz[x]=1;
	for(int i=T.H[x]; i; i=T.nxt[i])
		if(T.to[i]!=f) pre_DFS(T.to[i],x), sz[x]+=sz[T.to[i]];
}
void Solve(int x,int f,int tot)
{
	if(x<=n) Ans+=1ll*(tot-1)*val[x];//以x为起点的路径数 
	Ans+=1ll*(tot-sz[x])*sz[x]*val[x];//起点在x到根方向的一侧，终点在另一侧 
	for(int i=T.H[x]; i; i=T.nxt[i])
		Ans+=1ll*val[x]*(tot-sz[T.to[i]])*sz[T.to[i]], Solve(T.to[i],x,tot);//起点在子树方向，终点到其它地方去(包括x)
		//注意刚开始算了个以x为起点的数，直接交换起点终点(*2)是不对的！
}
//void Solve(int x,int f,int tot)
//{
//	if(x<=n) Ans+=2ll*(tot-1)*val[x];//以x为起点&终点的路径数 
//	int sum=tot-sz[x];
//	for(int i=T.H[x]; i; i=T.nxt[i])
//		Ans+=2ll*val[x]*sum*sz[T.to[i]], sum+=sz[T.to[i]], Solve(T.to[i],x,tot);
//}

int main()
{
	tot=/*!*/n=read(),m=read();
	while(m--) G.AddEdge(read(),read());
	for(int i=1; i<=n; ++i)//不一定连通！这个很mmp。
		if(!dfn[i]) Tarjan(i), pre_DFS(i,i), Solve(i,i,sz[i]);
	printf("%lld",Ans);

	return 0;
}
