/*
18888KB	3000MS(18892kb	2536ms)
[xxy tql!](https://www.cnblogs.com/TheRoadToTheGold/p/8998774.html)

$d_i$不同就不用说了，建出树来$DFS$一遍。
对于$d_i$不同的情况，考虑如何把这些数依次填到树里。
首先对于已解锁的节点$x$（已解锁是指父节点已经处理完的点，刚开始就是$fa[x]=0$的$x$），为其子树预定$sz[x]$大小的位置。
把$d_i$从小到大排序依次枚举，每次要尽量往$1,2,...,n$这个序列中尽量靠后的位置填（填到$p$表示$Ans_p=d_i$）。
假设现在最小的数是$v$，且一共有$k$个相同的$v$，首先我们要找到最靠右的位置$p$，$p$满足$p\sim n$需求数至少为$k$，然后在$p$处填上$v$（此时一定会在$p$填$v$，因为比$p$大的空位置全加起来也不够$k$个）；然后把$p$位置的$sz[p]$删掉，"解锁"$p$的儿子，即再在$son_p$处预定$sz[son_p]$的大小，看能不能之后填数时填更优的某个$son_p$处。
然后$k$-=$1$，重复上面的过程（找一个满足...的最靠右的位置$p$...），直到$k=0$。
这些都可以用线段树实现。复杂度$O(n\log n)$。
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define eps 1e-9
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int H[N],nxt[N],sz[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson r=m,rt=ls
	#define rson l=m+1,rt=rs
	#define S N<<2
	int sum[S];
	#undef S
	void Modify(int l,int r,int rt,int p,int v)
	{
		while(l!=r)
		{
			sum[rt]+=v;
			int m=l+r>>1;
			p<=m ? (lson) : (rson);
		}
		sum[rt]+=v;
	}
	int Query(int l,int r,int rt,int k)
	{
		while(l!=r)
		{
			int m=l+r>>1;
			sum[rs]>=k ? (rson) : (k-=sum[rs],lson);
		}
		return l;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline double readdb()
{
	double x=0,y=0.1;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);x=x*10+c-48,c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=y*(c-48),y*=0.1,c=gc());
	return x;
}
inline void AE(int u,int v)
{
	nxt[v]=H[u], H[u]=v, sz[u]+=sz[v];
}

int main()
{
	static int A[N],Ans[N];
	const int n=read(); const double K=readdb();
	for(int i=1; i<=n; ++i) A[i]=read(), sz[i]=1;
	std::sort(A+1,A+1+n);
	for(int i=n; i; --i) AE(int(i/K+eps),i);//or floor(i/K) 这样不需要eps...神奇...
	for(int v=H[0]; v; v=nxt[v]) T.Modify(1,n,1,v,sz[v]);
	for(int i=1,j=1; i<=n; i=j)
	{
		while(A[i]==A[j]) ++j;
		for(int k=j-i; k; --k)
		{
			int x=T.Query(1,n,1,k);
			Ans[x]=A[i], T.Modify(1,n,1,x,-sz[x]);
			for(int v=H[x]; v; v=nxt[v]) T.Modify(1,n,1,v,sz[v]);
		}
	}
	for(int i=1; i<=n; ++i) printf("%d ",Ans[i]);

	return 0;
}
