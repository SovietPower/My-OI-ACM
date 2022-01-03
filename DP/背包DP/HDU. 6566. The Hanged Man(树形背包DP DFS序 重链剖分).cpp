/*
78MS	9920Kb
$Description$
给一棵$n$个点的树，每个点有体积$a_i$和价值$b_i$，求总容量分别为$1\sim m$时选出一个最大价值独立集（相邻节点不能同时选）的方案数。
$n\leq 50,m\leq 5000$。
$Solution$
还是先考虑最简单的，$f[i][j][0/1]$表示当前为点$i$，已选$j$体积，选/不选$i$的方案数。树上背包复杂度$O(nm^2)$。
考虑用DFS序优化树形背包。问题在于 DFS序从$i$到$i+1$时，这个点$A_i$可能先向上走很多步到$x$，然后再向下到$A_{i+1}$，所以需要记录$x$的状态才能知道$fa[A_{i+1}]$选没选。同理，DP时要记一个点到根节点路径上所有点的状态，状态数就成了$2^n$。
优化是，用重链剖分来求DFS序，先DFS轻儿子再走重儿子。这样$i$到$i+1$需要向上跳时，会跳过$i$所在的一整条重链（走一条轻边$fa[top[A_i]]-top[A_i]$到$i+1$所在重链），对$i+1$我们只需记$fa[top[A_i]]$的状态。
同理，只需对每一条轻边$u\to v$记点$u$的状态，一共要记当前点到根节点路径上$O(轻边条数)=O(\log n)$个点的状态，状态数为$2^{\log n}=n$。
复杂度$O(n^2m)$。
细节：先把所有点要记的所有$fa[top[i]]$求出来（记为$sta$）。转移时，先枚举$sta_i$求出$sta_{i+1}$的状态，然后再枚举选不选$i+1$更新$s_{i+1}$即可。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb push_back
typedef long long LL;
const int N=54,M=5004;

int A[N],B[N],fa[N],son[N],sz[N],top[N],Index,dfn[N],Ref[N];
std::vector<int> e[N],sta[N];
struct Node
{
	int val; LL cnt;
	Node(int val=0,LL cnt=0):val(val),cnt(cnt) {}
	Node operator +(const Node &x)const
	{
		return val==x.val?Node(val,cnt+x.cnt):val>x.val?*this:x;
	}
	friend void operator +=(Node &t,const Node &x)
	{
		t.val==x.val?(t.cnt+=x.cnt):t.val<x.val?(t=x,0):0;
	}
}ans[M],f[2][N<<1][M];//实际不需要N*2空间（算上自己也严格小于等于logn？），但最好还是开2N 

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v)
{
	e[u].pb(v), e[v].pb(u);
}
void DFS1(int x)
{
	int mx=0; sz[x]=1, son[x]=0/*!*/;
	for(auto v:e[x])
		if(v!=fa[x])
			fa[v]=x, DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
}
void DFS2(int x,int tp)
{
	Ref[dfn[x]=++Index]=x, top[x]=tp;
	for(auto v:e[x])
		if(v!=fa[x] && v!=son[x]) DFS2(v,v);
	if(son[x]) DFS2(son[x],tp);
}
void Clear(int p,int n,int m)
{
	const Node c=Node(0,0);
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=m; ++j) f[p][i][j]=c;
}
void Solve()
{
	static int num[N];

	const int n=read(),m=read();
	for(int i=1; i<=n; ++i) A[i]=read(),B[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1), Index=0, DFS2(1,1);

	for(int i=1; i<=n; ++i)
		for(int x=i; x; sta[i].pb(x),x=fa[top[x]]);
	Clear(0,n*2,m), Clear(1,n*2,m);//不需要n*2 

	int now=0,nxt=1;
	f[now][0][0]=Node(0,1), f[now][1][A[1]]=Node(B[1],1);
	for(int q=2; q<=n; ++q,std::swap(now,nxt))
	{
		int x=Ref[q],y=Ref[q-1];
		int limx=(1<<sta[x].size())-1,limy=(1<<sta[y].size())-1;
		Clear(nxt,limx,m);

		int cnt=0;
		for(auto p:sta[x]) num[p]=cnt++;//这不是O(n)的事嘛为啥都要n^2 

		int fa=-1,tmp=::fa[x];
		for(auto p:sta[y]) if(++fa,p==tmp) break;//fa[x]在sta[y]里 

		for(int s=0; s<=limy; ++s)
		{
			int ss=0,i=0;
			for(auto v:sta[y])
			{
				if(s>>i&1 && num[v]) ss|=(1<<num[v]);
				++i;
			}
			for(int i=0; i<=m; ++i) // 注意sta[x][0]=x
				if(f[now][s][i].cnt)
				{
					f[nxt][ss][i]+=f[now][s][i];
					if(!(s>>fa&1) && i+A[x]<=m)
						f[nxt][ss|1][i+A[x]]+=Node(f[now][s][i].val+B[x],f[now][s][i].cnt);
				}
		}
		for(auto p:sta[x]) num[p]=0;
	}

	const Node c=Node(0,0);
	for(int i=1; i<=m; ++i) ans[i]=c;
	for(int s=0,lim=1<<sta[Ref[n]].size(); s<lim; ++s)
		for(int i=1; i<=m; ++i)
			ans[i]=ans[i]+f[now][s][i];
	for(int i=1; i<=m; ++i) printf("%lld%c",ans[i].cnt," \n"[i==m]);

	for(int i=1; i<=n; ++i) std::vector<int>().swap(e[i]);
	for(int i=1; i<=n; ++i) std::vector<int>().swap(sta[i]);
}

int main()
{
	for(int T=read(),t=1; t<=T; printf("Case %d:\n",t++),Solve());
	return 0;
}
