/*
36944kb	3808ms
$Description$
给定一棵树，每次询问给定$p,k$，求满足$p,a$都是$b$的祖先，且$p,a$距离不超过$k$的三元组$p,a,b$个数。
$n,q\leq3\times10^5$。
$Solution$
$p,a,b$都在一条链上。
那么如果$a$是$p$的祖先，答案就是$\min(dep[p],\ k)*(sz[p]-1)$。可以$O(1)$计算。
如果$a$在$p$的子树中，答案就是$\sum_{dis(a,p)\leq k}sz[a]-1$。
对于第二种情况，实际就是对深度在$dep[p]\sim dep[p]+k$且处于$p$子树内的点的$size$求和。
以$dep$为下标，就是对$p$子树区间求和了。可以主席树/线段树合并。时空复杂度$O(n\log n)$。

也可以用树状数组维护深度为$x$的所有点的$size$和。类似天天爱跑步，在进入一棵子树时把$Ans$减去$sum(dep[p],dep[p]+k)$，离开这棵子树时把$Ans$再加上$sum(dep[p],dep[p]+k)$，就可以得到这棵子树的答案$Ans$了。
时间复杂度$O(n\log n)$。

用到的数组下标是深度，所以可以试下长链剖分。同样$f[x][i]$表示以$x$为根深度为$i$的点的$size$和。
长链剖分每次继承重儿子要把数组后移一位，而我们要求区间和，这样前缀和就不好维护了。但是我们可以维护后缀和。
复杂度$O(n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5;

int sz[N],dep[N],mxd[N],son[N],pos[N];
LL Ans[N],f[N];//f:后缀和 //LL!
char IN[MAXIN],*SS=IN,*TT=IN;
struct Edge
{
	int Enum,H[N],nxt[N<<1],to[N<<1];
	inline void AE(int u,int v)
	{
		to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
		to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
	}
}T;
struct Quries
{
	int Enum,H[N],nxt[N],id[N],k[N];
	inline void AE(int ID,int K,int u)
	{
		id[++Enum]=ID, k[Enum]=K, nxt[Enum]=H[u], H[u]=Enum;
	}
}Q;


inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void DFS1(int x,int fa)
{
	int mx=-1;/*-1!*/ sz[x]=1;
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa)
			dep[v]=dep[x]+1, DFS1(v,x), sz[x]+=sz[v], mxd[v]>mx&&(mx=mxd[v],son[x]=v);
	mxd[x]=mx+1;
}
void DFS2(int x,int fa)
{
	static int Index=0;
	int px=pos[x]=++Index;// f[px]=sz[x]-1;
	if(!son[x]) return;
	DFS2(son[x],x), f[px]+=f[px+1];
	for(int i=T.H[x],v; i; i=T.nxt[i])
		if((v=T.to[i])!=fa && v!=son[x])
		{
			DFS2(v,x); int pv=pos[v];
			for(int j=0,lim=mxd[v]; j<lim; ++j) f[px+j+1]+=f[pv+j];
			f[px]+=f[pv];
		}
	LL sum=f[px];
	for(int i=Q.H[x],mx=mxd[x]; i; i=Q.nxt[i])
	{
		int k=Q.k[i],id=Q.id[i];
		Ans[id]=1ll*std::min(dep[x],k)*(sz[x]-1)+sum-(k>=mx?0:f[px+k+1]);
	}
	f[px]+=sz[x]-1;
}

int main()
{
	int n=read(),q=read();
	for(int i=1; i<n; ++i) T.AE(read(),read());
	for(int i=1; i<=q; ++i) Q.AE(i,read(),read());
	DFS1(1,1), DFS2(1,1);
	for(int i=1; i<=q; ++i) printf("%lld\n",Ans[i]);

	return 0;
}
