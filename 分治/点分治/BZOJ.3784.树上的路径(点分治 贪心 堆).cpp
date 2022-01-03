/*
103684kb	2836ms
$Description$
给定一棵$n$个点的带权树，求树上$\frac{n\times(n-1)}{2}$条路径中，长度最大的$m$条路径的长度。
$n\leq50000,\ m\leq\min(3\times10^5,\frac{n\times(n-1)}{2})$。
$Solution$
利用 点分治可以处理出树上所有路径 的性质，在每次点分治处理子树时，我们把当前根$root$和访问到的点$x$依次存到同一个数组里，把存下来的$dis(x,root)$序列记作$d_i$。
再由点分治的性质，这样得到的数组长度是$O(n\log n)$的。

$x$与$root$以及$root$之前子树中的点$y$可以形成一条路径，而且这些点（$root$和$y$）现在在数组中的位置是一段连续的区间，设为$[l,r]$。
那么$dis(x,root)$能和$d_l,d_{l+1},...,d_r$中的任意一个数组合，得到一条路径长为$dis(x,root)+d_i$。
那么问题就变成了，对于一个长为$n\log n$的序列中的每个数$i$，它可以和某个区间$[l_i,r_i]$中的数$j$组合，得到长度为$d_i+d_j$的路径。我们要选出最长的$m$条。

怎么做呢。
最初每个数$i$肯定是和$[l_i,r_i]$中$d_j$最大的$j$组合（RMQ预处理），也就是第一大的值肯定是从所有$i$与$[l_i,r_i]$最大的$j_i$中组合，然后选最大的。
假设我们选出$k$（$k$和对应的$j_k$是所有$i$中$d_i+d_j$最大的），然后之后$k$只能和$[l_k,j)\bigcup(j,r_k]$这些数组合。
而第二大的值要么是从其它的那些$(i,j_i)$中选，要么再拿$k$和$[l_k,j)\bigcup(j,r_k]$中的数组合。
所有我们用堆得到$k$后，再拿$k$分别和$[l_k,j)$中最大的数组合、$(j,r_k]$中最大的数组合，再扔到堆里就好了。
复杂度$O((n\log n+m)\log(n\log n))$。

ps：**ps：**~~在其他题里$n$还没有那么大，所以ST表的一二维顺序影响不大。~~呸 （起码在BZOJ上）影响很大。~~但是~~在这题差别就更明显了。。（7252ms$\to$2896ms）
这个贪心还可以用[可持久化可并堆]写。。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=50005,M=N*16;

int Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],Min,root,sz[N],tot,d[M],L[M],R[M],Ln,Rn,Log[M],pos[20][M];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int val,di,l,r;
	bool operator <(const Node &a)const
	{
		return val<a.val;
	}
};
std::priority_queue<Node> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline int Max(int x,int y)
{
	return d[x]>d[y]?x:y;
}
inline int Query(int l,int r)
{
	int k=Log[r-l+1];
	return Max(pos[k][l],pos[k][r-(1<<k)+1]);
}
void FindRoot(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=fa)
			FindRoot(v,x,tot), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v]);
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void Calc(int x,int fa,int dep)
{
	d[++tot]=dep, L[tot]=Ln, R[tot]=Rn;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=fa) Calc(v,x,dep+len[i]);
}
void Solve(int x)
{
	vis[x]=1, d[++tot]=0, L[tot]=1, R[tot]=0, Ln=Rn=tot;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) Calc(to[i],x,len[i]), Rn=tot;
	for(int i=H[x]; i; i=nxt[i])
		if(!vis[to[i]]) Min=N, FindRoot(to[i],x,sz[to[i]]), Solve(root);
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<n; ++i) AE(read(),read(),read());
	Min=N, FindRoot(1,1,n), Solve(root);

	pos[0][1]=1;
	for(int i=2; i<=tot; ++i) Log[i]=Log[i>>1]+1, pos[0][i]=i;
	for(int j=1; j<=Log[tot]; ++j)//写成 j<=Log[n],i=n-t，还能过除了第6个点外的所有点= =。
		for(int t=1<<j-1,i=tot-t; i; --i)
			pos[j][i]=Max(pos[j-1][i],pos[j-1][i+t]);
	for(int i=1; i<=tot; ++i)
		if(L[i]<=R[i]) q.push((Node){d[i]+d[Query(L[i],R[i])],d[i],L[i],R[i]});

	for(int i=1,p; i<=m; ++i)
	{
		Node tmp=q.top(); q.pop();
		printf("%d\n",tmp.val), p=Query(tmp.l,tmp.r);
		if(tmp.l<p) q.push((Node){tmp.di+d[Query(tmp.l,p-1)],tmp.di,tmp.l,p-1});
		if(p<tmp.r) q.push((Node){tmp.di+d[Query(p+1,tmp.r)],tmp.di,p+1,tmp.r});
	}

	return 0;
}
