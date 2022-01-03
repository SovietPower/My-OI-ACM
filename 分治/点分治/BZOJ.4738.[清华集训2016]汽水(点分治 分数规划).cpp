/*
6952kb	6680ms
$Description$
给定一棵树和$k$，求一条路径，使得$\left|\frac{路径长度}{边数}-k\right|$最小。输出最小值。
$n\leq 5\times 10^5,\ k\leq 10^{13}$。
$Solution$
记$val_i$是每条边的边权，$s$是边权和，$t$是经过边数，$k$是给定的$k$。
在点分治的时候二分答案$x$，设$|\frac st-k|=x$，判断是否还能满足$|\frac st-k|<x$。
因为是绝对值，分两种情况：
1. $\frac st-k\geq 0\to \sum val_i-k\geq 0$，
判断是否有$\frac st-k< x\to\quad s-t*k<t*x\to\quad\sum val_i-k<t*x$。
2. $\frac st-k<0\to\sum val_i-k<0$，
判断是否有$\frac st-k>-x\to\quad s-t*k>-t*x\to\quad \sum val_i-k>-t*x$

先对每条边的边权$val_i$减掉一个$k$。
以第一种情况为例，就是求是否存在两条路径$i,j$，使得$s_i+s_j\geq 0$，且$s_i+s_j<t_i*x+t_j*x$。
把$DFS$得到的子树路径信息存一个三元组$(s,t,anc)$，表示一条路径的权值和、边数、这条路径来自哪棵子树（两条路径拼起来的时候不能来自同一棵子树）。
然后把所有三元组按$s$从小到大排序。那从小到大枚举$i$，第一个满足$s_i+s_j\geq 0$的$j$的位置一定是单调递减的，$j$后面（$i$之前）的路径都满足。
所以维护两个$pair$，表示两个$s_k-t_k*x$最小的、来自不同子树的三元组$A,B$。找到第一个$s_p>0$的位置$p$，令$i=p,j=p-1$，然后随着$i$的枚举，更新一下$A,B$，然后$j$也不断往前移动顺便更新$A,B$就可以了。每次对于$i$，就把$A,B$做$k$，与$i$组合一下看是否可以满足$s_k-t_k*x<t_i*x-s_i$。
具体看代码吧，

有两种情况就二分$x$的时候，用两个$check$判断$x$（$\frac st -k\geq 0$）和$-x$（$\frac st-k<0$）是否有一个可行就行了。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<LL,int>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e4+5;
const LL INF=1ll<<60;

int cnt,Enum,H[N],nxt[N<<1],to[N<<1],Min,root,sz[N];
LL Ans,len[N<<1];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	LL s; int t,anc;
	inline bool operator <(const Node &x)const
	{
		return s<x.s;
	}
}A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(LL w,int u,int v)
{
	Ans=std::min(Ans,std::abs(w));//abs!!!
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void FindRoot(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa)
			FindRoot(v,x,tot), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v]);
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void DFS(int x,int fa,LL s,int dep,int anc)
{
	A[++cnt]=(Node){s,dep,anc};
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]] && v!=fa) DFS(v,x,s+len[i],dep+1,anc);
}
inline void Upd(pr &x,pr &y,pr now)
{
	if(now.first<y.first)
	{
		if(now.first<x.first)
		{
			if(now.second!=x.second) y=x;
			x=now;
		}
		else if(now.second!=x.second) y=now;
	}
}
bool Check1(LL k,int pos,int cnt)
{
	pr x(INF,0),y(INF,0); A[0].s=-INF;
	for(int i=pos,j=pos-1; i<=cnt; ++i)
	{
		while(A[i].s+A[j].s>=0) Upd(x,y,mp(A[j].s-k*A[j].t,A[j].anc)), --j;
		if((x.second==A[i].anc?y.first:x.first)+A[i].s<k*A[i].t) return 1;
		Upd(x,y,mp(A[i].s-k*A[i].t,A[i].anc));
	}
	return 0;
}
bool Check2(LL k,int pos,int cnt)
{//s>-tx -> -s<tx
	pr x(INF,0),y(INF,0); A[cnt+1].s=INF;
	for(int i=pos-1,j=pos; i; --i)
	{
		while(A[i].s+A[j].s<0) Upd(x,y,mp(-A[j].s-k*A[j].t,A[j].anc)), ++j;
		if((x.second==A[i].anc?y.first:x.first)-A[i].s<k*A[i].t) return 1;
		Upd(x,y,mp(-A[i].s-k*A[i].t,A[i].anc));
	}
	return 0;
}
void Solve(int x)
{
	vis[x]=1, A[cnt=1]=(Node){0,0,0};
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) DFS(v,x,len[i],1,v);
	int p=1; std::sort(A+1,A+1+cnt), A[cnt+1].s=0;
	while(A[p].s<0) ++p;
	LL l=1,r=Ans,mid;//判断是否存在比Ans小的答案 范围是1~Ans！（UOJ数据真心强=-=）
	while(l<=r)
		if(Check1(mid=l+r>>1,p,cnt)||Check2(mid,p,cnt)) Ans=mid-1, r=mid-1;
		else l=mid+1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) Min=N, FindRoot(v,x,sz[v]), Solve(root);
}

int main()
{
	const int n=read(); const LL K=readll();//readll!!
	Ans=INF;//在这 不能在Solve()前面 = = 
	for(int i=1; i<n; ++i) AE(readll()-K,read(),read());
	Min=N, FindRoot(1,1,n), Solve(root);
	printf("%lld\n",Ans);

	return 0;
}
