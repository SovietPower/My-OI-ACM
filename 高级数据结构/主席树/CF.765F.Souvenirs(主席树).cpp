/*
982ms	28900KB
$Description$
给定长为$n$的序列$A_i$。$m$次询问，每次给定$l,r$，求$\min_{l\leq i,j\leq r,i\neq j}|A_i-A_j|$。
$n\leq10^5,\ m\leq3\times10^5$。
$Solution$
离线，把询问按右端点排序。
当右端点$r=i$时，考虑$l$在每个位置的贡献。
先只考虑$j\lt i,\ A_j\geq A_i$的情况。等会把所有数取反再做一次。
$A_i$的贡献就是，找到$i$左边第一个$\geq A_i$的数$A_j$，给区间$[1,j]$的答案和$A_j-A_i$取$\min$。然后找$j$左边第一个$\geq A_i$且$\lt A_j$的数$A_{j'}$，更新区间$[1,j']$...
注意前面区间是可以用$A_j-A_{j'}$做答案的，所以要满足$A_{j'}-A_i\lt A_j-A_{j'}\ \Rightarrow\ A_{j'}\lt\frac{A_j+A_i}{2}$。每次$A_j$会至少除以$2$（虽然会带个$\frac{A_i}{2^k}$，不管它= =），所以只会找$O(\log A)$次。
找$j'$用主席树好了。复杂度是$O(n\log n\log A)$的。离散化一下就是$O(n\log^2n)$了。
（CF数据范围给的真心...nb...=v=）

**PS：**找第一个$j$可以直接单调栈=-=
关于具体如何找，$i$左边第一个$\lt x$的位置（这个数肯定$\lt A_j$，所以不用管此时的$j$）：以权值$A_k$从小到大为下标建主席树，每棵树$T_k$维护$\leq A_k$的位置有哪些。查一下$i$位置在$[A_i,x)$权值中的排名$rk$，然后求$[A_i,x)$中排名$rk-1$的位置就可以惹。
前缀修改最小值，单点查询，可以换成树状数组单点修改，后缀查询最小值。
然后这个写法似乎非常丑...完全比不过线段树+`set`的一个写法...=v=
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,INF=0x7fffffff;

int A[N],root[N],pos[N],rk[N],ref[N],Ans[N*3]/*3n!!!*/;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int l,r,id;
	inline bool operator <(const Quries &x)const
	{
		return r<x.r;
	}
}q[N*3];
struct President_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,son[y][0],l,m
	#define rson rs,son[y][1],m+1,r
	#define S N*18
	int tot,sz[S],son[S][2];
	#undef S
	void Modify(int &x,int y,int l,int r,int p)
	{
		sz[x=++tot]=sz[y]+1;
		if(l==r) return;
		int m=l+r>>1;
		p<=m?(rs=son[y][1],Modify(lson,p)):(ls=son[y][0],Modify(rson,p));
	}
	int GetRank(int x,int y,int l,int r,int p)//y-x
	{
		if(l==r) return sz[y]-sz[x];//1
		int m=l+r>>1;
		return p<=m ? GetRank(lson,p) : sz[son[y][0]]-sz[ls]+GetRank(rson,p);
	}
	int Find(int x,int y,int l,int r,int k)
	{
		if(l==r) return l;
		int m=l+r>>1,t=sz[son[y][0]]-sz[ls];
		return k<=t?Find(lson,k):Find(rson,k-t);
	}
}T1;
struct BIT
{
	int n,t[N];
	#define lb(x) (x&-x)
	inline void Init(int nn) {n=nn, memset(t,0x7f,n+1<<2);}
	inline void Modify(int p,int v)
	{
		for(; p; p^=lb(p)) t[p]=std::min(t[p],v);
	}
	inline int Query(int p)
	{
		int res=INF;
		for(; p<=n; p+=lb(p)) res=std::min(res,t[p]);
		return res;
	}
}T2;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline bool cmp(int a,int b)
{
	return A[a]<A[b];
}
void Solve(const int n,const int Q)
{
	static int sk[N];
	for(int i=1; i<=n; ++i) pos[i]=i;
	std::sort(pos+1,pos+1+n,cmp);
	int cnt=0; T1.tot=0, T2.Init(n);
	for(int i=1; i<=n; ++i) A[pos[i]]!=A[pos[i-1]]&&(ref[++cnt]=A[pos[i]]), rk[pos[i]]=cnt, T1.Modify(root[cnt],root[rk[pos[i-1]]],1,n,pos[i]);//root[rk[pos[i-1]]]
	ref[0]=-INF, A[sk[0]=0]=INF;
	for(int top=0,i=1,now=1; i<=n&&now<=Q; ++i)
	{
		while(A[sk[top]]<A[i]) --top;
		int j=sk[top];
		while(j)
		{
			T2.Modify(j,A[j]-A[i]);
			if(A[i]==A[j]) break;
			int p=std::upper_bound(ref+1,ref+1+cnt,A[i]+A[j]-1>>1)-ref-1;
			if(ref[p]<A[i]) break;
			int t=T1.GetRank(root[rk[i]-1],root[p],1,n,i);
			if(t==1) break;
			j=T1.Find(root[rk[i]-1],root[p],1,n,t-1);
		}
		sk[++top]=i;
		while(q[now].r==i) Ans[q[now].id]=std::min(Ans[q[now].id],T2.Query(q[now].l)), ++now;
	}
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	const int Q=read();
	for(int i=1; i<=Q; ++i) q[i]=(Quries){read(),read(),i};
	std::sort(q+1,q+1+Q), memset(Ans,0x7f,sizeof Ans);
	A[0]=Ans[0], q[Q+1].r=N, Solve(n,Q);
	for(int i=1; i<=n; ++i) A[i]=-A[i];
	Solve(n,Q);
	for(int i=1; i<=Q; ++i) printf("%d\n",Ans[i]);

	return 0;
}
