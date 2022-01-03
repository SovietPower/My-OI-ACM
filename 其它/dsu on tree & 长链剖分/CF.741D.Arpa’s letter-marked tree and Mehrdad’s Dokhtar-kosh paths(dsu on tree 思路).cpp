/*
608ms	79100KB
$Description$
给定一棵树，每条边上有一个字符(a~v)。对每个节点，求它的子树中一条最长的路径，满足 路径上所有边上的字符可以重新排列成一个回文串。输出最长长度。
$n\leq 5\times10^5$。
$Solution$
可以构成回文串，即要么所有字符都出现了偶数次，要么有一个出现了奇数次、其余都出现了偶数次。
转化为异或！把每个字符c(0~21)映射到1<<c上去。令$s[x]$表示根节点到$x$路径上边权的异或和。那么路径$(u,v)$满足条件当且仅当$s[u]^s[v]$等于0或是某个二次幂。
而路径$(u,v)$的答案是$dep[u]+dep[v]-dep[LCA]*2$。在LCA处计算，这样只需要对每个状态求它最大的$dep$，而且更新时只有23种方式（对于$s[v]$，可以从$\max\{dep[s[v]]\}$和$\max\{dep[s[v]^(1<<i)]\}$更新）。
dsu on tree求每个子树的$\max\{dep[s]\}$就好了。
复杂度$O(23n\log n)$。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5,INF=0x3f3f3f3f;

int Enum,H[N],nxt[N],to[N],ch[N],s[N],f[(1<<22)+2],L[N],R[N],A[N],dep[N],sz[N],son[N],Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int c)
{
	to[++Enum]=v, nxt[Enum]=H[u], ch[Enum]=c, H[u]=Enum;
}
void DFS1(int x)
{
	static int Index=0;
	A[L[x]=++Index]=x;
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		dep[v=to[i]]=dep[x]+1, s[v]=s[x]^ch[i], DFS1(v), sz[x]+=sz[v], sz[v]>mx&&(mx=sz[v],son[x]=v);
	R[x]=Index;
}
inline int Add(int s,int d,int delta)
{
	int ans=f[s]+d-delta;
	for(int i=0; i<22; ++i) ans=std::max(ans,f[s^(1<<i)]+d-delta);//d[u]+d[v]-d[LCA]*2
	return ans;
}
void DFS2(int x,int keep)
{
	int ans=0;
	for(int i=H[x]; i; i=nxt[i]) if(to[i]!=son[x]) DFS2(to[i],0),ans=std::max(ans,Ans[to[i]]);
	if(son[x]) DFS2(son[x],1),ans=std::max(ans,Ans[son[x]]);

	ans=std::max(ans,Add(s[x],0,dep[x])), f[s[x]]=std::max(f[s[x]],dep[x]);
	for(int i=H[x],v,delta=dep[x]<<1; i; i=nxt[i])
		if((v=to[i])!=son[x])
		{
			for(int j=L[v]; j<=R[v]; ++j) ans=std::max(ans,Add(s[A[j]],dep[A[j]],delta));
			for(int j=L[v]; j<=R[v]; ++j) f[s[A[j]]]=std::max(f[s[A[j]]],dep[A[j]]);
		}
	Ans[x]=ans;
	if(!keep) for(int i=L[x]; i<=R[x]; ++i) f[s[A[i]]]=-INF;
}

int main()
{
	int n=read();
	for(int i=2,x,c; i<=n; ++i)
	{
		x=read(),c=gc(); while(!isalpha(c)) c=gc();
		AE(x,i,1<<c-'a');
	}
	memset(f,-0x3f,sizeof f);//没有的值不能用0更新 
	DFS1(1), DFS2(1,1);
	for(int i=1; i<=n; ++i) printf("%d ",Ans[i]);

	return 0;
}
