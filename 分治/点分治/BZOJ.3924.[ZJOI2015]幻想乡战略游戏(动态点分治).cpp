/*
28972kb	35752ms
$Description$
树上点有点权（初始为0），边有边权，每次修改一个点的点权，并询问点$x$使$\sum_idis(x,i)*A_i$最小。$dis$只计算边权。
即带修改查询树上带权重心。
$n,q\leq 10^5$。
$Solution$
依旧点分治。我们考虑怎么计算以x为补给站的答案cost[x].直接用cost[]不好维护，考虑它可以怎么得到。
(以下 x下的子树指点分治时以x为重心访问到的所有节点，即将每次找到的重心处理成一棵树，点分树中的子树)
用v_son[x]表示以x为补给站 x下的子树的所有点的贡献，v_fa[x]表示以fa[x]为补给站 x下子树的所有点的贡献，num[x]表示x下子树点数，这些都是很好动态维护的。
那么利用容斥，我们可以算出fa[x]范围内的cost[x]: cost[x] = v_son[x] + v_son[fa] + num[fa]*dis(x,fa) - v_fa[x] - num[x]*dis(x,fa) (画个图更清楚)
这样因为点分树的深度只有logn，不断向上，复杂度是logn的。
现在如何统计答案？
从一个点x开始，如果它子树中有cost[v]小于cost[x]的点，那么一定往v更优，于是往v所在子树的重心递归(保证复杂度)，直到没有cost[v]<cost[x]，这个cost[x]就是最优解。
这样需要枚举x在原树中的儿子，由于每个点度数不超过20，所以总复杂度是O(20nlog^2n) 
思路不难 却又想了半个上午。。
线段树更优啊 以后再说吧 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

int n,Min,root,sz[N],H[N],fa[N],Enum,val[N<<1],to[N<<1],to_r[N<<1],nxt[N<<1],num[N];
int cnt,pos[N],dis[N],log2[N<<1],st[N<<1][18];
LL v_son[N],v_fa[N];
bool vis[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline void AddEdge(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, val[Enum]=w;
}
void Get_root(int x,int f,int tot)
{
	int mx=0; sz[x]=1;
	for(int v,i=H[x]; i; i=nxt[i])
		if((v=to[i])!=f&&!vis[v])
		{
			Get_root(v,x,tot), sz[x]+=sz[v]/*漏了这句 重心找错T成sb。。*/;
			if(sz[v]>mx) mx=sz[v];
		}
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void pre_DFS(int x,int f)
{
//	int t=++tm; st[++cnt][0]=t, pos[x]=cnt, id[t]=x;
	st[++cnt][0]=dis[x]/*边权为正的话可以直接用dis[]*/, pos[x]=cnt;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=f) dis[to[i]]=dis[x]+val[i], pre_DFS(to[i],x),st[++cnt][0]=dis[x];
}
void Init_RMQ()
{
	for(int i=2; i<=cnt; ++i) log2[i]=log2[i>>1]+1;
	for(int j=1; j<=log2[cnt]; ++j)
		for(int i=cnt-(1<<j-1); i; --i)
			st[i][j]=std::min(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
int LCA_dis(int l,int r)
{
	l=pos[l], r=pos[r];
	if(l>r) std::swap(l,r);
	int k=log2[r-l+1];
	return std::min(st[l][k],st[r-(1<<k)+1][k]);
}
inline int Get_dis(int x,int y){
	return dis[x]+dis[y]-2*LCA_dis(x,y);
}
void Solve(int x)
{
	vis[x]=1;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]])//初始为0真方便 子树不用DFS了 
			Min=N, Get_root(to[i],x,sz[to[i]]), to_r[i]=root, fa[root]=x, Solve(root);
}
LL Calc(int x)
{
	LL res=v_son[x];
	for(int i=x; fa[i]; i=fa[i])
		res+=v_son[fa[i]]-v_fa[i]+1ll*(num[fa[i]]-num[i])*Get_dis(x,fa[i]);
	return res;
}
LL Query(int x)
{
	LL res;int bef;
	while(1)
	{
		res=Calc(x), bef=x;
		for(int i=H[x]; i; i=nxt[i])//一定在to[i]这棵子树上，利用分治树使得递归层数最少 
			if(Calc(to[i])<res) {x=to_r[i]; break;}//这不需要暂存Calc() 
		if(x==bef) return res;
	}
}

int main()
{
	n=read();int q=read(),x,e;
	for(int u,v,w,i=1; i<n; ++i) u=read(),v=read(),w=read(),AddEdge(u,v,w);
	Min=N, Get_root(1,-1,n);
	int rt=root;
	pre_DFS(root,-1), Init_RMQ(), Solve(root);
	while(q--)
	{
		x=read(),e=read(),num[x]+=e;
		for(int i=fa[x]; i; i=fa[i]) v_son[i]+=1ll*e*Get_dis(x,i), num[i]+=e;
		for(int i=x; fa[i]; i=fa[i]) v_fa[i]+=1ll*e*Get_dis(x,fa[i]);
		printf("%lld\n",Query(rt));
	}
	return 0;
}
